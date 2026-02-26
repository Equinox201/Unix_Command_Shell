#include "minishell.h"

void	ft_tok_delnode(t_token *node)
{
	if (!node)
		return ;
	ft_safe_str(node->string);
	ft_safe_str(node->store_string);
	free(node);
}

void	ft_tok_lstclear(t_token **lst)
{
	t_token	*temp;
	t_token	*next;

	if (!lst || !*lst)
		return ;
	temp = *lst;
	next = 0;
	while (temp != NULL)
	{
		next = temp->next;
		ft_tok_delnode(temp);
		temp = next;
	}
	*lst = NULL;
}
