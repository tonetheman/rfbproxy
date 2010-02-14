INTRODUCTION 
Proxy is a C application that when run on a multi-homed host will forward
all packets from source, to destination. Where source might be a system on
the Internet, and destination might be a box on a private network behind a
multi-homed Linux machine. The way I use it is to change the telnet port on
a machine on my internal network from 23 to 999, then I'll run the proxy on
the multi-homed box, and from the Internet, telnet to the multi-homed box
on port 999 and it will automagically put me on the internal machine.

client			proxy_server		Telnet Server
+----------+		+----------+		+----------+
| Internet |- - - >	|     |    |- - - >	| Real     |
| Host	   | telnet	|NIC1 |NIC2|     23	| telnet   |
|          |  999	|     |    |		| server   |
+----------+		+----------+		+----------+
0.0.0.0/0      		192.*   10.*    	10.*

The arguments to proxy when run on the multi-homed host would be:

proxy -s 999 -D internal.private.net -d 23

For a complete list of options to proxy, run 'proxy --help'.

This tells proxy to accept connections on port 999 and send them to the
internal machine on port 23. This example shows the power of proxy, you can
also use it to set up an internal web server, or mail server, etc, etc...
without having any of the machines connected to the net except for the
multi-homed box.

You can use an optional 4-th parameter (-S) to tell proxy which one of
machine's assigned IP's bind to. If this is omitted, proxy will bind to all
of the addresses. This may be useful if you want the proxied port to only
be visible to localhost or to serve requests for different IP addresses
(but the same port) differently. This will also let you choose a different
destination port.

FILTERING 
Proxy-2.2.4 can also do filtering. In order to take advantage of the
filtering rules of proxy-2.2, you must make a config file. The file will
reside in the /etc directory and it will be called "proxy.filters"
(i.e. /etc/proxy.filters).  The filter file can contain comments, only if
the first character of the line starts with the pound sign '#'. Example:

Example 1:
# This is a proper comment. (correct)

Example 2:
DENY.209.209.123.12 # DENY this host (Not correct)

The first example is a correct comment, the second isn't. 

The filters file can be setup with a default policy for either accept or
deny.  If a default policy of deny is chosen, then all traffic that hasn't
been specifically allowed, will be denied. By contrast, if a default policy
of accept is given, all traffic that isn't specifically denied will be
allowed.

proxy filters are to be written as 'rule.ip', here is an example:

ACCEPT.127.0.0.1
DENY.127.0.0.1

Please note that names are not allowed, so:

DENY.localhost 

will _not_ work.

There is no order in which filter rules have to be written, this means that
the default policy could be at the top, middle or bottom of the file. The
default policy must be written on a line by itself terminated by a
semi-colon, example:

ACCEPT;

or

DENY; 

Alternatively, if there is no filters file in place, all connections will
be allowed. Please see the file called "proxy.filters_example" in this
directory for more detail.

CHANGES 
Proxy 2.2.4 changes include: 
	+ Use pthread_detach to detach threads...
	+ For some reason, creating your thread in a detached state is not
	the same as calling pthread_detach() after calling pthread_create().
	I can now create more than 1024 threads, things are good again...
	+ I have written a small Perl app that can be used to stress test
	proxy. Basically, you call it like so:

	./proxy -s <port> -d 80 -D some.web.server -n
	./regress server port #

	where server is the server running proxy, port is the port proxy is
	listening on, and # is the number of connections you want to make to
	proxy.

	Things are very stable now, and proxy can be considered for use in
	production environments.

AUTHOR
Proxy was written and is maintained by Sonny Parlin.

CONTRIBUTERS
Dmitri E. Kalintsev: dek@hades.uz
Added extra parameter for specifying source IP for binding.

LICENSE 
This program is free software; you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the Free
Software Foundation; either version 2 of the License, or any later version.

This program is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
more details.

You should have received a copy of the GNU General Public License along
with this program; if not, write to the Free Software Foundation, Inc., 59
Temple Place - Suite 330, Boston, MA 02111-1307, USA.
