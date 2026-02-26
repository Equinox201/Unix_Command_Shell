#include "minishell.h"

int	ft_quote_syntax_check(t_data *data, char *input, int len, int a)
{
	int	dblq;
	int	sglq;

	dblq = 0;
	sglq = 0;
	while (a < len)
	{
		if (input[a] == '\'' && !dblq)
			sglq = !sglq;
		else if (input[a] == '\"' && !sglq)
			dblq = !dblq;
		a++;
	}
	if (sglq || dblq)
	{
		if (sglq)
			ft_messaging("unexpected EOF while looking for matching ", "`\'\'");
		if (dblq)
			ft_messaging("unexpected EOF while looking for matching ", "`\"\'");
		ft_messaging("syntax error: ", "unexpected end of file");
		data->error_code = 2;
		return (FAIL);
	}
	return (PASS);
}

int	ft_empty_inputs(char *usr_i)
{
	int	a;

	a = 0;
	while (usr_i[a])
	{
		if (!(usr_i[a] == ' ' || (usr_i[a] >= 9 && usr_i[a] <= 13)))
			return (PASS);
		a++;
	}
	return (FAIL);
}

int	ft_id_tok_type(char *usr_i, int a)
{
	if (usr_i[a] == 32 || (usr_i[a] >= 9 && usr_i[a] <= 13))
		return (TOKEN_SPACES);
	else if (usr_i[a] == '|')
		return (TOKEN_PIPE);
	else if (usr_i[a] == '<')
	{
		if (usr_i[a + 1] == '<')
			return (TOKEN_HEREDOC);
		return (TOKEN_INPUT);
	}
	else if (usr_i[a] == '>')
	{
		if (usr_i[a + 1] == '>')
			return (TOKEN_APPEND);
		return (TOKEN_TRUNC);
	}
	else if (usr_i[a] == '\0')
		return (TOKEN_END);
	else
		return (0);
}
