#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

unsigned int	string_length(char const *s)
{
	unsigned int	len;

	len = 0;
	while (s[len] != '\0')
		len++;
	return (len);
}

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	s_len;
	char			*new_str;
	unsigned int	i;

	if (s == NULL || f == NULL)
		return (NULL);
	s_len = string_length(s);
	i = 0;
	new_str = (char *)malloc((s_len + 1) * sizeof(char));
	if (new_str == NULL)
		return (NULL);
	while (i < s_len)
	{
		new_str[i] = f(i, s[i]);
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}
