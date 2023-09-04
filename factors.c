#include <stdio.h>
#include <stdlib.h>
/**
void factorize(int n)
{
	int factor = 2;

	printf("%d=", n);

	while (n > 1)
	{
		if (n % factor == 0)
		{
			printf("%d", factor);
			n /= factor;
			if (n > 1)
			{
				printf("*");
			}
		}
		else
		{
			factor++;
		}
	}

	printf("\n");
}
*/

void factorize(int n)
{
	if (n <= 1)
	{
		printf("%d=%d*%d\n", n, n, 1);
		return;
	}

	int factor1 = 1;
	int factor2 = n;

	for (int i = 2; i * i <= n; i++)
	{
		if (n % i == 0)
		{
			factor1 = i;
			factor2 = n / i;
			break;
		}
	}

	printf("%d=%d*%d\n", n, factor2, factor1);
}
int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		printf("Usage: %s <file>\n", argv[0]);
		return (1);
	}

	char *input_file = argv[1];
	FILE *file = fopen(input_file, "r");

	if (file == NULL)
	{
		printf("File not found: %s\n", input_file);
		return (1);
	}

	char line[1024];

	while (fgets(line, sizeof(line), file))
	{
		int n = atoi(line);
		factorize(n);
	}

	fclose(file);
	return (0);
}
