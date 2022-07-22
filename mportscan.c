/*
 mportscan Copyright (C) <2016> <matthias holl>

 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>



 mportscan.c

 port scanner

 by mah00

 www.mahoosoft.com

 linux:

 gcc -o mportscan mportscan.c

 sudo ./mportscan

 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>

int main(int argc, char *argv[]) {
	int mahoosocket, port;
	struct hostent *mh;

	printf("mportscan:\n");
	if (argc != 2) {
		fprintf(stderr, "usage: client hostname\n");
		exit(1);
	}

	if ((mh = gethostbyname(argv[1])) == NULL) {
		perror("gethostbyname");
		exit(1);
	}
	for (port = 0; port <= 65000; port++) {
		struct sockaddr_in mahoodestaddr;
		if ((mahoosocket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
			perror("socket");
			exit(1);
		}

		mahoodestaddr.sin_family = AF_INET;
		mahoodestaddr.sin_port = htons(port);
		mahoodestaddr.sin_addr = *((struct in_addr *) mh->h_addr);
		memset(&(mahoodestaddr.sin_zero), '\0', 8);

		if (connect(mahoosocket, (struct sockaddr *) &mahoodestaddr,
				sizeof(struct sockaddr)) == -1) {
			close(mahoosocket);
		} else {
			printf("%i open\n", port);
			close(mahoosocket);
		}
	}
}
