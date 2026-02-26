#include "minishell.h"

int	ft_env_size_export(t_env *lst)
{
	t_env	*temp;
	int		count;

	temp = lst;
	count = 0;
	while (temp != NULL)
	{
		if (ft_isalpha(temp->key[0]) == 1)
			count++;
		temp = temp->next;
	}
	return (count);
}

int	ft_empty_export(t_data *data)
{
	int		count;
	int		a;
	char	**order;

	a = 0;
	count = ft_env_size_export(data->env);
	if (count == 0)
		return (FAIL);
	order = malloc((count + 1) * (sizeof(char *)));
	if (!order)
		return (FAIL);
	ft_quicksort_prep(data, order, count);
	while (a < count)
	{
		ft_putendl_fd(order[a], STDOUT_FILENO);
		a++;
	}
	a = 0;
	while (a < count)
	{
		ft_safe_str(order[a]);
		a++;
	}
	free(order);
	return (PASS);
}

int	ft_format_check(char *args)
{
	int	a;

	a = 0;
	if (ft_isalpha(args[a]) == 0 && args[a] != '_')
		return (FAIL);
	a++;
	while (args[a] != '\0' && args[a] != '=')
	{
		if (!ft_isalnum(args[a]) && args[a] != '_')
			return (FAIL);
		a++;
	}
	return (PASS);
}

int	ft_edit_or_add(t_data *data, char *args)
{
	int		a;
	char	*key;
	int		error_code;
	t_env	*tmp;

	tmp = NULL;
	a = ft_strfind(args, '=');
	if (a == -1)
		return (FAIL);
	key = ft_substr(args, 0, a);
	tmp = ft_env_find_node(data, key);
	if (tmp == NULL)
		error_code = ft_env_new_node(data, args);
	else
		error_code = ft_env_edit_node(data, key, args);
	ft_safe_str(key);
	return (error_code);
}

int	ft_export(t_data *data, char **args)
{
	int	a;
	int	error_code;

	a = 1;
	error_code = 0;
	if (!args[a])
		ft_empty_export(data);
	while (args[a])
	{
		if (ft_format_check(args[a]) == FAIL)
			error_code = ft_error_message("export", args[a],
					" not a valid identifier", FAIL);
		else
			ft_edit_or_add(data, args[a]);
		a++;
	}
	return (error_code);
}
