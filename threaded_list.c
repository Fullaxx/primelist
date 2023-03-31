#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>
#include <signal.h>
#include <gmp.h>

/*
static void alarm_handler(int signum)
{
	(void) alarm(1);
}
*/

int g_shutdown = 0;
static void sig_handler(int signum)
{
	switch(signum) {
		case SIGHUP:
		case SIGINT:
		case SIGTERM:
		case SIGQUIT:
			g_shutdown = 1;
			break;
	}
}

static void* search_loop(void *param)
{
	int err = 0;
	mpz_t i, p;
	mpz_init_set_ui(i, 1);

	char *start_p = getenv("START_P");
	if(start_p) { err = mpz_init_set_str(p, start_p, 10); }
	else { mpz_init_set_ui(p, 1); }

	if(err) { fprintf(stderr, "mpz_init_set_str(p, %s) failed!\n", start_p); g_shutdown = 1; }

	while(g_shutdown == 0) {
		mpz_nextprime (p, p);
		mpz_add_ui(i, i, 1);
		gmp_printf("%Zd: %Zd\n", i, p);
	}
	mpz_clear(i);
	fflush(stdout);
	return NULL;
}

static inline void holding_pattern(void)
{
#ifdef _DEFAULT_SOURCE
	usleep(1000);
#else
	sleep(1);
#endif
}

int main(int argc, char *argv[])
{
	int err;
	void *ret;
	pthread_t thr_id;
	pthread_attr_t attr;

	err = pthread_attr_init(&attr);
	if(err) { perror("pthread_attr_init()"); exit(1); }

	err = pthread_create(&thr_id, &attr, &search_loop, NULL);
	if(err) { perror("pthread_create()"); exit(2); }

#ifdef _GNU_SOURCE
	err = pthread_setname_np(thr_id, "search_loop");
	if(err) { perror("pthread_setname_np()"); }
#endif

	signal(SIGINT,  sig_handler);
	signal(SIGTERM, sig_handler);
	signal(SIGQUIT, sig_handler);
	signal(SIGHUP,  sig_handler);
/*
	signal(SIGALRM, alarm_handler);
	(void) alarm(1);
*/

	while(!g_shutdown) { holding_pattern(); }
	fflush(stdout);

	err = pthread_join(thr_id, &ret);
	if(err) { perror("pthread_join()"); }

#ifdef DEBUG
	if(ret != NULL) {
		fprintf(stderr, "search thread exited with '%s'\n", (char *)ret);
	}
#endif

	return 0;
}
