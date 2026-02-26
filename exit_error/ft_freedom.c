#include "minishell.h"

void	ft_safe_str(void *str)
{
	if (str != NULL)
	{
		free(str);
		str = NULL;
	}
}

void	ft_safe_array(void ***array)
{
	int	a;

	a = 0;
	if (!array || !(*array))
		return ;
	while ((*array)[a])
	{
		ft_safe_str((*array)[a]);
		(*array)[a] = NULL;
		a++;
	}
	free(*array);
	*array = NULL;
}

void	ft_lstclear_ctrl(t_data *data, int ctrl)
{
	if (ctrl == TOK)
		ft_tok_lstclear(&data->token);
	else if (ctrl == CMD)
		ft_cmd_lstclear(&data->cmd);
	else if (ctrl == ENV)
		ft_env_lstclear(&data->env);
	else if (ctrl == ALL)
	{
		ft_tok_lstclear(&data->token);
		ft_cmd_lstclear(&data->cmd);
		ft_env_lstclear(&data->env);
	}
	return ;
}

void	ft_free_data_struct(t_data *d)
{
	if (d->user_input)
	{
		ft_safe_str(d->user_input);
		d->user_input = NULL;
	}
	if (d->token)
		ft_lstclear_ctrl(d, TOK);
	if (d->cmd)
		ft_lstclear_ctrl(d, CMD);
}

void	ft_full_exit(t_data *d, int error_code)
{
	if (d)
	{
		if (d->cmd && d->cmd->file)
		{
			ft_command_close_fd(d->cmd);
			ft_reset_stdin_stdout(d->cmd->file);
		}
		ft_parent_close_pipe(d);
		ft_free_data_struct(d);
		if (d->env_cpy)
			ft_safe_array((void ***)&d->env_cpy);
		if (d->env)
			ft_lstclear_ctrl(d, ENV);
		rl_clear_history();
		free(d);
	}
	exit(error_code);
}
