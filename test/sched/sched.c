#include <minix/syslib.h>
#include <minix/gpio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
	int b;
	b = fork();
	if (b != 0)
	{
		printf("Starting CPU intensive process on %d...\n", b);
		clock_t start = clock();
		clock_t diff;

		int n = 10000;
		int i = 3;
		int count, c;

		if (n >= 1)
		{
			printf("First %d prime numbers are :\n", n);
			printf("2\n");
		}

		for (count = 2; count <= n; )
		{
			for (c = 2; c <= i - 1; c++)
			{
				if (i%c == 0)
					break;
			}
			if (c == i)
			{
				//printf("%d\n", i);
				count++;
			}
			i++;
		}

		diff = clock() - start;
		printf("The CPU computation took %d.\n", diff);
		exit(EXIT_SUCCESS);
	}

	b = fork();
	if (b != 0)
	{
		printf("Starting I/O intensive process on %d...\n", b);
		clock_t start = clock();

		FILE *fp, *fp2, *fpout;
		char *line = NULL;
		size_t len = 0;
		ssize_t read;
		int sum;

		fpout = fopen("./dataout.txt", "w+");
		fp1 = fopen("./data1.txt", "r+");


		if (fpout == NULL || fp1 == NULL || fp2 == NULL)
		{
			printf("One of the files could not be opened.\n");
			exit(EXIT_FAILURE);
		}

		for (int i = 0; i < 10000; i++)
		{
			if (i % 2)
				fp = fopen("./data1.txt", "r+");
			else
				fp = fopen("./data2.txt", "r+");
			read = getline(&line, &len, fp);
			sum += atoi(line);
			fprintf(fpout, "%d\n", sum);
		}

		clock_t diff = clock() - start;
		printf("The I/O computation took %d.\n", diff);
		exit(EXIT_SUCCESS);
	}
}