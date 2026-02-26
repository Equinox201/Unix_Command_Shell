#include "minishell.h"

int		g_signal_code = 0;

void	ft_new_line(int sig)
{
	(void)sig;
	g_signal_code = 130;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	ft_reset_line(int sig)
{
	(void)sig;
	rl_on_new_line();
}

void	ft_handle_sigquit(void)
{
	struct sigaction	sig_quit;

	ft_memset(&sig_quit, 0, sizeof(sig_quit));
	sig_quit.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sig_quit, NULL);
}

void	ft_init_signals(void)
{
	struct sigaction	sig_init;

	ft_handle_sigquit();
	ft_memset(&sig_init, 0, sizeof(sig_init));
	sig_init.sa_handler = &ft_new_line;
	sigaction(SIGINT, &sig_init, NULL);
}

void	ft_disable_signals(void)
{
	struct sigaction	sig_end;

	ft_memset(&sig_end, 0, sizeof(sig_end));
	sig_end.sa_handler = &ft_reset_line;
	sigaction(SIGINT, &sig_end, NULL);
	sigaction(SIGQUIT, &sig_end, NULL);
}
