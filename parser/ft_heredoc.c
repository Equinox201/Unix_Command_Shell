#include "minishell.h"

bool	ft_if_quoted(char *s)
{
	if (!s)
		return (false);
	if (ft_find_quotes(s) == 1)
		return (true);
	return (false);
}

void	ft_parse_heredoc(t_token **token, t_command *cmd)
{
	int		len;

	if (!(*token)->next || (*token)->next->type != TOKEN_WORD)
		return ;
	if (cmd->file->heredoc_del)
	{
		ft_safe_str(cmd->file->heredoc_del);
		cmd->file->heredoc_del = NULL;
	}
	cmd->file->heredoc_quotes = ft_if_quoted((*token)->next->string);
	if (cmd->file->heredoc_quotes)
	{
		len = ft_quotelen((*token)->next->string, 0, 0);
		ft_handle_quotes((*token)->next, len, 0, 0);
	}
	cmd->file->heredoc_del = ft_strdup((*token)->next->string);
	cmd->file->heredoc_input = true;
	*token = (*token)->next->next;
}

void	ft_heredoc_input(t_command *cmd, t_data *data)
{
	t_command	*current;
	int			pipe_fd[2];

	current = cmd;
	if (!cmd || !data)
		return ;
	while (current)
	{
		if (current->file && current->file->heredoc_del
			&& current->file->heredoc_input)
		{
			if (pipe(pipe_fd) == -1)
				return ;
			ft_readline_heredoc(pipe_fd[1], current->file, data);
			close(pipe_fd[1]);
			current->file->fd_in = pipe_fd[0];
			current->file->heredoc_input = false;
		}
		current = current->next;
	}
}

char	*ft_expand_heredoc(char *line, t_data *data)
{
	char	*new_str;
	t_token	*tok;
	int		a;

	a = 0;
	tok = ft_tok_lstnew(line, 2);
	while (tok->string[a])
	{
		if (tok->string[a] == '$')
		{
			if (ft_expand_syntax(tok->string, a) == PASS)
				ft_expand_token(data, tok, a + 1);
		}
		a++;
	}
	new_str = ft_strdup(tok->string);
	ft_tok_delnode(tok);
	return (new_str);
}

void	ft_readline_heredoc(int write_fd, t_fds_io *io, t_data *data)
{
	char	*line;

	while (1)
	{
		ft_init_signals();
		line = readline("> ");
		ft_disable_signals();
		if (ft_line_handle(io, &line, data) != 0)
			break ;
		ft_putendl_fd(line, write_fd);
		ft_safe_str(line);
	}
	ft_safe_str(line);
}
