#include "libft.h"

int	main(int argc, char **argv, char **envp)
{
	char	*cmd;
	(void) argc;
	(void) argv;
	++argv;
	cmd = argv[0];
	if (ft_execvpe((const char *) cmd, (const char **) argv, (const char **) envp) == -1)
		return (1);
	return (0);
}
