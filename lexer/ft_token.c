#include "minishell.h"

char	*ft_fill_token(char *src, int pos, int len)
{
	char	*new_str;
	int		i;

	new_str = malloc(sizeof(char) * (len + 1));
	if (!new_str)
		return (NULL);
	i = 0;
	while (i < len)
	{
		new_str[i] = src[pos + i];
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}

int	ft_generate_token(t_data *d, int pos, int start, int tok)
{
	int		len;
	char	*string;

	string = NULL;
	if (tok == TOKEN_WORD)
	{
		len = (pos - start);
		string = ft_fill_token(d->user_input, start, len);
		if (!string)
			return (FAIL);
		ft_tok_add_node(&d->token, string, tok);
	}
	else if (tok >= TOKEN_PIPE)
	{
		len = 1;
		if (tok == TOKEN_APPEND || tok == TOKEN_HEREDOC)
			len = 2;
		string = ft_fill_token(d->user_input, pos, len);
		if (!string)
			return (FAIL);
		ft_tok_add_node(&d->token, string, tok);
	}
	ft_safe_str(string);
	return (PASS);
}

int	ft_token_creation(t_data *data, char *usr_in, int curr, int *a)
{
	int	tok;
	int	tok_prv;

	tok = ft_id_tok_type(usr_in, (*a));
	tok_prv = 0;
	if ((*a) != 0)
		tok_prv = ft_id_tok_type(usr_in, (*a) - 1);
	if (tok != 0)
	{
		if ((*a) != 0 && tok_prv == 0)
			ft_generate_token(data, (*a), curr, TOKEN_WORD);
		if (tok >= TOKEN_PIPE)
		{
			ft_generate_token(data, (*a), curr, tok);
			if (tok == TOKEN_APPEND || tok == TOKEN_HEREDOC)
				(*a)++;
		}
		curr = (*a) + 1;
	}
	return (curr);
}

int	ft_fetch_current_flag(int flag, char *usr_in, int a)
{
	if (usr_in[a] == '\'' && flag == 0)
		return (1);
	else if (usr_in[a] == '\'' && flag == 1)
		return (0);
	else if (usr_in[a] == '\"' && flag == 0)
		return (2);
	else if (usr_in[a] == '\"' && flag == 2)
		return (0);
	else
		return (flag);
}

int	ft_token_start(t_data *data, char *user_input, int len)
{
	int	a;
	int	curr;
	int	flag;

	a = 0;
	curr = 0;
	flag = 0;
	while (a <= len)
	{
		flag = ft_fetch_current_flag(flag, user_input, a);
		if (flag == 0)
			curr = ft_token_creation(data, user_input, curr, &a);
		a++;
	}
	return (PASS);
}
