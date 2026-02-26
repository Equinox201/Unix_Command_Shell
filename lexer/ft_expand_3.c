#include "minishell.h"

int	ft_isspace(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (FAIL);
	return (PASS);
}

void	ft_find_variables(t_data *data)
{
	t_token	*t;
	int		a;

	t = data->token;
	while (t)
	{
		a = 0;
		while (t->string[a])
		{
			if (t->string[a] == '$' && ft_isspace(t->string[a + 1]) != 1)
			{
				if (t->prev && t->prev->type == TOKEN_HEREDOC)
					break ;
				t->type = TOKEN_VAR;
				break ;
			}
			a++;
		}
		t = t->next;
	}
}

int	ft_expand_syntax(char *s, int pos)
{
	int	a;
	int	b;

	a = pos + 1;
	b = pos - 1;
	if (s[a] == '$' || s[a] == ' ' || s[a] == '=' || s[a] == '\0')
		return (FAIL);
	if (pos > 0 && (s[b] == '\"' && s[a] == '\"'))
		return (FAIL);
	return (PASS);
}
