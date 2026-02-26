#include "minishell.h"

int	ft_unset(t_data *data, char **args)
{
	int	a;

	a = 1;
	if (!data || !data->env)
		return (FAIL);
	if (!args[1])
		return (0);
	while (args[a])
	{
		ft_env_remove_node(data, args[a]);
		a++;
	}
	return (PASS);
}
