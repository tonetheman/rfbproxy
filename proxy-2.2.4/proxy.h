/*-----------------------------------------------*/
/* Universal header for network programming code */
/* Sonny Parlin 12/98				 */
/*-----------------------------------------------*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include <errno.h>
#include <signal.h>
#include <syslog.h>
#include <netdb.h>
#include <fcntl.h>
#include <sys/time.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <signal.h>
#include <ctype.h>
#include <getopt.h>

/* Define bzero() as a macro incase it's not in std C library */
#define bzero(ptr,n) memset(ptr, 0, n)

/* Miscellaneous constants */
#define MAXLINE         4096    /* max text line length */
#define MAXSOCKADDR  	128     /* max socket address structure size */
#define BUFFSIZE        8192    /* buffer size for reads and writes */

/* uncomment next line for non-posix compliant systems */
#define socklen_t unsigned int

/* Following shortens all the type casts of pointer arguments */
#define SA      struct sockaddr

/* Function declorations for proxy */
void Close(int descriptor);
void PrintUsage (int n);
void *proxy (void *ptr);
int GetLargestSocket(int sd1, int sd2);
int daemon_init (const char *pname, int facility);
int FilterIP (char *);
void finish (int sig);
int tcp_connect(const char *, const char *);
int tcp_listen(const char *, const char *, socklen_t *);
char *sock_ntop(const SA *, socklen_t);
char *Sock_ntop(const SA *, socklen_t);
