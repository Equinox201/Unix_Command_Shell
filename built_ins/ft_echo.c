#include "minishell.h"

int	ft_flag_check(char *str)
{
	int	a;

	a = 0;
	if (str[a] != '-')
		return (0);
	a++;
	while (str[a] && str[a] == 'n')
		a++;
	if (str[a] == '\0')
		return (1);
	return (0);
}

void	ft_print_args(char **args, int start)
{
	int	a;

	a = start + 1;
	while (args[a])
	{
		ft_putstr_fd(args[a], STDOUT_FILENO);
		if (args[a + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		a++;
	}
	if (start == 0)
		ft_putchar_fd('\n', STDOUT_FILENO);
}

int	ft_echo(t_data *data, char **args, bool flag)
{
	int	a;
	int	b;

	a = 1;
	b = 0;
	(void)data;
	if (flag == true)
		return (EXIT_FAILURE);
	if (args[a] && ft_flag_check(args[a]) == 1)
	{
		b++;
		a++;
		while (args[a] && ft_flag_check(args[a]) == 1)
		{
			b++;
			a++;
		}
	}
	ft_print_args(args, b);
	return (EXIT_SUCCESS);
}
