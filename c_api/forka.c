#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include </home/tongchuhuozhai/learn1/c_api/threada.h>
#include <stdarg.h>
#include <string.h>
#include <fcntl.h>

void var_multi(const char* p, ...)
{
	char *p1 = 0;

	// last fixed para
	printf("%s\n", p);

	// declare pointer
	va_list p_list;

	// define pointer
	va_start(p_list, p);

	// second variable para
	p1 = va_arg(p_list, char*);
	printf("%s\n", p1);
	
	// third variable para
	p1 = va_arg(p_list, char*);
	printf("%s\n", p1);


	va_end(p_list);
}

void file_t()
{
	int fd = open("/tmp/file_test_a", O_WRONLY | O_CREAT);
	char a[] = "data";
	write(fd, a, sizeof(a));
	close(fd);

	char buffer[10];
	fd = open("/tmp/file_test_a", O_RDONLY);
	read(fd, buffer, 3);
	close(fd);
	printf("%s\n", buffer);

}

int main()
{
	pid_t pid = fork();
	if( pid == 0 ) {
		printf("sub process beging... \n ");
		// define the vector of command parameters
		char *v[] = {"ls", "-l", NULL};

		// define enviroment varialbles 
		char *e[] = {"PATH=/bin/ls", NULL};

		execve("/bin/ls", v, e);

		// why it doesn't print
		printf("sub process end. " );

	} else if ( pid != 0 ) {
		printf("parent process begin...\n " ); 
		waitpid(pid, NULL, 0); 
		printf("parent process receive msg that sub process exit. \n" ); 
		start_threada();
		var_multi("para1", "para2", "para3");
		file_t();
   	}
}
