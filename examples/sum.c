#include<stdio.h>
#include<stdlib.h>
#include<syscall.h>

void main(int argc, char *argv[])
{
	printf("%d ",pibonacci(atoi(argv[2])));
	printf("%d\n",sum_of_four_integers(atoi(argv[2]),atoi(argv[3]),atoi(argv[4]),atoi(argv[5])));
}
