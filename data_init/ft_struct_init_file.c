#include "minishell.h"

void	ft_init_file(t_fds_io *file)
{
	if (!file)
		return ;
	file->filein = NULL;
	file->fileout = NULL;
	file->heredoc_del = NULL;
	file->heredoc_quotes = false;
	file->flag = false;
	file->fd_in = -1;
	file->fd_out = -1;
	file->store_stdin = -1;
	file->store_stdout = -1;
}

t_fds_io	*ft_create_new_file(void)
{
	t_fds_io	*new_file;

	new_file = malloc(sizeof(t_fds_io));
	if (!new_file)
		return (NULL);
	ft_init_file(new_file);
	return (new_file);
}
