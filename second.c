#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
	int fd3, fd4;
	int words, lines, characters, len, i;
	char ch;
	FILE *fp;

	// FIFO file path
	const char *FIFO1 = "FIFO1";
	const char *FIFO2 = "FIFO2";

	// Creating the named file(FIFO)
	// mkfifo(<pathname>, <permission>)
	mkfifo(FIFO1, 0666);
	mkfifo(FIFO2, 0666);
	char str1[80];
	while (1)
	{
		// First open in read only and read
		fd3 = open(FIFO1, O_RDONLY);
		read(fd3, str1, 80);

		// Print the read string and close
		printf("User1: %s\n", str1);
		len = strlen(str1);
		words = 0;
		lines = 0;
		characters = 0;
		for (i = 0; i < len; i++)
		{
			if (str1[i] == ' ' || str1[i] == '.')
				words++;
			if (str1[i] == '.')
				lines++;
		}
		characters = (strlen(str1)) - 1;

		close(fd3);

		// Now open in write mode and write
		// string taken from the user.
		fp = fopen("a.txt", "w+");
		fprintf(fp, "\nNo. of Lines are: %d\n", lines);
		fprintf(fp, "\nNo. of words are: %d\n", words);
		fprintf(fp, "\nNo. of characters are: %d\n", characters);

		fclose(fp);
		close(fd3);

		fd4 = open(FIFO2, O_WRONLY);
		system("cat a.txt > FIFO2");
		close(fd4);
	}
	return 0;
}

