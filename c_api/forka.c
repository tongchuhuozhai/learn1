#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include "./threada.h"
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

void copy_string(char *source, char *dest, int size){
	int i; 
	for(; i<size; i++){
		*dest = *source;	
		dest++;
		source++;
	}	
}

void file_t()
{
	int fd = open("/tmp/file_test_a", O_WRONLY | O_CREAT);
	char a[] = "data";
	write(fd, a, sizeof(a));
	close(fd);

	//
	char *source, *dest;
	source = "this is string";
	dest = (char *)malloc(sizeof(char)*6);
	copy_string(source, dest, 5);
	printf("\n<-------------copy string function----------------->\n");
	printf("source string is : %s, \ndest string copied is : %s", source, dest);

	// 
	char buffer[10];
	fd = open("/tmp/file_test_a", O_RDONLY);
	read(fd, buffer, 3);
	close(fd);
	printf("\n%s\n", buffer);
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

		goto code1;

	} else if ( pid != 0 ) {
		printf("parent process begin...\n " ); 
		waitpid(pid, NULL, 0); 
		printf("parent process receive msg that sub process exit. \n" ); 
		start_threada();
		var_multi("para1", "para2", "para3");
		file_t();
   	}

code1 : 
	{
		int i = 1;
		volatile int *p = &i;
		*p = 1;
		*p = 2;
		printf("volatile means the content of address p(%0x) change easily, whicn keep *p from compiler optimization(that is *p =2). \n ", p);
	}
}
