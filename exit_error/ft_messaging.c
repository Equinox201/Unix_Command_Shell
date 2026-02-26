#include "minishell.h"

char	*ft_dup_or_join(char *s1, char *s2)
{
	if (!s2)
		return (ft_strdup(s1));
	if (!s1)
		return (ft_strdup(s2));
	else
		return (ft_strjoin(s1, s2));
}

char	*ft_check_quotes(char *final, char *cmd, char *dtl)
{
	char	*temp;

	if (ft_strncmp(cmd, "export", 7) == 0 || ft_strncmp(cmd, "unset", 6) == 0)
	{
		temp = ft_dup_or_join(final, "'");
		ft_safe_str(final);
		final = temp;
		temp = ft_dup_or_join(final, dtl);
		ft_safe_str(final);
		final = temp;
		temp = ft_dup_or_join(final, "'");
		ft_safe_str(final);
		final = temp;
		return (final);
	}
	else
	{
		temp = ft_dup_or_join(final, dtl);
		ft_safe_str(final);
		final = temp;
	}
	temp = ft_strjoin(final, ": ");
	ft_safe_str(final);
	final = temp;
	return (final);
}

int	ft_error_message(char *cmd, char *dtl, char *msg, int err_code)
{
	char	*final;
	char	*temp;

	if (cmd)
		final = ft_dup_or_join(cmd, ": ");
	if (dtl)
		final = ft_check_quotes(final, cmd, dtl);
	if (!cmd && !dtl)
		final = ft_strdup(msg);
	else
	{
		temp = ft_strjoin(final, msg);
		ft_safe_str(final);
		final = temp;
	}
	ft_print_error(final);
	ft_safe_str(final);
	return (err_code);
}

void	ft_messaging(char *msg, char *dtl)
{
	char	*final;

	final = ft_dup_or_join(msg, dtl);
	ft_print_error(final);
	ft_safe_str(final);
}

void	ft_print_error(char *message)
{
	ft_putstr_fd("Minishell: ", STDERR_FILENO);
	ft_putendl_fd(message, STDERR_FILENO);
}
