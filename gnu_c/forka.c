#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include "./threada.h"
#include <stdarg.h>
#include <string.h>
#include <fcntl.h>


#define printf_d(str1,str2...) printf(str1,##str2)
void var_multi(const char* p, ...)
{
	char *p1 = 0;

	// last fixed para
	printf("%s\n", p);

	// declare pointer
	va_list p_list;

	// define pointer, point to last fixed parameter
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

	//
	test_const();

	test_enum();

	test_snprintf();

	test_if_likely();

	test_define();
}
void test_define(){
	
	printf("\n <------------ test define  ---------------- > \n");
	printf_d("test %d \n", 1);
        printf_d("test## \n");
}

void test_if_likely(){
	printf("\n <------------ enum if likely ---------------- > \n");
	if(!1){
		printf("if it is bigger than 0 , it is true \n");	
	}
	if(-1){
		printf("if it is less than 0 , it is true \n");	
	}
	
	if(0){
	}else{
		printf("if it is 0, it is false\n");
	}


	if( 1 ) { // likely(1)){
		printf("likely help compiler to optimize, which \n");	
	}
}
void test_enum()
{
	enum ren {zhongshengren, wushengren};
	enum ren ren1;
	ren1 = zhongshengren;
	printf("\n <------------ enum learn ---------------- > \n");
	printf("the valude of enum variable is %d \n ", ren1);

	ren1 = 0; // 不必转型
	int i = 0;
	switch (i){
	case zhongshengren:
		printf("the defalut valude of first element in enum set is %d \n ", zhongshengren);
		break;
	case wushengren:
		printf("the defalut valude of second element in enum set is %d \n ", wushengren);
		break;
	default:
		break;
	}

}
void test_const()
{
	printf("\n <------------ const learn ---------------- > \n");
	char *p = "adfd";
	//p[0] = 'b'; p指向一个内存中的只读区域，这里p[0] = 'b', 修改只读区域，报段错误
	char c[4]= "abc";
	//const (char *) p1;
	const char *p1;
	p1 = p;
	p1++;
	char* const ps;
	// ps++; const在＊的左边，表示该指针不能变，不是指针所指向的东西不能变，即指针不能自增。
	//const (char*) ps;
}

void test_snprintf()
{
	printf("\n <------------ snprintf learn ---------------- > \n");
	char s[10] = "1234567890";
	char *p = "abc";
	strcpy(s, p);
	printf("test strcpy \t dest mem contains : %s \n", s);

	char n1[100];
	snprintf(n1, 15, "abc%d%s", 3,  "efg");
	printf("\n n1 : %s \n", n1);
}
int main()
{
	pid_t pid = fork();
	if( pid == 0 ) {
		char a = '0';
		printf("char 0 assic :%d \n", a);
		printf("char 1 assic : 0x%0X\n ", a);
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

