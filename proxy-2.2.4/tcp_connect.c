#include "proxy.h"

int
tcp_connect(const char *host, const char *serv)
{
  int sockfd, n;
  struct addrinfo hints, *res, *ressave;

  /* 
   * Initialize addrinfo struct, and specify a socket 
   * family and a socket type for our proxy connection.
   */
  bzero(&hints, sizeof(struct addrinfo));
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;

  if ( (n = getaddrinfo(host, serv, &hints, &res)) != 0) {
    syslog(LOG_ERR, "tcp_connect error for %s, %s", host, serv);
  }

  ressave = res;

  /* 
   * Loop through, calling socket and connect for each IP, creating
   * a linked list of addrinfo structures, once a successful connection
   * has been made, break out of loop. We then free memory and return
   * a socket descriptor.
   */
  do {
    sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if (sockfd < 0)
      continue;

    if (connect(sockfd, res->ai_addr, res->ai_addrlen) == 0)
      break;	/* Break on success */

   close(sockfd);
  } while ( (res = res->ai_next) != NULL); /* Build linked list */

  if (res == NULL) {
    syslog(LOG_ERR, "tcp_connect error for %s, %s", host, serv);
  }

  freeaddrinfo(ressave);
  return (sockfd);
}
