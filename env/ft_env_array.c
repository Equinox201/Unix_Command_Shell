#include "minishell.h"

char	**ft_recreate_env(t_env *og_env)
{
	char	**new_env;
	t_env	*tmp;
	int		a;

	a = 0;
	tmp = og_env;
	new_env = malloc(sizeof(char *) * (ft_env_lstsize(og_env) + 1));
	if (!new_env)
		return (NULL);
	while (tmp)
	{
		new_env[a] = ft_strdup(tmp->original);
		if (!new_env[a])
		{
			ft_safe_array((void ***)&new_env);
			return (NULL);
		}
		tmp = tmp->next;
		a++;
	}
	new_env[a] = NULL;
	return (new_env);
}

int	ft_reset_env(t_data *data)
{
	ft_safe_array((void ***)&data->env_cpy);
	data->env_cpy = ft_recreate_env(data->env);
	return (PASS);
}

int	ft_env_append_create(t_data *data, char *key, char *args)
{
	t_env	*tmp;

	tmp = ft_env_find_node(data, key);
	if (tmp == NULL)
		ft_env_new_node(data, args);
	else
		ft_env_edit_node(data, key, args);
	return (ft_reset_env(data));
}

int	ft_update_oldpwd(t_data *data)
{
	char	*pwd_cpy;
	t_env	*tmp;

	tmp = ft_env_find_node(data, "PWD");
	if (!tmp || !tmp->value)
		return (FAIL);
	pwd_cpy = ft_strjoin("OLDPWD=", tmp->value);
	ft_env_edit_node(data, "OLDPWD", pwd_cpy);
	ft_safe_str(pwd_cpy);
	return (PASS);
}
