#include "minishell.h"

int	ft_division_check(char *str)
{
	int	a;

	a = 0;
	while (str[a])
	{
		if (str[a] == ' ')
			return (1);
		a++;
	}
	return (0);
}

char	**ft_increase_size(t_command *curr, size_t old_size)
{
	char	**new_str;
	size_t	a;

	a = 0;
	new_str = malloc(sizeof(char *) * (old_size + 2));
	if (!new_str)
		return (NULL);
	while (a < old_size)
	{
		new_str[a] = curr->args[a];
		a++;
	}
	new_str[a] = NULL;
	new_str[a + 1] = NULL;
	free(curr->args);
	return (new_str);
}

void	ft_fill_single_command(t_command *cmd, const char *arg, int count)
{
	char	**temp;

	if (!arg || arg[0] == '\0')
		return ;
	if (!cmd->args)
	{
		cmd->args = malloc(sizeof(char *) * 2);
		if (!cmd->args)
			return ;
		cmd->args[0] = ft_strdup(arg);
		cmd->args[1] = NULL;
		return ;
	}
	while (cmd->args[count])
		count++;
	temp = ft_increase_size(cmd, count);
	if (!temp)
		return ;
	cmd->args = temp;
	if (count == 1 && ft_strcmp(cmd->args[0], "echo") != 0)
		cmd->args[count] = ft_strtrim_front(arg, " \t\n\v\f\r");
	else
		cmd->args[count] = ft_strdup(arg);
	cmd->args[count + 1] = NULL;
}

void	ft_fill_multi_command(t_command *cmd, const char *arg)
{
	char	**split_str;
	int		a;

	a = 0;
	split_str = ft_split(arg, ' ');
	if (!split_str)
		return ;
	while (split_str[a])
	{
		ft_fill_single_command(cmd, split_str[a], 0);
		a++;
	}
	ft_safe_array((void ***)&split_str);
}

void	ft_handle_var_word(t_data *data, t_token **tok)
{
	t_command	*last_cmd;
	t_token		*temp;

	temp = *tok;
	last_cmd = ft_last_command(data->cmd);
	while (temp->type == 2 || temp->type == 3)
	{
		if (temp->prev == NULL || (temp->prev && temp->prev->type == 4)
			|| last_cmd->args == NULL)
		{
			if (temp->type == 3 && ft_division_check(temp->string) == 1)
				ft_fill_multi_command(last_cmd, temp->string);
			else
				ft_fill_single_command(last_cmd, temp->string, 0);
		}
		else
			ft_fill_single_command(last_cmd, temp->string, 0);
		temp = temp->next;
	}
	(*tok) = temp;
}
