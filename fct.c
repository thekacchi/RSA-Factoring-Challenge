#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gmp.h>

void factorize(char *n_str)
{
	mpz_t n, factor1, factor2;
	mpz_inits(n, factor1, factor2, NULL);

	mpz_set_str(n, n_str, 10);

	if (mpz_cmp_ui(n, 1) <= 0)
	{
		gmp_printf("%Zd=%Zd*%Zd\n", n, n, n);
		return;
	}

	mpz_set_ui(factor1, 1);
	mpz_set(factor2, n);

	mpz_t divisor;
	mpz_init(divisor);

	for (mpz_set_ui(divisor, 2); mpz_cmp(divisor, n) <= 0; mpz_add_ui(divisor, divisor, 1))
	{
		if (mpz_divisible_p(n, divisor))
		{
			mpz_set(factor1, divisor);
			mpz_divexact(factor2, n, divisor);
			break;
		}
	}

	gmp_printf("%Zd=%Zd*%Zd\n", n, factor2, factor1);

	mpz_clears(n, factor1, factor2, divisor, NULL);
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
		line[strcspn(line, "\n")] = '\0';
		factorize(line);
	}

	fclose(file);
	return (0);
}
