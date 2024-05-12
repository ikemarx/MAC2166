/***************************************************************/
/**                                                           **/
/**   Henrique Schneider Marx                    14578432     **/
/**   Exercicio-Programa 1-a                                  **/
/**   Professora Cristina Gomes Fernandes                     **/
/**   Turma: 02                                               **/
/**                                                           **/
/***************************************************************/

#include<stdio.h>
int main() {
	int base3, base10, pot, resto;
	scanf("%d", &base3);
	while(base3 != 0) {
		pot = 1;
		base10 = 0;
		while (base3 != 0) {
			resto = base3 % 10;
			base10 += resto * pot;
			pot *= 3;
			base3 /= 10;
		}
		printf("%d\n", base10);
		scanf("%d", &base3);
	}
	return 0;
}