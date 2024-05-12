/***************************************************************/
/**                                                           **/
/**   Henrique Schneider Marx                    14578432     **/
/**   Exercicio-Programa 2                                    **/
/**   Professora Cristina Gomes Fernandes                     **/
/**   Turma: 02                                               **/
/**                                                           **/
/***************************************************************/

#include<stdio.h>
#include<math.h>
void read_data(double *x0, double *x1, double *x2, double *x3, double *v0, double *v1, double *v2, double *v3, double *m0, double *m1, double *m2, double *m3, double *T_max) {
	scanf("%lf%lf%lf%lf%lf%lf%lf%lf%lf%lf%lf%lf%lf", x0, v0, m0, x1, v1, m1, x2, v2, m2, x3, v3, m3, T_max);
}
double t(double x, double xx, double v, double vv) {
	double dt;
	if (vv - v < 0) {
		dt = (xx - x - 0.1)/(vv - v);
		if (dt < 0)
			return -dt;
		else
			return dt;
	} else
		return HUGE_VAL;
}
double min(double a, double b, double c, int *i) {
	double m;
	if (a <= b && a <= c) {
		m = a;
		*i = 1;
	} else if (b <= a && b <= c) {
		m = b;
		*i = 2;
	} else {
		m = c;
		*i = 3;
	}
	return m;
}
double adv(double *x, double v, double t) {
	*x += v * t;
	if (v < 0)
		return - v * t;
	else
		return v * t;
}
void resolve(double *v, double *vv, double m, double mm) {
	double A = (2 * ((m * (*v)) + (mm * (*vv))))/(m + mm);
	*v = A - *v;
	*vv = A - *vv;
}
void print_data(long c1, long c2, long c3, double x0, double x1, double x2, double x3, double v0, double v1, double v2, double v3, double d0, double d1, double d2, double d3) {
	printf("Numero de colisoes por bloco: %ld %ld %ld\nNumero total de colisoes: %ld\nColisoes dos dois blocos a direita: %ld\nx0 = %f v0 = %f d0 = %f\nx1 = %f v1 = %f d1 = %f\nx2 = %f v2 = %f d2 = %f\nx3 = %f v3 = %f d3 = %f\n", c1, c2, c3, c1+c2+c3, c2+c3, x0, v0, d0, x1, v1, d1, x2, v2, d2, x3, v3, d3);
}
int main() {
	double x0, x1, x2, x3, v0, v1, v2, v3, m0, m1, m2, m3, d0, d1, d2, d3, T_max, T = 0.0, dt = 0.0;
	long c1, c2, c3;
	int i = 0;
	c1 = c2 = c3 = d0 = d1 = d2 = d3 = 0;
	read_data(&x0, &x1, &x2, &x3, &v0, &v1, &v2, &v3, &m0, &m1, &m2, &m3, &T_max);
	while (T < T_max) {
		dt = min(t(x0, x1, v0, v1), t(x1, x2, v1, v2), t(x2, x3, v2, v3), &i);
		if (dt == HUGE_VAL) {
			dt = T_max - T;
			i = 0;
		}
		T += dt;
		d0 += adv(&x0, v0, dt);
		d1 += adv(&x1, v1, dt);
		d2 += adv(&x2, v2, dt);
		d3 += adv(&x3, v3, dt);
		if (i == 1) {
			resolve(&v0, &v1, m0, m1);
			c1++;
		}
		if (i == 2) {
			resolve(&v1, &v2, m1, m2);
			c2++;
		}
		if (i == 3) {
			resolve(&v2, &v3, m2, m3);
			c3++;
		}
	}
	print_data(c1, c2, c3, x0, x1, x2, x3, v0, v1, v2, v3, d0, d1, d2, d3);
	if (i != 0)
		printf("Ha colisoes remanescentes\n");
	else
		printf("Nao ha mais colisoes\n");
	return 0;
}