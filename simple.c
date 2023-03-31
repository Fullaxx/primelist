#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>

static void print_all(mpz_t p)
{
	mpz_t i;
	mpz_init_set_ui(i, 1);

	/* Endless Loop */
	while(1) {
		mpz_nextprime (p, p);
		mpz_add_ui(i, i, 1);
		gmp_printf("%Zd: %Zd\n", i, p);
	}
	/*mpz_clear(i);*/
}

static void print_this_many(mpz_t p, unsigned long count)
{
	unsigned long i = 0;

	while(i < count) {
		mpz_nextprime (p, p);
		gmp_printf("%lu: %Zd\n", ++i, p);
	}
}

int main(int argc, char *argv[])
{
	mpz_t p;
	int err = 0;
	char *start_p = getenv("START_P");

	if(start_p) { err = mpz_init_set_str(p, start_p, 10); }
	else { mpz_init_set_ui(p, 1); }

	if(err) { fprintf(stderr, "mpz_init_set_str(p, %s) failed!\n", start_p); exit(1); }

	unsigned long count = 0;
	if(argc == 2) { count = strtoul(argv[1], NULL, 10); }

	if(count == 0) { print_all(p); }
	else { print_this_many(p, count); }

	mpz_clear(p);
	return 0;
}
