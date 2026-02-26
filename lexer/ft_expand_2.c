#include "minishell.h"

int	ft_special(char c)
{
	if (c == '?' || c == '#' || c == '$' || c == '!' || c == '*' || c == '@'
		|| c == '_' || (c >= '0' && c <= '9'))
		return (1);
	return (0);
}

char	*ft_special_expand(t_data *data, char c)
{
	t_env	*temp;
	char	*value;

	if (c == '?')
		return (ft_itoa(data->error_code));
	else if (c == '0')
		return (ft_strdup("Jacky & Nico Minishell"));
	else if (c == '_')
	{
		temp = ft_env_find_node(data, "_");
		if (!temp)
			return (NULL);
		value = ft_strdup(temp->value);
		return (value);
	}
	else
		return (NULL);
}

char	*ft_og_var_value(t_data *data, t_token *tok, int a)
{
	char	*var_name;
	t_env	*tmp;
	int		b;

	if (tok->string[a] && ft_special(tok->string[a]) == 1)
		return (ft_special_expand(data, tok->string[a]));
	b = a;
	while (tok->string[b] && (ft_isalnum(tok->string[b]) == 1
			|| tok->string[b] == '_'))
		b++;
	var_name = ft_substr(tok->string, a, b - a);
	tmp = ft_env_find_node(data, var_name);
	ft_safe_str(var_name);
	if (!tmp)
		return (NULL);
	return (ft_strdup(tmp->value));
}

int	ft_varlen(char *var)
{
	int	a;
	int	len;

	a = 0;
	len = 0;
	while (var[a] != '$')
		a++;
	a++;
	if ((var[a] >= '0' && var[a] <= '9') || var[a] == '?')
		return (1);
	while (var[a] && (ft_isalnum(var[a]) == 1 || var[a] == '_'))
	{
		len++;
		a++;
	}
	return (len);
}

void	ft_replace_null_var(t_token *t, char *var, int a)
{
	int		b;
	int		c;
	int		len;
	char	*new_str;

	b = 0;
	c = 0;
	len = ft_strlen(var) - ft_varlen(var + a);
	new_str = malloc(sizeof(char) * (len + 1));
	if (!new_str)
		return ;
	ft_bzero(new_str, len + 1);
	while (var[b])
	{
		if (var[b] == '$' && b == a)
		{
			b = (b + ft_varlen(var + a) + 1);
			if (var[b] == '\0')
				break ;
		}
		new_str[c++] = var[b++];
	}
	new_str[c] = '\0';
	ft_safe_str(t->string);
	t->string = new_str;
}
