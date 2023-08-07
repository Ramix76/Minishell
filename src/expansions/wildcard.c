/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framos-p <framos-p@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 14:48:38 by framos-p          #+#    #+#             */
/*   Updated: 2023/07/26 17:16:36 by framos-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <string.h>

static t_list	*ft_getentries(char *expanded);
static int		ft_matches_pattern(char *pattern, char *d_name);
static char		*ft_concat_list(t_list *list);

char	*ft_expand_wildcard(char *str, t_data *data)
{
	char	*temp;
	char	*expanded;
	t_list	*list;

	expanded = ft_strdup(str);
	list = ft_getentries(expanded);
	if (list == NULL)
		return (expanded);
	else
	{
		temp = expanded;
		expanded = ft_concat_list(list);
		ft_lstclear(&list, &free);
		free(list);
		free(temp);
	}
	return (expanded);
	(void) data;
}

static t_list	*ft_getentries(char *expanded)
{
	DIR				*dir;
	struct dirent	*entry;
	t_list			*list;
	char			*name;

	list = NULL;
	dir = opendir(".");
	if (dir == NULL)
		return (ft_fprintf(stderr, "%s: %s\n", SH_NAME, strerror(errno)), NULL);
	entry = readdir(dir);
	while (entry != NULL)
	{
		if (ft_strcmp(".", entry->d_name) != 0
			&& ft_strcmp("..", entry->d_name) != 0
			&& ft_matches_pattern(expanded, entry->d_name) == EXIT_SUCCESS)
		{
			name = ft_strdup(entry->d_name);
			ft_lstadd_back(&list, ft_lstnew(name));
		}
		entry = readdir(dir);
	}
	closedir(dir);
	return (list);
}

/* function assumes that pattern is never NULL */

static int	ft_matches_pattern(char *pattern, char *name)
{
	int		prefix;
	int		suffix;
	char	*asterisc;

	prefix = 0;
	suffix = 0;
	asterisc = ft_strchr(pattern, '*');
	if (asterisc != pattern)
		prefix = asterisc - pattern;
	if (*(asterisc + 1) != '\0')
		suffix = ft_strlen(asterisc + 1);
	if (ft_strncmp(pattern, name, prefix) == 0)
	{
		ft_strrev(pattern);
		ft_strrev(name);
		if (ft_strncmp(pattern, name, suffix) == 0)
		{
			ft_strrev(pattern);
			return (ft_strrev(name), EXIT_SUCCESS);
		}
		ft_strrev(pattern);
		ft_strrev(name);
	}
	return (EXIT_FAILURE);
}

static char	*ft_concat_list(t_list *list)
{
	size_t	len;
	char	*concat;
	t_list	*lst;

	len = 0;
	if (list == NULL)
		return (NULL);
	lst = list;
	while (lst != NULL)
	{
		len += ft_strlen(lst->content);
		lst = lst->next;
		++len;
	}
	concat = (char *) malloc(sizeof(char) * len);
	ft_memset(concat, '\0', len);
	lst = list;
	while (lst != NULL)
	{
		ft_strlcat(concat, lst->content, len);
		ft_strlcat(concat, " ", len);
		lst = lst->next;
	}
	return (concat);
}
