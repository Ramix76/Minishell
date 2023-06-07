#include "minishell.h"
#include "libft.h"
#include "test.utils.h"

int	main(int argc, char **argv, const char **envp)
{
	char	*name;
	char	*path;

	init_log(argc, argv, (char **) envp);

	path = ft_getenv("PATH", envp);
	printf("og_getenv: %s\n", getenv("PATH"));
	printf("og_getenv: %s\n", getenv(NULL));
	printf("ft_getenv: %s\n", path);

	name = "cat -e";
	printf("ft_which: %s\n", ft_which(name, ft_getenv("PATH", envp)));
	printf("ft_which: %s\n", ft_which(name, NULL));
	printf("ft_which: %s\n", ft_which(NULL, path));
	return (0);
}
