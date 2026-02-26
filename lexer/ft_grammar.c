#include "minishell.h"

int	ft_tok_syntax(t_token *t)
{
	if (t->prev)
	{
		if (t->type == TOKEN_PIPE && t->prev->type == TOKEN_PIPE)
			return (FAIL);
		if (t->type > TOKEN_PIPE && t->prev->type > TOKEN_PIPE)
			return (FAIL);
		if (t->type == TOKEN_END && t->prev->type >= TOKEN_PIPE)
			return (FAIL);
	}
	return (PASS);
}

void	ft_special_message(t_token *t)
{
	char	*error;
	char	*temp;

	if (t->type == TOKEN_END && t->prev)
	{
		error = ft_strjoin("\'", t->prev->string);
		temp = error;
		error = ft_strjoin(error, "\'");
		ft_messaging("syntax error near unexpected token ", error);
	}
	else
	{
		error = ft_strjoin("\'", t->string);
		temp = error;
		error = ft_strjoin(error, "\'");
		ft_messaging("syntax error near unexpected token ", error);
	}
	ft_safe_str(error);
	ft_safe_str(temp);
}

int	ft_grammar_check(t_data *data)
{
	t_token	*t;

	t = data->token;
	while (t)
	{
		if (t->type == TOKEN_PIPE && t->prev == NULL)
		{
			ft_messaging("syntax error near unexpected token ", "'|'");
			return (FAIL);
		}
		if (ft_tok_syntax(t) != PASS)
		{
			if (t->type == TOKEN_END && t->prev && t->prev->type > TOKEN_PIPE)
				ft_messaging("syntax error near unexpected token ",
					"\"newline\"");
			else
				ft_special_message(t);
			return (FAIL);
		}
		t = t->next;
	}
	return (PASS);
}
