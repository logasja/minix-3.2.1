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
		printf("Starting CPU intensive process...\n");
		clock_t start = clock();
		clock_t diff;

		int n = 10;
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
				printf("%d\n", i);
				count++;
			}
			i++;
		}

		diff = clock() - start;
		printf("The CPU computation took %d.", diff);
		exit();
	}

	b = fork();
	if (b != 0)
	{
		printf("Starting I/O intensive process...\n");
		start = clock();

		FILE *fp;
		FILE *fpout;
		char *line = NULL;
		size_t len = 0;
		ssize_t read;
		int sum;

		fp = fopen("./data.txt", "r+");
		fpout = fopen("./dataout.txt", "w+");

		if (fp == NULL || fpout == NULL)
		{
			printf("One of the files could not be opened.\n");
			exit(EXIT_FAILURE);
		}

		while ((read = getline(&line, &len, fp)) != -1) {
			sum += atoi(line);
			fprint(fpout, "%d", sum);
		}

		fprintf(fp, "SUM: %d", sum);

		diff = clock() - start;
		printf("The computaion took %d.", diff);
		exit();
	}
}