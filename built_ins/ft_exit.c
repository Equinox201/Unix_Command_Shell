#include "minishell.h"

long	ft_atol(const char *str)
{
	int		a;
	long	sign;
	long	new;

	a = 0;
	sign = 1;
	new = 0;
	while (str[a] == 32 || (str[a] >= 9 && str[a] <= 13))
		a++;
	if (str[a] == '-' || str[a] == '+')
	{
		if (str[a] == '-')
			sign *= -1;
		a++;
	}
	while (str[a] >= '0' && str[a] <= '9')
	{
		new = (new * 10) + (str[a] - '0');
		a++;
	}
	return (new * sign);
}

int	ft_skip(char *num_str, int *a)
{
	while (num_str[*a] == 32 || (num_str[*a] >= 9 && num_str[*a] <= 13))
		(*a)++;
	if (num_str[*a] == '+' || num_str[*a] == '-')
		(*a)++;
	return (*a);
}

int	ft_extract_num(t_data *data, char *num_str, int *ctrl, int a)
{
	long	number;

	if (!num_str)
		return (data->error_code);
	a = ft_skip(num_str, &a);
	if (!ft_isdigit(num_str[a]))
	{
		*ctrl = 1;
		return (data->error_code);
	}
	while (num_str[a])
	{
		if (!ft_isdigit(num_str[a]))
		{
			*ctrl = 1;
			return (2);
		}
		a++;
	}
	number = ft_atol(num_str);
	if (number > INT_MAX || number < INT_MIN)
		*ctrl = 1;
	return (number % 256);
}

int ft_args_len(char **args)
{
	int a;

	a = 0;
	if (!args)
		return (0);
	while (args[a] != NULL)
		a ++;
	return (a);
}

int	ft_exit(t_data *data, char **args)
{
	int	ex_code;
	int	ctrl;
	int	solo;
	int len;

	ex_code = 0;
	solo = 0;
	ctrl = 0;
	len = ft_args_len(args);
	if (data->cmd->next != NULL || data->cmd->prev != NULL)
		solo = 1;
	if (solo == 0 && len <= 2)
		ft_print_exit();
	if (!args || !args[1])
		ex_code = data->error_code;
	else
	{
		ex_code = ft_extract_num(data, args[1], &ctrl, 0);
		if (ctrl == 1)
			ex_code = ft_error_message("exit", args[1],
					"numeric argument required", 2);
		else if (args[2])
			return (ft_error_message("exit", NULL, "too many arguments", 1));
	}
	ft_full_exit(data, ex_code);
	return (2);
}
