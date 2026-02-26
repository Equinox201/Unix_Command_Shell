#include "minishell.h"

int	ft_env_insert_node(t_data *data, t_env *new)
{
	t_env	*temp;

	if (!data || !new)
		return (FAIL);
	temp = data->env;
	while (temp->next)
	{
		temp = temp->next;
	}
	new->next = NULL;
	new->prev = temp;
	temp->next = new;
	return (ft_reset_env(data));
}

t_env	*ft_env_find_node(t_data *data, char *search)
{
	t_env	*temp;

	temp = data->env;
	while (temp != NULL)
	{
		if (ft_strcmp(temp->key, search) == 0)
			return (temp);
		temp = temp->next;
	}
	return (NULL);
}

int	ft_env_new_node(t_data *data, char *content)
{
	t_env	*new_node;

	new_node = ft_env_lstnew(content);
	if (new_node == NULL)
		return (FAIL);
	return (ft_env_insert_node(data, new_node));
}

int	ft_env_edit_node(t_data *data, char *trgt, char *content)
{
	t_env	*temp;
	char	*value;
	int		a;
	int		len;

	if (!data->env || !content)
		return (FAIL);
	temp = ft_env_find_node(data, trgt);
	if (!temp)
		return (FAIL);
	len = ft_strlen(content);
	a = ft_strfind(content, '=');
	value = ft_substr(content, a + 1, len - a);
	if (value == NULL)
		return (FAIL);
	ft_safe_str(temp->original);
	ft_safe_str(temp->value);
	temp->original = ft_strdup(content);
	temp->value = value;
	return (ft_reset_env(data));
}

int	ft_env_remove_node(t_data *data, char *trgt)
{
	t_env	*temp;

	temp = NULL;
	if (!data->env || !data->env || !trgt)
		return (FAIL);
	temp = ft_env_find_node(data, trgt);
	if (!temp)
		return (FAIL);
	if (temp->prev)
		temp->prev->next = temp->next;
	else
		data->env = temp->next;
	if (temp->next)
		temp->next->prev = temp->prev;
	ft_env_delnode(temp);
	if (!data->env)
		return (PASS);
	return (ft_reset_env(data));
}
