#include "minishell.h"

void	ft_parse_input(t_token *t, t_fds_io *f)
{
	if (f && f->flag == true)
		return ;
	if (f && f->filein)
	{
		if (f->fd_in == -1 || (f->fileout && f->fd_out == -1))
			return ;
		ft_safe_str(f->filein);
		close(f->fd_in);
	}
	f->filein = ft_strdup(t->next->string);
	if (f->filein && f->filein[0] == '\0')
	{
		ft_error_message(t->next->store_string, NULL,
			"ambiguous redirect", 0);
		f->flag = true;
		return ;
	}
	f->fd_in = open(f->filein, O_RDONLY);
	if (f->fd_in == -1)
	{
		ft_error_message(f->filein, NULL, strerror(errno), 0);
		f->flag = true;
	}
}

void	ft_parse_append(t_token *t, t_fds_io *f)
{
	if (f && f->flag == true)
		return ;
	if (f && f->fileout)
	{
		if (f->fd_out == -1 || (f->filein && f->fd_in == -1))
			return ;
		ft_safe_str(f->fileout);
		close(f->fd_out);
	}
	f->fileout = ft_strdup(t->next->string);
	if (f->fileout && f->fileout[0] == '\0')
	{
		ft_error_message(t->next->store_string, NULL,
			"ambiguous redirect", 0);
		f->flag = true;
		return ;
	}
	f->fd_out = open(f->fileout, O_WRONLY | O_CREAT | O_APPEND, 0664);
	if (f->fd_out == -1)
	{
		ft_error_message(f->fileout, NULL, strerror(errno), 0);
		f->flag = true;
	}
}

void	ft_parse_trunc(t_token *t, t_fds_io *f)
{
	if (f && f->flag == true)
		return ;
	if (f && f->fileout)
	{
		if (f->fd_out == -1 || (f->filein && f->fd_in == -1))
			return ;
		ft_safe_str(f->fileout);
		close(f->fd_out);
	}
	f->fileout = ft_strdup(t->next->string);
	if (f->fileout && f->fileout[0] == '\0')
	{
		ft_error_message(t->next->store_string, NULL,
			"ambiguous redirect", 0);
		f->flag = true;
		return ;
	}
	f->fd_out = open(f->fileout, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (f->fd_out == -1)
	{
		ft_error_message(f->fileout, NULL, strerror(errno), 0);
		f->flag = true;
	}
}

void	ft_handle_redirect(t_data *data, t_token **token)
{
	t_token		*tok;
	t_command	*last_cmd;

	tok = *token;
	last_cmd = ft_last_command(data->cmd);
	if (!last_cmd->file)
		last_cmd->file = ft_create_new_file();
	if ((*token)->type == TOKEN_HEREDOC)
	{
		ft_parse_heredoc(token, last_cmd);
		return ;
	}
	else if ((*token)->type == TOKEN_INPUT)
		ft_parse_input(tok, last_cmd->file);
	else if ((*token)->type == TOKEN_TRUNC)
		ft_parse_trunc(tok, last_cmd->file);
	else if ((*token)->type == TOKEN_APPEND)
		ft_parse_append(tok, last_cmd->file);
	if (tok->next->next)
		(*token) = tok->next->next;
	else
		(*token) = tok->next;
}
