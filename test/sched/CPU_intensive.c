#include <minix/syslib.h>
#include <minix/gpio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

int main(void)
{
	//int b;
	//int parent = getpid();
	//b = fork();
	//if (b != 0)
	//// Child process
	//{
	//	getchar();
	//}
	//else
	//{
		int n = 10000;
		int i = 3;
		int count, c;

		for (count = 2; count <= n; )
		{
			for (c = 2; c <= i - 1; c++)
			{
				if (i%c == 0)
					break;
			}
			if (c == i)
			{
				count++;
			}
			i++;
		}

		_exit(EXIT_SUCCESS);
	//}
}