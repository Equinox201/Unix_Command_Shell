#include "minishell.h"

int	ft_cmd_dir_find(char *cmd)
{
	struct stat	dir_check;

	if (ft_strchr(cmd, '/') == NULL && !getenv("PATH"))
		return (FAIL);
	if (access(cmd, F_OK) != 0)
		return (FAIL);
	if (stat(cmd, &dir_check) != 0)
		return (FAIL);
	if (S_ISDIR(dir_check.st_mode))
		return (FAIL);
	if (access(cmd, F_OK | X_OK) != 0)
		return (FAIL);
	return (PASS);
}

int	ft_cmd_dir_check(char *cmd)
{
	struct stat	dir_check;

	if (ft_strchr(cmd, '/') == NULL && !getenv("PATH"))
		return (ft_error_message(cmd, NULL, "command not found", 127));
	if (access(cmd, F_OK) != 0)
		return (ft_error_message(cmd, NULL, strerror(errno), 127));
	if (stat(cmd, &dir_check) != 0)
		return (ft_error_message(cmd, NULL, strerror(errno), 127));
	if (S_ISDIR(dir_check.st_mode))
		return (ft_error_message(cmd, NULL, "Is a directory", 126));
	if (access(cmd, F_OK | X_OK) != 0)
		return (ft_error_message(cmd, NULL, strerror(errno), 126));
	return (PASS);
}

char	*ft_local_command(char *cmd)
{
	if (ft_cmd_dir_find(cmd) != 0)
		return (NULL);
	else
		return (ft_strdup(cmd));
}

int	ft_system_exec(t_data *data, t_command *cmd)
{
	int	error_code;

	if (!cmd || !cmd->args)
		return (ft_error_message(NULL, NULL, "invalid command", 127));
	if (ft_strchr(cmd->args[0], '/') != NULL)
	{
		cmd->path = ft_local_command(cmd->args[0]);
		if (!cmd->path)
			return (ft_cmd_dir_check(cmd->args[0]));
	}
	else
	{
		cmd->path = ft_command_create(data, cmd->args[0]);
		if (!cmd->path)
			return (ft_error_message(cmd->args[0], NULL, "command not found",
					127));
	}
	error_code = ft_cmd_dir_check(cmd->path);
	if (error_code != PASS)
		return (error_code);
	if (execve(cmd->path, cmd->args, data->env_cpy) == -1)
		return (ft_error_message("execve", NULL, strerror(errno), errno));
	return (FAIL);
}

int	ft_cmd_exec_prep(t_data *data, t_command *cmd, t_fds_io *file)
{
	if (cmd != NULL)
	{
		if (cmd->prev && cmd->prev->pipe_output)
			dup2(cmd->prev->pipe_fd[0], STDIN_FILENO);
		if (cmd->pipe_output)
			dup2(cmd->pipe_fd[1], STDOUT_FILENO);
		ft_child_close_pipe(data, cmd);
	}
	ft_dup2_redirect(file);
	ft_command_close_fd(cmd);
	ft_parent_close_pipe(data);
	return (0);
}
