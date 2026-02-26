#include "libft.h"
#include <stdio.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*ptrs1;
	const unsigned char	*ptrs2;
	size_t				i;

	ptrs1 = s1;
	ptrs2 = s2;
	i = 0;
	if (n == 0)
		return (0);
	while (i < n)
	{
		if (ptrs1[i] != ptrs2[i])
		{
			return (ptrs1[i] - ptrs2[i]);
		}
		i++;
	}
	return (0);
}
