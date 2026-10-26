#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

static unsigned fib(unsigned n) {
	if (n == 0)
		return 0;
	else if (n == 1)
		return 1;
	else
		return fib(n - 1) + fib(n - 2);
}

static void usage(void)
{
	fprintf(stderr, "usage: c_fib [OPTIONS]\n\
OPTIONS:\n\
   -h     -- display this screen\n\
   -n <num>     -- calculate Fib(n), the default is 28\n\
   -c <count>   -- repeat calculation count times, the default is 1000\n\
\n\
Examples:\n\
   $ c_fib -c1 -n 5\n\
   $ c_fib -c2 -n 28\n\
");
}

int main(int argc, char** argv)
{
	int opt;

	int n = 28;
	int count = 1000;
	int i;

	while ((opt = getopt(argc, argv, "+c:hn:r:s:t")) != -1) {
		switch (opt) {
			case 'h':
				usage();
				exit(0);
			case 'c':
				count = atoi(optarg);
				break;
			case 'n':
				n = atoi(optarg);
				break;
			default:
				usage();
				exit(1);
		}
	}

	for (i = 0; i < count; ++i) {
		printf("%u\n", fib(n));
	}
	return 0;
}
