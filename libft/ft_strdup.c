#include <stdlib.h>
#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*ptr;
	size_t	i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	ptr = malloc((i + 1) * sizeof(char));
	if (ptr != NULL)
	{
		ft_memcpy(ptr, s, i + 1);
		return (ptr);
	}
	return (NULL);
}
