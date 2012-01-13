#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <unistd.h>

int main()
{
	// define socket address
	struct sockaddr_in sockaddra;
	sockaddra.sin_family=AF_INET;
	sockaddra.sin_port=0; //htons(20);
	sockaddra.sin_addr.s_addr=INADDR_ANY;

	// define socket file descriptor
	int socket_fd = socket(AF_INET, SOCK_STREAM, 0); 


	bind(socket_fd, (struct sockaddr *) &sockaddra, sizeof(sockaddra));

	listen(socket_fd, 10);

	struct sockaddr_in client_addr;
	while(1)
	{
		int s = sizeof(struct sockaddr);
		int connect_socket_fd = accept(socket_fd, (struct sockaddr *) &client_addr, (int *) &s);

		char buf[1024];

		int result = recv(connect_socket_fd, buf, 1024, MSG_OOB);

		printf("buf is %s, ", buf);
	}
}
