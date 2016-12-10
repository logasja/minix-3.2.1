#include <minix/syslib.h>
#include <minix/gpio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

int input[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

int main(void)
{
	//int b;
	//b = fork();
	//if (b != 0)
	//	// Child process
	//{
	//	getchar();
	//}
	//else
	//{
		FILE* fp = fopen("./data1.txt", "r+");
		FILE* fpout = fopen("./dataout2.txt", "w+");
		char *line = NULL;
		size_t len = 0;
		ssize_t read;
		int sum;
		// Read from file and do calculations on number in it
		for (int i = 0; i < 10000; i++)
		{
			read = getline(&line, &len, fp);
			sum += atoi(line);
			fprintf(fpout, "%d\n", sum);
		}

		fclose(fp);
	//}
}