#include "minishell.h"

int	ft_init_data(t_data *data, char **envar)
{
	if (!data || !envar)
		return (FAIL);
	data->token = NULL;
	data->exit_status = 0;
	data->user_input = NULL;
	data->error_code = 0;
	data->cmd = NULL;
	data->env = NULL;
	if (envar)
	{
		ft_env_lst_create(data, envar);
		data->env_cpy = ft_copy_env(envar);
	}
	return (ft_init_check(data));
}

int	ft_init_check(t_data *data)
{
	if (data->env_cpy == NULL)
		return (FAIL);
	if (data->env == NULL)
		return (FAIL);
	return (PASS);
}

char	**ft_copy_env(char **envar)
{
	char	**new_env;
	int		a;
	int		b;

	a = 0;
	b = 0;
	if (!envar)
		return (NULL);
	while (envar[a])
		a++;
	new_env = malloc((a + 1) * sizeof(char *));
	if (!new_env)
		return (NULL);
	while (b < a)
	{
		new_env[b] = ft_strdup(envar[b]);
		if (!new_env[b])
		{
			ft_safe_array((void ***)&new_env);
			return (NULL);
		}
		b++;
	}
	new_env[b] = NULL;
	return (new_env);
}

void	ft_env_lst_create(t_data *data, char **envar)
{
	int	a;

	a = 0;
	if (!envar)
		return ;
	while (envar[a])
	{
		ft_env_add_node(&data->env, envar[a]);
		a++;
	}
}
