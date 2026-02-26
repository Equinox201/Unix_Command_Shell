#include "minishell.h"

int	ft_find_quotes(char *str)
{
	int	a;

	a = 0;
	while (str[a])
	{
		if (str[a] == '\'' || str[a] == '\"')
			return (1);
		a++;
	}
	return (0);
}

int	ft_quotelen(char *str, int a, int len)
{
	int	flag;
	int	new_flag;

	flag = 0;
	new_flag = 0;
	while (str[a])
	{
		new_flag = ft_fetch_current_flag(flag, str, a);
		if (new_flag != flag)
		{
			flag = new_flag;
			a++;
			continue ;
		}
		len++;
		a++;
	}
	if (flag != 0)
		len++;
	return (len);
}

char	ft_quote_char(int flag)
{
	if (flag == 1)
		return ('\'');
	if (flag == 2)
		return ('\"');
	return (' ');
}

void	ft_handle_quotes(t_token *tok, int len, int a, int b)
{
	char	*new_str;
	int		flag;
	int		new_flag;

	flag = 0;
	new_flag = 0;
	new_str = malloc(sizeof(char) * (len + 1));
	if (!new_str)
		return ;
	while (tok->string[a])
	{
		new_flag = ft_fetch_current_flag(flag, tok->string, a);
		if (new_flag != flag)
		{
			flag = new_flag;
			a++;
			continue ;
		}
		new_str[b++] = tok->string[a++];
	}
	if (flag != 0)
		new_str[b++] = ft_quote_char(flag);
	new_str[b] = '\0';
	ft_safe_str(tok->string);
	tok->string = new_str;
}
