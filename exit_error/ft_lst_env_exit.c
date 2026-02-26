#include "minishell.h"

void	ft_env_delnode(t_env *node)
{
	if (!node)
		return ;
	ft_safe_str(node->key);
	ft_safe_str(node->value);
	ft_safe_str(node->original);
	free(node);
	node = NULL;
}

void	ft_env_lstclear(t_env **lst)
{
	t_env	*temp;
	t_env	*next;

	if (!lst || !*lst)
		return ;
	temp = *lst;
	next = 0;
	while (temp != NULL)
	{
		next = temp->next;
		ft_env_delnode(temp);
		temp = next;
	}
	*lst = NULL;
}
