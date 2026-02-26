#include "minishell.h"

void	ft_free_fds_io(t_fds_io *file)
{
	if (!file)
		return ;
	if (file->filein)
		ft_safe_str(file->filein);
	if (file->fileout)
		ft_safe_str(file->fileout);
	if (file->heredoc_del)
		ft_safe_str(file->heredoc_del);
	if (file->fd_in >= 0)
	{
		close(file->fd_in);
		file->fd_in = -1;
	}
	if (file->fd_out >= 0)
	{
		close(file->fd_out);
		file->fd_out = -1;
	}
	free(file);
}

void	ft_cmd_delnode(t_command *node)
{
	if (!node)
		return ;
	ft_safe_array((void ***)&node->args);
	ft_safe_str(node->path);
	ft_free_fds_io(node->file);
	if (node->pipe_fd)
	{
		free(node->pipe_fd);
		node->pipe_fd = NULL;
	}
	free(node);
}

void	ft_cmd_lstclear(t_command **lst)
{
	t_command	*temp;
	t_command	*next;

	if (!lst || !*lst)
		return ;
	temp = *lst;
	next = 0;
	while (temp != NULL)
	{
		next = temp->next;
		ft_cmd_delnode(temp);
		temp = next;
	}
	*lst = NULL;
}
