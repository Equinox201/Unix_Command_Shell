#include "minishell.h"

int	ft_cmd_fds_prep(t_fds_io *f)
{
	if (!f || (!f->filein && !f->fileout))
		return (PASS);
	if ((f->filein && f->fd_in == -1) || (f->fileout && f->fd_out == -1))
		return (FAIL);
	return (PASS);
}

int	ft_std_io_backup(t_fds_io *f)
{
	int	error_code;

	error_code = PASS;
	f->store_stdin = dup(STDIN_FILENO);
	if (f->store_stdin == -1)
		error_code = ft_error_message("dup", "stdin backup", strerror(errno),
				FAIL);
	f->store_stdout = dup(STDOUT_FILENO);
	if (f->store_stdout == -1)
		error_code = ft_error_message("dup", "stdout backup", strerror(errno),
				FAIL);
	return (error_code);
}

int	ft_dup2_redirect(t_fds_io *f)
{
	int	error_code;

	error_code = PASS;
	if (!f)
		return (0);
	error_code = ft_std_io_backup(f);
	if (f->fd_in != -1)
	{
		if (dup2(f->fd_in, STDIN_FILENO) == -1)
			error_code = ft_error_message("dup2", f->filein, strerror(errno),
					FAIL);
	}
	if (f->fd_out != -1)
	{
		if (dup2(f->fd_out, STDOUT_FILENO) == -1)
			error_code = ft_error_message("dup2", f->fileout, strerror(errno),
					FAIL);
	}
	return (error_code);
}

int	ft_pipe_create(t_data *data)
{
	int			*pip;
	t_command	*tmp;

	tmp = data->cmd;
	while (tmp)
	{
		if (tmp->pipe_output || (tmp->prev && tmp->prev->pipe_output))
		{
			pip = malloc(sizeof * pip * 2);
			if (!pip || pipe(pip) != 0)
			{
				ft_free_data_struct(data);
				return (FAIL);
			}
			tmp->pipe_fd = pip;
		}
		tmp = tmp->next;
	}
	return (127);
}
