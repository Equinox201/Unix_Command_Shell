#include "minishell.h"

void	print_token_type(t_token *token, char *prefix)
{
	printf("%s", prefix);
	if (token->type == TOKEN_SPACES)
		printf("SPACES\n");
	else if (token->type == TOKEN_WORD)
		printf("WORD\n");
	else if (token->type == TOKEN_VAR)
		printf("VAR\n");
	else if (token->type == TOKEN_PIPE)
		printf("PIPE\n");
	else if (token->type == TOKEN_INPUT)
		printf("INPUT\n");
	else if (token->type == TOKEN_TRUNC)
		printf("TRUNC\n");
	else if (token->type == TOKEN_HEREDOC)
		printf("HEREDOC\n");
	else if (token->type == TOKEN_APPEND)
		printf("APPEND\n");
	else if (token->type == TOKEN_END)
		printf("END\n");
}

void	print_token_list(t_token **tokens)
{
	t_token	*lst;
	int		i;

	lst = *tokens;
	printf("\n---- TOKEN LIST\n");
	i = 0;
	while (lst)
	{
		printf("--- Token [%d] [%p]\n", i, lst);
		printf("\tString = [%s]\n", lst->string);
		printf("\tStr backup = [%s]\n", lst->store_string);
		print_token_type(lst, "\tType = ");
		printf("\tStatus = %d\n", lst->status);
		if (lst->prev)
			printf("\tPrev = [%p]\n", lst->prev);
		else
			printf("\tPrev = NULL\n");
		if (lst->next)
			printf("\tNext = [%p]\n", lst->next);
		else
			printf("\tNext = NULL\n");
		i++;
		lst = lst->next;
	}
}

static void	test_print_cmd_args(t_command *cmd)
{
	int	i;

	if (!cmd->args)
		return ;
	i = 0;
	while (cmd->args[i])
	{
		printf("\tArgs[%d] = %s\n", i, cmd->args[i]);
		i++;
	}
}

static void	test_print_cmd_io(t_command *cmd)
{
	if (!cmd->file)
	{
		printf("\tNo file struct\n");
		return ;
	}
	if (cmd->file->filein)
	{
		printf("\tInfile: %s\n", cmd->file->filein);
		printf("\t\tfd_in: %d\n", cmd->file->fd_in);
	}
	if (!cmd->file->filein)
		printf("\tInfile: (NULL) \n");
	if (cmd->file->heredoc_del)
		printf("\tHeredoc delimiter: %s\n", cmd->file->heredoc_del);
	if (cmd->file->fileout)
	{
		printf("\tOutfile: %s\n", cmd->file->fileout);
		printf("\t\tfd_out: %d\n", cmd->file->fd_out);
	}
	if (!cmd->file->fileout)
		printf("\tOutfile: (NULL) \n");
}

void	test_print_cmd_list(t_data *data)
{
	t_command	*cmd;

	cmd = data->cmd;
	printf("\n---- COMMAND LIST\n");
	while (cmd)
	{
		printf("--- Command = %s\n", cmd->args[0]);
		test_print_cmd_args(cmd);
		printf("\tPipe_output = %d\n", cmd->pipe_output);
		test_print_cmd_io(cmd);
		printf("\tPrev: %p, \n", (void *)cmd->prev);
		printf("\tNext: %p\n", (void *)cmd->next);
		printf("\n");
		cmd = cmd->next;
	}
	printf("\n");
}
