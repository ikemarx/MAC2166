/***************************************************************/
/**                                                           **/
/**   Henrique Schneider Marx                    14578432     **/
/**   Exercicio-Programa 3                                    **/
/**   Professora Cristina Gomes Fernandes                     **/
/**   Turma: 02                                               **/
/**                                                           **/
/***************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_PIXELS 1000000
#define rand2166() (rand2166f(-1))
#define srand2166(seed) (rand2166f((seed)))
#define AA 16807
#define MM 2147483647
#define MIN_PIXELS 10000

void output_image(int col, int row, int v_max, int image[]);
void read_image(int *col, int *row, int *v_max, int **image);
void encode(int col, int row, int v_max, int image[], int key);
void decode(int col, int row, int v_max, int image[], int key, int decoded[]);
void decode_in_loco(int col, int row, int v_max, int image[], int key);
void decode_brute_force(int col, int row, int v_max, int image[], int max_key);
double entropy(int v_max, int N, int image[]);
int rand2166f(int seed);
void decode_fast(int v_max, int image[], int key, int decoded[]);

int main(int argc, char *argv[]) {
	int col, row, v_max;
	int *image = NULL;
	int key = atoi(argv[2]);
	int opcao = atoi(argv[1]);
	read_image(&col, &row, &v_max, &image);
	if (opcao == 0)
		encode(col, row, v_max, image, key);
	if (opcao == 1)
		decode_in_loco(col, row, v_max, image, key);
	if (opcao == 2)
		decode_brute_force(col, row, v_max, image, key);
	output_image(col, row, v_max, image);
	free(image);
	return 0;
}
void output_image(int col, int row, int v_max, int image[]) {
	int i, j;
	printf("P2\n%d %d\n%d\n", col, row, v_max);
	for (i = 0;i < row;i++) {
		for (j = 0;j < col; j++)
			printf("%03d ", image[i * col + j]);
		printf("\n");
	}
}
void read_image(int *col, int *row, int *v_max, int **image) {
	int i;
	scanf("P2\n%d %d\n%d", col, row, v_max);
	*image = malloc(*col * *row * sizeof(int));
	for (i = 0;i < *col * *row;i++)
		scanf("%d", &(*image)[i]);
}
void encode(int col, int row, int v_max, int image[], int key) {
	int i;
	srand2166(key);
	for (i = 0;i < row*col;i++)
		image[i] = (image[i] + (rand2166() % (v_max + 1))) % (v_max + 1);
}
void decode(int col, int row, int v_max, int image[], int key, int decoded[]) {
	int i;
	srand2166(key);
	for (i = 0;i < row*col;i++)
		decoded[i] = (image[i] - (rand2166() % (v_max + 1)) + (v_max + 1)) % (v_max + 1);
}
void decode_in_loco(int col, int row, int v_max, int image[], int key) {
	int i;
	srand2166(key);
	for (i = 0;i < row*col;i++)
		image[i] = (image[i] - (rand2166() % (v_max + 1)) + (v_max + 1)) % (v_max + 1);
}
void decode_brute_force(int col, int row, int v_max, int image[], int max_key) {
	int key, best_key = 0, decoded[MIN_PIXELS];
	double H, H_min = entropy(v_max, col*row, image);
	for (key = 0; key < max_key; key++) {
		decode_fast(v_max, image, key, decoded);
		H = entropy(v_max, MIN_PIXELS, decoded);
		if (H < H_min) {
			H_min = H;
			best_key = key;
		}
	}
	decode_in_loco(col, row, v_max, image, best_key);
}
double entropy(int v_max, int N, int image[]) {
	int i, *f;
	double H = 0.0, p;
	f = malloc(v_max * (sizeof *f));
	for (i = 0;i < v_max;i++)
		f[i] = 0;
	for (i = 0;i < N;i++)
		f[image[i]]++;
	for (i = 0;i < v_max;i++) {
		if (f[i] > 0) {
			p = (double) f[i]/N;
			H += p * log(1.0/p);
		}
	}
	free(f);
	return H;
}
int rand2166f(int seed) {
	static long r;
	if (seed >= 0) {
	r = seed;
	return 0;
	}
	r = (r * AA) % MM;
	return r;
}
void decode_fast(int v_max, int image[], int key, int decoded[]) {
	int i;
	srand2166(key);
	for (i = 0; i < MIN_PIXELS;i++)
		decoded[i] = (image[i] - (rand2166() % (v_max + 1)) + (v_max + 1)) % (v_max + 1);
}