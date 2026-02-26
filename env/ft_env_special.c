#include "minishell.h"

void	ft_update_last_cmd(t_data *data)
{
	int		a;
	char	*last_arg;
	char	*new_str;

	a = 0;
	if (!data || !data->cmd)
		return ;
	while (data->cmd->args[a] != NULL)
		a++;
	if (a == 0)
		return ;
	last_arg = ft_strdup(data->cmd->args[a - 1]);
	if (!last_arg)
		return ;
	new_str = ft_strjoin("_=", last_arg);
	ft_env_edit_node(data, "_", new_str);
	ft_safe_str(last_arg);
	ft_safe_str(new_str);
}

int	ft_check_newenv(char **env)
{
	int	a;

	a = 0;
	while (a < 3)
	{
		if (!env[a])
			return (FAIL);
		a++;
	}
	return (PASS);
}

char	**ft_force_create_env(void)
{
	char	**n;
	char	cwd[4096];
	char	*temp_wd;
	char	*new_wd;

	n = malloc(sizeof(char *) * 5);
	if (!n)
		return (NULL);
	temp_wd = getcwd(cwd, sizeof(cwd));
	new_wd = ft_strjoin("PWD=", temp_wd);
	n[0] = ft_strdup(new_wd);
	n[1] = ft_strdup("SHLVL=1");
	n[2] = ft_strdup("_=./minishell");
	n[3] = NULL;
	ft_safe_str(new_wd);
	if (ft_check_newenv(n) == FAIL)
	{
		ft_safe_array((void ***)&n);
		return (NULL);
	}
	return (n);
}

int	ft_update_shlvl(t_data *data)
{
	int		lvl;
	char	*new_lvl;
	char	*new_str;
	t_env	*tmp;

	tmp = ft_env_find_node(data, "SHLVL");
	if (!tmp || !tmp->value)
		return (FAIL);
	lvl = ft_atoi(tmp->value) + 1;
	new_str = ft_itoa(lvl);
	if (!new_str)
		return (FAIL);
	new_lvl = ft_strjoin("SHLVL=", new_str);
	ft_safe_str(new_str);
	ft_env_edit_node(data, "SHLVL", new_lvl);
	ft_safe_str(new_lvl);
	return (PASS);
}
