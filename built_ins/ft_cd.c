#include "minishell.h"

void	ft_refresh_directory(t_data *data, char *new_wd)
{
	t_env	*temp;
	char	*full;
	char	*oldpwd;

	temp = ft_env_find_node(data, "PWD");
	if (temp)
	{
		oldpwd = ft_strjoin("OLDPWD=", temp->value);
		ft_env_append_create(data, "OLDPWD", oldpwd);
		ft_safe_str(oldpwd);
	}
	full = ft_strjoin("PWD=", new_wd);
	ft_env_append_create(data, "PWD", full);
	ft_safe_str(full);
}

int	ft_execute_cd(t_data *data, char *path)
{
	char	cwd[4096];
	char	*new_wd;

	new_wd = NULL;
	if (chdir(path) != 0)
	{
		if (errno == ESTALE)
			errno = ENOENT;
		ft_error_message("cd", path, strerror(errno), errno);
		return (FAIL);
	}
	new_wd = getcwd(cwd, sizeof(cwd));
	if (!new_wd)
	{
		ft_error_message("cd: error retrieving current directory",
			"getcwd: cannot access parent directories", strerror(errno), errno);
		new_wd = ft_strjoin("PWD=/", path);
	}
	else
		new_wd = ft_strdup(cwd);
	ft_refresh_directory(data, new_wd);
	ft_safe_str(new_wd);
	return (PASS);
}

int	ft_valid_arguments(char **array)
{
	if (!array || !array[1] || array[1][0] == '\0' || ft_strcmp(array[1],
			"~") == 0)
		return (1);
	if (array[2])
		return (0);
	if (array[1][0] == 32 || ft_strncmp(array[1], "--", 3) == 0)
		return (1);
	if (ft_strncmp(array[1], "-", 2) == 0)
		return (2);
	return (3);
}

char	*ft_cd_pathfinder(t_data *data, int ctrl)
{
	t_env	*temp;

	temp = NULL;
	if (ctrl == 1)
	{
		temp = ft_env_find_node(data, "HOME");
		if (!temp || !temp->value || temp->value[0] == '\0')
		{
			ft_error_message("cd", NULL, "HOME not set", FAIL);
			return (NULL);
		}
		return (ft_strdup(temp->value));
	}
	else
	{
		temp = ft_env_find_node(data, "OLDPWD");
		if (!temp || !temp->value)
		{
			ft_error_message("cd", NULL, "OLDPWD not set", FAIL);
			return (NULL);
		}
		return (ft_strdup(temp->value));
	}
}

int	ft_cd(t_data *data, char **args)
{
	int		ctrl;
	int		error_code;
	char	*dest;

	ctrl = ft_valid_arguments(args);
	if (ctrl == 0)
		return (ft_error_message("cd", NULL, "too many arguments", FAIL));
	if (ctrl == 1 || ctrl == 2)
		dest = ft_cd_pathfinder(data, ctrl);
	else
		dest = ft_strdup(args[1]);
	if (!dest)
		return (FAIL);
	error_code = ft_execute_cd(data, dest);
	free(dest);
	return (error_code);
}
