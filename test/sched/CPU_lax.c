#include <minix/syslib.h>
#include <minix/gpio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

int input[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

int main(void)
{
	int b;
	int parent = getpid();
	b = fork();
	if (b != 0)
		// Child process
	{
		getchar();
	}
	else
	{
		int value = 0;
		for (int i = 0; i < 10000; i++)
		{
			value *= input[i % 10];
		}
	}
}