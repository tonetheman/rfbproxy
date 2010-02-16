
#include "rfbp.h"

#include <iostream>

using std::cout;
using std::endl;
using std::cerr;

extern int tcp_connect(const char * host, const char * serv);
extern int tcp_listen(const char * host, const char * serv, 
	socklen_t * addrlenp);

struct AppOptions {
	bool nodaemon;
	char * destip;
	char * destport;
	char * srcip;
	char * srcport;

	AppOptions() {
		nodaemon = false;
		destip = destport = 0;
		srcip = srcport = 0;
	}
};

struct Proxy {
};

static struct option const long_opts[] = {
	{0,0,0,0}
};

void application_shutdown(int sig) {
	pthread_exit(0);
}

void usage() {
	cout << "rfbp some stuff" << endl;
	exit(-1);
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

	cout << "after setting signal" << endl;

	AppOptions opts;
	parse_args(argc, argv, opts);

	cout << "after parse args" << endl;

	int listenfd = -1;
	socklen_t addrlen;
	if (opts.srcip) {
		listenfd = tcp_listen(opts.srcip, opts.srcport, &addrlen);
	} else {
		listenfd = tcp_listen(0, opts.srcport, &addrlen);
	}

	struct sockaddr* cliaddr = 0;
	if ((cliaddr = (struct sockaddr*)malloc(addrlen)) == 0) {
		cerr << "memory error" << endl;
	}

	socklen_t clilen;
	Proxy* ptr = 0;
	int connfd = -1;
	for(;;) {
		ptr = (struct Proxy*)malloc(sizeof(Proxy));
		clilen = addrlen;
		connfd = accept(listenfd, cliaddr, &clilen);
		if (connfd==-1) {
			continue;
		}
	}

	return 0;
}
