/***************************************************************/
/**                                                           **/
/**   Henrique Schneider Marx                    14578432     **/
/**   Exercicio-Programa 1-b                                  **/
/**   Professora Cristina Gomes Fernandes                     **/
/**   Turma: 02                                               **/
/**                                                           **/
/***************************************************************/

#include<stdio.h>
int main() {
	int n, opcao, f1, f2, f3, x;
	scanf("%d", &opcao);
	scanf("%d", &n);
	if (opcao == 0 || opcao == 1) {
		while (n != 0) {
			f1 = f2 = 1;
			f3 = 2;
			x = 1;
			while (f3 <= n) {
				f1 = f2;
				f2 = f3;
				f3 = f2 + f1;
				x++;
			}
			while (n > 0 || f3 != 1) {
				if (f2 <= n) {
					n -= f2;
					if (opcao == 0)
						printf("1");
					if (opcao == 1)
						printf("F_%d (%d)", x, f2);
				} else if (opcao == 0)
					printf("0");
				f3 = f2;
				f2 = f1;
				f1 = f3 - f2;
				x--;
				if (opcao == 1 && n != 0 && f2 <= n)
					printf(" + ");
			}
			printf("\n");
			scanf("%d", &n);
		}
	}
	if (opcao == 2) {
		while (n != 0) {
			f1 = x = 0;
			f2 = 1;
			while (n != 0) {
				f3 = f2 + f1;
				f1 = f2;
				f2 = f3;
				if (n % 10 == 1)
					x += f2;
				n /= 10;
			}
			printf("%d\n", x);
			scanf("%d", &n);
		}
	}
	return 0;
}