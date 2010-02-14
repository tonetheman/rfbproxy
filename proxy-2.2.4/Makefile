# For debugging...
#CFLAGS=-D_REENTRANT -Wall -ggdb -DDEBUG

CFLAGS=-D_REENTRANT -Wall -O6
LIBS=-lpthread

# LIBS for a non posix OS, like Solaris...
#LIBS=-lpthread -lsocket -lresolv -lnsl -L./unpv12e -lunp
   
all: proxy

proxy:  tcp_listen.o tcp_connect.o sock_ntop.o proxy.o proxy.h
	gcc $(CFLAGS) $(LDFLAGS) -o $@ $@.o tcp_listen.o tcp_connect.o sock_ntop.o $(LIBS)
	strip $@   
clean: 
	rm -f *~ *.o proxy
