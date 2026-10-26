#include <stdio.h>

static double fib(double n) {
	if (n == 0)
		return 0;
	else if (n == 1)
		return 1;
	else
		return fib(n - 1) + fib(n - 2);
}

int main(int argc, char** argv) {
	for (int i = 0; i < 1000; ++i) {
		printf("%g\n", fib(28));
	}
	return 0;
}
