#include "minishell.h"

void	exec_manager(void)
{
	t_ms	*ms;
	t_list	*cmds;

	ms = get_ms();
	cmds = ms->cmds;
	if (ft_lstsize(cmds) == 1)
	{
		single_cmd_exec(cmds->content);
		return ;
	}
	pipex(ms, cmds);
}

void    single_cmd_exec(t_cmd *cmd)
{
    pid_t   pid;
	int		status;

	if (!ft_strncmp(cmd->cmd_arr[0], "exit", 5))
		ft_exit(get_ms());
    pid = fork();
    if (pid == 0)
    {
		handle_redir_in(cmd);
		handle_redir_out(cmd);
		dup2(cmd->fd_in, STDIN_FILENO);
		dup2(cmd->fd_out, STDOUT_FILENO);
		execute_cmd(cmd);
	}
    waitpid(pid, &status, 0);
	catch_last_status(&status);
}