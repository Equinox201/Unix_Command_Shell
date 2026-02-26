#include "minishell.h"

int	ft_data_sig_start(t_data *data, char **env)
{
	char	**force_env;

	if (!env || !env[0])
	{
		force_env = ft_force_create_env();
		if (!force_env)
			return (FAIL);
		data->empty_env = true;
		if (ft_init_data(data, force_env) != PASS)
			return (ft_error_message("Usage", NULL, "Failed to initiate data",
					FAIL));
	}
	else
	{
		data->empty_env = false;
		if (ft_init_data(data, env) != PASS)
			return (ft_error_message("Usage", NULL, "Failed to initiate data",
					FAIL));
		ft_update_shlvl(data);
	}
	return (PASS);
}

int	ft_start_minishell(t_data *data)
{
	char	*prompt;

	ft_print_welcome();
	while (1)
	{
		ft_init_signals();
		prompt = ft_get_prompt(data->empty_env);
		data->user_input = readline(prompt);
		ft_safe_str(prompt);
		if (g_signal_code == 130)
		{
			data->error_code = 130;
			g_signal_code = 0;
		}
		ft_disable_signals();
		ft_start(data);
		ft_free_data_struct(data);
	}
	return (data->error_code);
}

int	main(int argc, char **argv, char **env)
{
	t_data	*data;
	int		error_code;

	error_code = 0;
	if (argc != 1 || argv[1])
		return (ft_error_message("Usage", NULL,
				"enter \"./minishell\" to start program", FAIL));
	data = malloc(sizeof(t_data));
	if (!data)
		return (0);
	if (ft_data_sig_start(data, env) == FAIL)
	{
		ft_free_data_struct(data);
		exit(EXIT_FAILURE);
	}
	error_code = ft_start_minishell(data);
	ft_full_exit(data, error_code);
	return (0);
}
