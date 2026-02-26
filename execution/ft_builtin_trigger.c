#include "minishell.h"

int	ft_builtin_trigger(t_data *data, t_command *cmd, int cmd_id)
{
	int	error_code;

	error_code = 127;
	if (cmd_id == bi_CD)
		error_code = ft_cd(data, cmd->args);
	else if (cmd_id == bi_ECHO)
	{
		if (cmd->file)
			error_code = ft_echo(data, cmd->args, cmd->file->flag);
		else
			error_code = ft_echo(data, cmd->args, false);
	}
	else if (cmd_id == bi_ENV)
		error_code = ft_env(data, cmd->args);
	else if (cmd_id == bi_EXIT)
		error_code = ft_exit(data, cmd->args);
	else if (cmd_id == bi_EXPORT)
		error_code = ft_export(data, cmd->args);
	else if (cmd_id == bi_PWD)
		error_code = ft_pwd(data, cmd->args);
	else if (cmd_id == bi_UNSET)
		error_code = ft_unset(data, cmd->args);
	return (error_code);
}

int	ft_identify_builtin(char *cmd)
{
	if (ft_strncmp(cmd, "cd", 3) == 0)
		return (bi_CD);
	if (ft_strncmp(cmd, "echo", 5) == 0)
		return (bi_ECHO);
	if (ft_strncmp(cmd, "env", 4) == 0)
		return (bi_ENV);
	if (ft_strncmp(cmd, "exit", 5) == 0)
		return (bi_EXIT);
	if (ft_strncmp(cmd, "export", 7) == 0)
		return (bi_EXPORT);
	if (ft_strncmp(cmd, "pwd", 4) == 0)
		return (bi_PWD);
	if (ft_strncmp(cmd, "unset", 6) == 0)
		return (bi_UNSET);
	return (0);
}

int	ft_builtin_exec(t_data *data, t_command *cmd)
{
	int	error_code;
	int	cmd_id;

	cmd_id = ft_identify_builtin(cmd->args[0]);
	if (cmd_id == 0)
		return (127);
	error_code = ft_builtin_trigger(data, cmd, cmd_id);
	return (error_code);
}
