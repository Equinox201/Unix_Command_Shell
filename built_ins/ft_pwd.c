#include "minishell.h"

int	ft_pwd(t_data *data, char **args)
{
	char	buffer[4096];
	char	*pwd;

	(void)data;
	(void)args;
	pwd = NULL;
	pwd = getcwd(buffer, 4096);
	if (!pwd)
	{
		ft_error_message("pwd", NULL, strerror(errno), errno);
		return (EXIT_FAILURE);
	}
	ft_putendl_fd(pwd, STDOUT_FILENO);
	return (EXIT_SUCCESS);
}
