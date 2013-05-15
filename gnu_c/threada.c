#include <pthread.h>
#include <stdio.h>
void *thread_func(void *arg)
{
	int i = 0x00000001;
	char b = (char)0x01;

	int r = i & b;
	printf("sizeof(int) is r is  %0x \n", r);

	short int x;
	x=0x0100;
	char *p[2];
	//p = (char *)&x; 
	char bc = *(p[0]);
	printf("content of low address x %0x", bc); 
	printf("thread a started... \n");
	return ( (void *) 0);
}
	pthread_t p;
void start_threada()
{
	
	int result;
	result = pthread_create(&p, NULL, thread_func, NULL);
	if (result == 0 ){
		printf("thread create successfully. \n ");
	} else {
		printf("thread create failed. \n " );
	}
}
