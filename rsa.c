#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include <string.h>

//Miller Rabin primality test
int is_prime(mpz_t n, int k)
{
	if (mpz_cmp_ui(n, 2) < 0)
	{
		return (0);
	}
	if (mpz_cmp_ui(n, 2) == 0)
	{
		return (1);
	}
	if (mpz_even_p(n))
	{
		return (0);
	}

	mpz_t d, r, a, x, n_minus_1;
	mpz_inits(d, r, a, x, n_minus_1, NULL);
	mpz_sub_ui(n_minus_1, n, 1);

	mpz_set(d, n_minus_1);
	while (mpz_even_p(d))
	{
		mpz_div_ui(d, d, 2);
	}

	gmp_randstate_t state;
	gmp_randinit_mt(state);
	gmp_randseed_ui(state, rand());

	for (int i = 0; i < k; i++)
	{
		mpz_urandomm(a, state, n_minus_1);
		mpz_add_ui(a, a, 1); //Ensure 1 < a < n

		mpz_powm(x, a, d, n);
		if (mpz_cmp_ui(x, 1) == 0 || mpz_cmp(x, n_minus_1) == 0)
		{
			continue;
		}

		int is_composite = 1;
		for (mpz_set_ui(r, 1); mpz_cmp(r, n_minus_1) < 0; mpz_mul_ui(r, r, 2))
		{
			mpz_powm_ui(x, x, 2, n);
			if (mpz_cmp_ui(x, 1) == 0)
			{
				return 0;
			}
			if (mpz_cmp(x, n_minus_1) == 0)
			{
				is_composite = 0;
				break;
			}

		}

		if (is_composite)
		{
			return (0);
		}
	}

	mpz_clears(d, r, a, x, n_minus_1, NULL);
	gmp_randclear(state);
	return (1);
}

//Polland's Rho factorization algorithm
void pollards_rho(mpz_t n, mpz_t factor)
{
	mpz_t x, y, d;
	mpz_inits(x, y, d, NULL);

	mpz_set_ui(x, 2);
	mpz_set_ui(y, 2);
	mpz_set_ui(d, 1);

	while (mpz_cmp_ui(d,1) == 0)
	{
		mpz_t temp;
		mpz_inits(temp, NULL);

		mpz_sub(temp, x, y);
		mpz_abs(temp, temp);
		mpz_gcd(d, temp, n);

		mpz_mul(temp, x, x);
		mpz_add(temp, temp, n);
		mpz_mod(x, temp, n);

		mpz_mul(temp, y, y);
		mpz_add(temp, temp, n);
		mpz_mod(y, temp, n);

		mpz_clear(temp);
	}

	mpz_set(factor, d);

	mpz_clears(x, y, d, NULL);
}

void find_primes(char *n_str)
{
	mpz_t n, factor1, factor2;
	mpz_inits(n, factor1, factor2, NULL);
	mpz_set_str(n, n_str, 10);

	if (mpz_cmp_ui(n, 1) <= 0)
	{
		gmp_printf("%s=%s*%s\n", n_str, n_str, n_str);
	}
	else if (is_prime(n, 20))
	{
		gmp_printf("%s is prine\n", n_str);
	}
	else
	{
		pollards_rho(n, factor1);
		mpz_divexact(factor2, n, factor1);
		gmp_printf("%s=%Zd*%Zd\n", n_str, factor1, factor2);
	}

	mpz_clears(n, factor1, factor2, NULL);
}

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		printf("Usage: %s <filename>\n", argv[0]);
		return (1);
	}

	char *filename = argv[1];
	FILE *file = fopen(filename, "r");

	if (!file)
	{
		printf("Failed to open file: %s\n", filename);
		return (1);
	}

	char n_str[1024];

	while (fgets(n_str, sizeof(n_str), file) != NULL)
	{
		char *newline = strchr(n_str, '\n');
		if (newline != NULL)
		{
			*newline = '\0';
		}

		find_primes(n_str);

	}

	fclose(file);
	return (0);
}

