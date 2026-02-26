#include "minishell.h"

int	ft_env(t_data *data, char **args)
{
	t_env	*tmp;

	tmp = data->env;
	if (args[1])
		return (ft_error_message("env", NULL, "too many arguments", 2));
	if (!data->env || !data->env_cpy)
		return (FAIL);
	while (tmp)
	{
		if (ft_strcmp(tmp->key, "_") == 0)
			ft_putendl_fd("_=/minishell/built_ins/env", STDOUT_FILENO);
		else
			ft_putendl_fd(tmp->original, STDOUT_FILENO);
		tmp = tmp->next;
	}
	return (PASS);
}
