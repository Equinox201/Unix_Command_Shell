#include "minishell.h"

int	ft_line_handle(t_fds_io *io, char **line, t_data *data)
{
	char	*expanded;

	if (*line == NULL)
	{
		ft_error_message("warning", "here-document delimited"
			" by end-of-file: wanted", io->heredoc_del, 1);
		return (1);
	}
	if (ft_strcmp(*line, io->heredoc_del) == 0)
	{
		data->error_code = 1;
		return (1);
	}
	if (!io->heredoc_quotes)
	{
		expanded = ft_expand_heredoc(*line, data);
		ft_safe_str(*line);
		*line = expanded;
		return (0);
	}
	return (0);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

int	ft_is_set(char const *s, char c)
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

char	*ft_strtrim_front(char const *s1, char const *set)
{
	char	*strtrim;
	size_t	start;
	size_t	len;
	size_t	i;

	if (s1 == NULL || set == NULL)
		return (NULL);
	start = 0;
	while (s1[start] != '\0' && ft_is_set(set, s1[start]))
		start++;
	len = ft_strlen(s1) - start;
	strtrim = (char *)malloc((len + 1) * (sizeof(char)));
	if (strtrim == NULL)
		return (NULL);
	i = 0;
	while (s1[start] != '\0')
	{
		strtrim[i] = s1[start];
		start++;
		i++;
	}
	strtrim[i] = '\0';
	return (strtrim);
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
	end = ft_strlen(s1);
	while (s1[start] != '\0' && ft_is_set(set, s1[start]))
		start++;
	while (end > start && ft_is_set(set, s1[end - 1]))
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
