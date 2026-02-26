#include <stdlib.h>
#include <stdio.h>

int	is_set(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	s_len(char const *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*strtrim;
	size_t	start;
	size_t	end;
	size_t	i;

	if (s1 == NULL || set == NULL)
		return (NULL);
	start = 0;
	end = s_len(s1);
	while (s1[start] != '\0' && is_set(set, s1[start]))
		start++;
	while (end > start && is_set(set, s1[end - 1]))
		end--;
	strtrim = (char *)malloc((end - start + 1) * (sizeof(char)));
	if (strtrim == NULL)
		return (NULL);
	i = 0;
	while (start < end)
	{
		strtrim[i] = s1[start];
		start++;
		i++;
	}
	strtrim[i] = '\0';
	return (strtrim);
}
