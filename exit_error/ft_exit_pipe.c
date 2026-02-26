#include "minishell.h"

void	ft_command_close_fd(t_command *cmd)
{
	if (cmd->file)
	{
		if (cmd->file->fd_in != -1)
			close(cmd->file->fd_in);
		if (cmd->file->fd_out != -1)
			close(cmd->file->fd_out);
	}
}

void	ft_parent_close_pipe(t_data *d)
{
	t_command	*temp;

	temp = d->cmd;
	while (temp)
	{
		if (temp->pipe_fd)
		{
			close(temp->pipe_fd[0]);
			close(temp->pipe_fd[1]);
		}
		temp = temp->next;
	}
}

void	ft_child_close_pipe(t_data *d, t_command *c)
{
	t_command	*temp;

	temp = d->cmd;
	while (temp)
	{
		if (temp != c && temp->pipe_fd)
		{
			close(temp->pipe_fd[0]);
			close(temp->pipe_fd[1]);
		}
		temp = temp->next;
	}
}

void	ft_reset_stdin_stdout(t_fds_io *fds)
{
	if (!fds)
		return ;
	if (fds->store_stdin != -1)
	{
		dup2(fds->store_stdin, STDIN_FILENO);
		close(fds->store_stdin);
		fds->store_stdin = -1;
	}
	if (fds->store_stdout != -1)
	{
		dup2(fds->store_stdout, STDOUT_FILENO);
		close(fds->store_stdout);
		fds->store_stdout = -1;
	}
}
