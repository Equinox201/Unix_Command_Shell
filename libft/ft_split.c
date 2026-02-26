#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

static int		word_count(char const *s, char c);

static size_t	word_copy(char **array_word, char const *s, char c);

static int		free_malloc(char **array_word, int position, size_t buffer);

char	**ft_split(char const *s, char c)
{
	size_t	num_word;
	char	**array_word;

	if (s == NULL)
		return (NULL);
	if (s[0] == '\0')
	{
		array_word = (char **)malloc(sizeof(char *));
		if (array_word == NULL)
			return (NULL);
		array_word[0] = NULL;
		return (array_word);
	}
	num_word = word_count(s, c);
	array_word = (char **)malloc((num_word + 1) * sizeof(char *));
	if (array_word == NULL)
		return (NULL);
	array_word[num_word] = NULL;
	if (word_copy(array_word, s, c))
		return (NULL);
	return (array_word);
}

int	word_count(char const *s, char c)
{
	size_t	i;
	size_t	word_flag;
	size_t	count;

	i = 0;
	word_flag = 0;
	count = 0;
	if (s == NULL || s[0] == '\0')
		return (0);
	while (s[i] != '\0')
	{
		if (s[i] != c && word_flag == 0)
		{
			word_flag = 1;
			count++;
		}
		else if (s[i] == c)
		{
			word_flag = 0;
		}
		i++;
	}
	return (count);
}

size_t	word_copy(char **array_word, char const *s, char c)
{
	size_t	word_length;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (s[i] != '\0')
	{
		word_length = 0;
		while (s[i] != '\0' && s[i] == c)
			i++;
		while (s[i] != '\0' && s[i] != c)
		{
			word_length++;
			i++;
		}
		if (word_length)
		{
			if (free_malloc(array_word, j, word_length + 1))
				return (1);
			ft_strlcpy(array_word[j], s + i - word_length, word_length + 1);
			j++;
		}
	}
	return (0);
}

int	free_malloc(char **array_word, int position, size_t buffer)
{
	int	i;

	i = 0;
	array_word[position] = malloc(buffer);
	if (array_word[position] == NULL)
	{
		while (i < position)
			free(array_word[i++]);
		free(array_word);
		return (1);
	}
	return (0);
}
