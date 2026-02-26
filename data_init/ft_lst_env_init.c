#include "minishell.h"

void	ft_init_env(t_env *env)
{
	env->key = NULL;
	env->value = NULL;
	env->original = NULL;
	env->prev = NULL;
	env->next = NULL;
}

int	ft_strfind(char *str, char c)
{
	int	a;

	a = 0;
	if (!str)
	{
		return (-1);
	}
	while (str[a])
	{
		if (str[a] == c)
			return (a);
		a++;
	}
	return (-1);
}

t_env	*ft_env_lstnew(char *str)
{
	t_env	*new_node;
	int		len;
	int		a;

	len = ft_strlen(str);
	a = ft_strfind(str, '=');
	new_node = (t_env *)malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	ft_init_env(new_node);
	new_node->prev = NULL;
	new_node->original = ft_strdup(str);
	new_node->key = ft_substr(str, 0, a);
	new_node->value = ft_substr(str, a + 1, len - a);
	new_node->next = NULL;
	if (!new_node->original || !new_node->key || !new_node->value)
	{
		free(new_node->original);
		free(new_node->key);
		free(new_node->value);
		free(new_node);
		return (NULL);
	}
	return (new_node);
}

void	ft_env_add_node(t_env **head, char *str)
{
	t_env	*new_node;
	t_env	*last;

	new_node = ft_env_lstnew(str);
	if (!new_node || !head)
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
