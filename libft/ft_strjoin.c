#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*strjoin;
	size_t	s1_len;
	size_t	s2_len;
	size_t	total_len;

	s1_len = 0;
	s2_len = 0;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	while (s1[s1_len] != '\0')
		s1_len++;
	while (s2[s2_len] != '\0')
		s2_len++;
	total_len = s1_len + s2_len + 1;
	strjoin = (char *)malloc(total_len * sizeof(char));
	if (strjoin == NULL)
		return (NULL);
	strjoin[0] = '\0';
	ft_strlcat(strjoin, s1, total_len + 1);
	ft_strlcat(strjoin, s2, total_len + 1);
	return (strjoin);
}
