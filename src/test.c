#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char	**ft_strduparr(char **arr)
{
	int		count;
	char	**copy;

	count = 0;
	if (arr == NULL)
		return (NULL);
	while (arr[count] != NULL)
		++count;
	copy = (char **) malloc(sizeof(char *) * (count + 1));
	if (copy == NULL)
		return (NULL);
	copy[count] = NULL;
	while (count-- > 0 && arr[count] != NULL)
		copy[count] = strdup(arr[count]);
	return (copy);
}

size_t	ft_arrlen(char **arr)
{
	size_t	len;

	len = 0;
	while (arr != NULL && arr[len] != NULL)
		++len;
	return (len);
}

char	**ft_arrndup(char **arr, size_t n)
{
	char	**dup;

	dup = (char **) malloc(sizeof(char *) * (n + 1));
	if (dup == NULL)
		return (NULL);
	dup[n] = NULL;
	while (n-- > 0)
		dup[n] = strdup(arr[n]);
	return (dup);
}

static void	ft_mv_end(char **arr, size_t position)
{
	size_t	i;
	char	*temp;

	i = position;
	while (arr != NULL && arr[i] != NULL)
	{
		printf("loop: %s\n", arr[i]);
		if (arr[i + 1] != NULL)
		{
			temp = arr[i];
			printf("temp: %s\n", temp);
			arr[i] = arr[i + 1];
			arr[i + 1] = temp;
		}
		++i;
	}
	free(arr[i]);
	arr[i] = NULL;
}

int	ft_redirections_rm(char **job)
{
	int	i;

	i = ft_arrlen(job) - 1;
	while (job != NULL && job[i] != NULL)
	{
		if (*job == job[i])
			break ;
		if (*(job[i - 1]) == 074 || *(job[i - 1]) == 076)
		{
			ft_mv_end(job, i);
			//ft_mv_end(job, i - 1);
		}
		--i;
	}
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	char	**arr;

	(void) argc;
	arr = ft_strduparr(argv + 1);
	ft_redirections_rm(arr);

	int	i = 0;
	while (arr != NULL && arr[i] != NULL)
	{
		printf("%s\n", arr[i]);
		++i;
	}
	return (0);
}
