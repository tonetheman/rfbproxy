#include "proxy.h"

#define LISTENQ 1024 

int
tcp_listen (const char *host, const char *serv, socklen_t * addrlenp)
{
  int listenfd, n;
  const int on = 1;
  struct addrinfo hints, *res, *ressave;

  bzero (&hints, sizeof (struct addrinfo));
  hints.ai_flags = AI_PASSIVE;
  hints.ai_socktype = SOCK_STREAM;

  if ((n = getaddrinfo (host, serv, &hints, &res)) != 0)
    {
      syslog(LOG_ERR, "tcp_listen error for %s, %s", host, serv);
    }

  ressave = res;

  do
    {
      listenfd = socket (AF_INET, res->ai_socktype, res->ai_protocol);
      if (listenfd < 0)
	continue;

      if (setsockopt (listenfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof (on)) != 0)
	{
	  syslog(LOG_ERR, "setsockopt error %m");
	}

      if (bind (listenfd, res->ai_addr, res->ai_addrlen) == 0)
	break;			/* success */

      close (listenfd);
    }
  while ((res->ai_next) != NULL);

  if (res == NULL)
    {
      printf ("tcp_listen error for %s, %s", host, serv);
      exit (1);
    }

  if (listen (listenfd, LISTENQ) != 0)
    {
      syslog(LOG_ERR, "listen error %m");
    }

  if (addrlenp)
    *addrlenp = res->ai_addrlen;	/* return size of protocol address */

  freeaddrinfo (ressave);

  return (listenfd);
}
