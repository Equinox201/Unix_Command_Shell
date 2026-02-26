#include "minishell.h"

int	ft_command_execute(t_data *data, t_command *cmd)
{
	int	error_code;

	if (!cmd || !cmd->args[0])
	{
		error_code = ft_error_message("child", "parsing error",
				"no command to execute", EXIT_FAILURE);
		ft_full_exit(data, error_code);
	}
	if (ft_cmd_fds_prep(cmd->file) != 0)
		ft_full_exit(data, EXIT_FAILURE);
	ft_cmd_exec_prep(data, cmd, cmd->file);
	error_code = ft_builtin_exec(data, cmd);
	if (error_code != 127)
		ft_full_exit(data, error_code);
	error_code = ft_system_exec(data, cmd);
	ft_full_exit(data, error_code);
	return (error_code);
}

int	ft_parent_process(t_data *data)
{
	t_command	*tmp;
	pid_t		tracker;
	int			code;
	int			final_code;

	code = 0;
	final_code = 0;
	tmp = data->cmd;
	while (tmp)
	{
		tracker = waitpid(tmp->pid, &code, 0);
		while (tracker == -1 && errno == EINTR)
			tracker = waitpid(tmp->pid, &code, 0);
		if (tracker == -1)
		{
			ft_error_message("waitpid", NULL, strerror(errno), errno);
			return (errno);
		}
		if (WIFSIGNALED(code))
			final_code = 128 + WTERMSIG(code);
		else if (WIFEXITED(code))
			final_code = WEXITSTATUS(code);
		tmp = tmp->next;
	}
	return (final_code);
}

int	ft_child_process(t_data *data)
{
	t_command	*tmp;
	int			error_code;

	tmp = data->cmd;
	while (tmp)
	{
		tmp->pid = fork();
		if (tmp->pid == -1)
			return (ft_error_message("fork", NULL, strerror(errno), FAIL));
		else if (tmp->pid == 0)
		{
			error_code = ft_command_execute(data, tmp);
			exit(error_code);
		}
		tmp = tmp->next;
	}
	ft_parent_close_pipe(data);
	return (ft_parent_process(data));
}

int	ft_exec_init_check(t_data *data)
{
	t_fds_io	*tmp;
	int			error_code;

	error_code = 127;
	if (!data->cmd->args)
	{
		tmp = data->cmd->file;
		if (!tmp || (!tmp->filein && tmp->fileout))
			error_code = PASS;
		else if ((tmp->filein && tmp->fd_in == -1) || (tmp->fileout
				&& tmp->fd_out == -1))
			error_code = FAIL;
	}
	return (error_code);
}

int	ft_execution_trigger(t_data *data)
{
	int	error_code;

	if (!data || !data->cmd || !data->cmd->args)
		return (PASS);
	if (data->cmd->file && data->cmd->file->heredoc_del)
	{
		if (data->cmd->file->fd_in == -1)
			ft_heredoc_input(data->cmd, data);
	}
	error_code = ft_exec_init_check(data);
	if (error_code != 127)
		return (error_code);
	error_code = ft_pipe_create(data);
	if (error_code != 127)
		return (error_code);
	if (data->cmd->pipe_output == 0 && data->cmd->prev == NULL
		&& (ft_cmd_fds_prep(data->cmd->file) == 1 || !data->cmd->file))
	{
		error_code = ft_builtin_exec(data, data->cmd);
		if (error_code != 127)
			return (error_code);
	}
	return (ft_child_process(data));
}
