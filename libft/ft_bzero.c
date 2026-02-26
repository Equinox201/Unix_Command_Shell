#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	ft_bzero(void *ptr, size_t n)
{
	size_t			i;
	unsigned char	*p;

	p = (unsigned char *)ptr;
	i = 0;
	while (i < n)
	{
		p[i] = '\0';
		i++;
	}
}
