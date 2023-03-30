#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>

unsigned long g_start_p = 1;

static void print_all(void)
{
	mpz_t i, p;
	mpz_init_set_ui(i, 1);
	mpz_init_set_ui(p, g_start_p);
	while(1) {
		mpz_nextprime (p, p);
		gmp_printf("%Zd: %Zd\n", i, p);
		mpz_add_ui(i, i, 1);
	}
}

static void print_this_many(unsigned long count)
{
	mpz_t p;
	unsigned long i = 1;
	mpz_init_set_ui(p, g_start_p);
	while(i <= count) {
		mpz_nextprime (p, p);
		gmp_printf("%lu: %Zd\n", i++, p);
	}
}

int main(int argc, char *argv[])
{
	char *start_p = getenv("START_P");
	if(start_p) { g_start_p = strtoul(start_p, NULL, 10); }

	unsigned long count = 0;
	if(argc == 2) { count = strtoul(argv[1], NULL, 10); }

	if(count == 0) { print_all(); }
	else { print_this_many(count); }

	return 0;
}
