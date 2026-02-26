#include "minishell.h"

void	ft_init_token(t_token *token)
{
	if (!token)
		return ;
	token->string = NULL;
	token->store_string = NULL;
	token->type = 0;
	token->status = DEFAULT;
	token->prev = NULL;
	token->next = NULL;
}

t_token	*ft_tok_lstnew(char *str, int tok_type)
{
	t_token	*new_node;

	new_node = (t_token *)malloc(sizeof(t_token));
	if (!new_node)
		return (NULL);
	ft_init_token(new_node);
	new_node->prev = NULL;
	new_node->string = ft_strdup(str);
	new_node->store_string = ft_strdup(str);
	new_node->type = tok_type;
	new_node->next = NULL;
	return (new_node);
}

void	ft_tok_add_node(t_token **head, char *str, int type)
{
	t_token	*new_node;
	t_token	*last;

	new_node = ft_tok_lstnew(str, type);
	if (!head || !new_node)
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
	new_node->next = NULL;
}
