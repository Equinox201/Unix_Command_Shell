#include "minishell.h"

void	ft_handle_pipe(t_data *data, t_token **token)
{
	t_command	*last_cmd;

	last_cmd = ft_last_command(data->cmd);
	last_cmd->pipe_output = true;
	ft_cmd_add_node(&data->cmd);
	(*token) = (*token)->next;
}

void	ft_parse_tokens(t_data *data)
{
	t_token	*tmp;

	tmp = data->token;
	if (tmp->type == TOKEN_END)
		return ;
	while (tmp->next != NULL)
	{
		if (tmp == data->token)
			ft_cmd_add_node(&data->cmd);
		if (tmp->type == TOKEN_WORD || tmp->type == TOKEN_VAR)
			ft_handle_var_word(data, &tmp);
		else if (tmp->type >= TOKEN_INPUT && tmp->type <= TOKEN_APPEND)
			ft_handle_redirect(data, &tmp);
		else if (tmp->type == TOKEN_PIPE)
			ft_handle_pipe(data, &tmp);
		else if (tmp->type == TOKEN_END)
			break ;
	}
	if (!data || !data->cmd)
		return ;
}
