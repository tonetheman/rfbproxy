
#include <pthread.h>
#include <signal.h>
#include <getopt.h>

#include <iostream>

struct AppOptions {
	bool nodaemon;
	char * destip;
	char * destport;
	char * srcip;
	char * srcport;
};

static struct option const long_opts[] = {
	{0,0,0,0}
};

void application_shutdown(int sig) {
	pthread_exit(0);
}

void usage() {
}

void parse_args(int argc, char* argv[], AppOptions & opts) {
	int c;
	while((c=getopt_long(argc,argv,"ns:S:d:D:", long_opts, 0))!= -1) {
		switch(c) {
			case 0:
				break;
			case 'n':
				opts.nodaemon = true;
				break;
			case 's':
				opts.srcport = optarg;
				break;
			case 'd':
				opts.destport = optarg;
				break;
			case 'D':
				opts.destip = optarg;
				break;
			case 'S':
				opts.srcip = optarg;
				break;
			default:
				usage();
				break;
		}
	}
}

int main(int argc, char* argv[]) {

	signal(SIGINT, application_shutdown);

	AppOptions opts;
	parse_args(argc, argv, opts);

	return 0;
}
