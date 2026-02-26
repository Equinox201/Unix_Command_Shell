#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static int	get_length(long n)
{
	int	count;

	count = 0;
	if (n == -2147483648)
		return (10);
	if (n < 0)
		n = -n;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n /= 10;
		count++;
	}
	return (count);
}

static int	negative(long n)
{
	if (n < 0)
		return (1);
	return (0);
}

char	*ft_itoa(int n)
{
	char	*convert;
	long	num;
	int		i;

	num = n;
	i = negative(n) + get_length(n);
	convert = (char *)malloc((i + 1) * sizeof(char));
	if (convert == NULL)
		return (NULL);
	convert[i--] = '\0';
	if (num == 0)
		convert[0] = '0';
	if (num < 0)
	{
		convert[0] = '-';
		num = -num;
	}
	while (num > 0)
	{
		convert[i--] = ((num % 10) + 48);
		num /= 10;
	}
	return (convert);
}
