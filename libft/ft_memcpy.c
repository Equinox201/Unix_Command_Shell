#include <unistd.h>
#include <stdio.h>

void	*ft_memcpy(void *dest, const void *src, size_t size)
{
	unsigned char	*e;
	unsigned char	*f;
	size_t			d;

	d = 0;
	e = (unsigned char *)dest;
	f = (unsigned char *)src;
	if (!e && !f)
		return (0);
	while (d < size)
	{
		*(unsigned char *)(dest + d) = *(unsigned char *)(src + d);
		d++;
	}
	return (dest);
}
