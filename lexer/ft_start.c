#include "minishell.h"

void	ft_expand_var_quote(t_data *data)
{
	t_token	*t;
	int		flag;
	int		len;

	ft_find_variables(data);
	t = data->token;
	while (t)
	{
		if (t->type == TOKEN_VAR)
			ft_expand_checker(data, t);
		flag = ft_find_quotes(t->string);
		if (flag != 0 && !(t->prev && t->prev->type == TOKEN_HEREDOC))
		{
			len = ft_quotelen(t->string, 0, 0);
			ft_handle_quotes(t, len, 0, 0);
		}
		t = t->next;
	}
}

int	ft_lex_user_input(t_data *data)
{
	int	len;

	if (data->user_input[0] == '\0')
		return (FAIL);
	else if (ft_empty_inputs(data->user_input) == 1)
		return (FAIL);
	add_history(data->user_input);
	len = ft_strlen(data->user_input);
	if (ft_quote_syntax_check(data, data->user_input, len, 0) == FAIL)
		return (FAIL);
	ft_token_start(data, data->user_input, len);
	if (!data->token)
		return (FAIL);
	if (ft_grammar_check(data) == FAIL)
		return (FAIL);
	return (PASS);
}

int	ft_process_user_input(t_data *data)
{
	if (ft_lex_user_input(data) == FAIL)
		return (FAIL);
	ft_expand_var_quote(data);
	return (PASS);
}

int	ft_start(t_data *data)
{
	if (data->user_input == NULL)
	{
		ft_print_exit();
		ft_full_exit(data, 0);
		data->error_code = 0;
		return (PASS);
	}
	if (ft_process_user_input(data) == FAIL)
		return (FAIL);
	ft_parse_tokens(data);
	data->error_code = ft_execution_trigger(data);
	if (ft_cmd_lstsize(data->cmd) == 1 && data->cmd->args)
		ft_update_last_cmd(data);
	return (data->error_code);
}
