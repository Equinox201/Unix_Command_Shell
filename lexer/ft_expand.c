#include "minishell.h"

void	ft_strcpy_remote(char *str1, char *str2, int *a)
{
	int	b;

	b = 0;
	while (str2[b])
	{
		str1[*a] = str2[b];
		b++;
		(*a)++;
	}
}

char	*ft_new_expanded(char *str, char *exp_var, int len, int a)
{
	int		b;
	int		c;
	char	*new_str;

	b = 0;
	c = 0;
	new_str = malloc(sizeof(char) * (len));
	if (!new_str)
		return (NULL);
	while (str[b])
	{
		if (str[b] == '$' && b == a)
		{
			ft_strcpy_remote(new_str, exp_var, &c);
			b = (b + ft_varlen(str + a) + 1);
			if (str[b] == '\0')
				break ;
		}
		new_str[c++] = str[b++];
	}
	new_str[c] = '\0';
	return (new_str);
}

void	ft_replace_exp_var(t_token *t, char *str, char *var, int a)
{
	char	*new_str;
	int		len_str;
	int		len_var;
	int		new_len;

	len_var = ft_strlen(var);
	len_str = ft_strlen(str) - ft_varlen(str + a);
	new_len = len_var + len_str;
	new_str = ft_new_expanded(str, var, new_len, a);
	if (!new_str)
		return ;
	if (t)
	{
		ft_safe_str(t->string);
		t->string = new_str;
	}
}

void	ft_expand_token(t_data *data, t_token *token, int a)
{
	char	*exp_var;

	exp_var = ft_og_var_value(data, token, a);
	if (exp_var == NULL)
		ft_replace_null_var(token, token->string, (a - 1));
	else
		ft_replace_exp_var(token, token->string, exp_var, (a - 1));
	ft_safe_str(exp_var);
}

void	ft_expand_checker(t_data *data, t_token *t)
{
	int	flag;
	int	a;

	a = 0;
	flag = 0;
	if (!t || !t->string || !t->string[a])
		return ;
	while (t->string[a])
	{
		flag = ft_fetch_current_flag(flag, t->string, a);
		if (t->string[a] == '$' && (flag == 0 || flag == 2))
		{
			if (ft_expand_syntax(t->string, a) == PASS)
			{
				ft_expand_token(data, t, a + 1);
				if (t->string == NULL || t->string[0] == '\0')
					return ;
				if (a >= 1)
					a --;
			}
		}
		a++;
	}
}
