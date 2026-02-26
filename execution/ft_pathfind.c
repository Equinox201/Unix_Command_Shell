#include "minishell.h"

char	*ft_raw_path_extract(t_data *data)
{
	char	*raw_path;
	t_env	*tmp;

	raw_path = NULL;
	tmp = ft_env_find_node(data, "PATH");
	if (!tmp)
		return (NULL);
	raw_path = ft_strdup(tmp->value);
	return (raw_path);
}

char	**ft_final_path(char **paths)
{
	int		a;
	char	*buffer;

	a = 0;
	while (paths[a])
	{
		buffer = paths[a];
		paths[a] = ft_strjoin(paths[a], "/");
		free(buffer);
		a++;
	}
	return (paths);
}

char	**ft_env_extraction(t_data *data)
{
	char	*raw_path;
	char	**exec_paths;

	raw_path = ft_raw_path_extract(data);
	if (raw_path == NULL)
		return (NULL);
	exec_paths = ft_split(raw_path, ':');
	free(raw_path);
	if (exec_paths == NULL)
		return (NULL);
	exec_paths = ft_final_path(exec_paths);
	if (exec_paths == NULL)
		return (NULL);
	return (exec_paths);
}

char	*ft_sys_cmd_line(char *cmd, char **exec_paths)
{
	int		a;
	char	*full_cmd;

	a = 0;
	full_cmd = NULL;
	while (exec_paths[a])
	{
		full_cmd = ft_strjoin(exec_paths[a], cmd);
		if (!full_cmd)
			ft_safe_array((void ***)&exec_paths);
		if (access(full_cmd, F_OK | X_OK) == 0)
			return (full_cmd);
		free(full_cmd);
		a++;
	}
	return (NULL);
}

char	*ft_command_create(t_data *data, char *cmd)
{
	char	**exec_paths;
	char	*full_cmd;

	full_cmd = NULL;
	exec_paths = ft_env_extraction(data);
	if (exec_paths != NULL)
	{
		full_cmd = ft_sys_cmd_line(cmd, exec_paths);
		ft_safe_array((void ***) &exec_paths);
	}
	return (full_cmd);
}
