#include "minishell.h"

void	ft_init_command(t_command *cmd)
{
	if (!cmd)
		return ;
	cmd->args = NULL;
	cmd->path = NULL;
	cmd->pipe_output = false;
	cmd->pipe_fd = NULL;
	cmd->pid = 0;
	cmd->file = NULL;
	cmd->prev = NULL;
	cmd->next = NULL;
}

t_command	*ft_cmd_lstnew(void)
{
	t_command	*new_node;

	new_node = (t_command *)malloc(sizeof(t_command));
	if (!new_node)
		return (NULL);
	ft_init_command(new_node);
	return (new_node);
}

void	ft_cmd_add_node(t_command **head)
{
	t_command	*new_node;
	t_command	*last;

	if (!head)
		return ;
	new_node = ft_cmd_lstnew();
	if (!new_node)
		return ;
	if (*head == NULL)
	{
		*head = new_node;
		return ;
	}
	last = *head;
	while (last->next != NULL)
		last = last->next;
	last->next = new_node;
	new_node->prev = last;
}
