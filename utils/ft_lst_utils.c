#include "minishell.h"

int	ft_tok_lstsize(t_token *lst)
{
	t_token	*temp;
	int		count;

	temp = lst;
	count = 0;
	while (temp != NULL)
	{
		count++;
		temp = temp->next;
	}
	return (count);
}

int	ft_cmd_lstsize(t_command *lst)
{
	t_command	*temp;
	int			count;

	temp = lst;
	count = 0;
	while (temp != NULL)
	{
		count++;
		temp = temp->next;
	}
	return (count);
}

int	ft_env_lstsize(t_env *lst)
{
	t_env	*temp;
	int		count;

	temp = lst;
	count = 0;
	while (temp != NULL)
	{
		count++;
		temp = temp->next;
	}
	return (count);
}

t_command	*ft_last_command(t_command *cmd)
{
	while (cmd->next != NULL)
		cmd = cmd->next;
	return (cmd);
}
