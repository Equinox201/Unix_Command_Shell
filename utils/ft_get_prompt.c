#include "minishell.h"

int	ft_len(char *str)
{
	int	len;
	int	a;

	len = 0;
	a = 6;
	while (str[a] && ft_isalnum(str[a]) == 1)
	{
		a++;
		len++;
	}
	if (len == 0)
		return (7);
	return (len);
}

char	*ft_fetch_comp(char *prompt)
{
	char	*temp;
	char	*comp;
	char	*new;
	char	*ses_man;

	comp = NULL;
	ses_man = getenv("SESSION_MANAGER");
	if (ses_man != NULL)
		comp = ft_substr(ses_man, ft_strlen("local/"), ft_len(ses_man));
	if (!comp)
		comp = ft_strdup("unknown");
	new = ft_strjoin(prompt, comp);
	free(prompt);
	free(comp);
	temp = new;
	new = ft_strjoin(temp, ":");
	free(temp);
	return (ft_edit_cwd(new, 0));
}

int	ft_check_home(char *cwd)
{
	char	*home;
	int		len;

	home = ft_strdup(getenv("HOME"));
	if (!home)
		return (0);
	len = ft_strlen(home);
	if (ft_strncmp(cwd, home, len - 1) == 0)
	{
		ft_safe_str(home);
		return (len);
	}
	ft_safe_str(home);
	return (0);
}

char	*ft_edit_cwd(char *prompt, int a)
{
	char	cwd[4096];
	char	*temp;
	char	*new_prompt;
	char	*tild;

	if (getcwd(cwd, sizeof(cwd)) == NULL)
		return (prompt);
	a = ft_check_home(cwd);
	if (a != 0)
	{
		temp = ft_substr(cwd, a, ft_strlen(cwd) - a);
		if (!temp)
			return (prompt);
		tild = ft_strjoin(prompt, "~");
		new_prompt = ft_strjoin(tild, temp);
		ft_safe_str(temp);
		ft_safe_str(tild);
		ft_safe_str(prompt);
		return (new_prompt);
	}
	new_prompt = ft_strjoin(prompt, cwd);
	ft_safe_str(prompt);
	return (new_prompt);
}

char	*ft_get_prompt(bool empty_env)
{
	char	*final;
	char	*temp;
	char	*new_prompt;

	if (empty_env == true)
	{
		new_prompt = ft_strdup("(empty env): Minishell$ ");
		return (new_prompt);
	}
	final = ft_strdup(getenv("USER"));
	if (!final)
		final = ft_strdup("unknown");
	temp = ft_strjoin(final, "@");
	free(final);
	temp = ft_fetch_comp(temp);
	new_prompt = ft_strjoin(temp, "$ ");
	free(temp);
	return (new_prompt);
}
