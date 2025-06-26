/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgalizio <jgalizio@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 20:34:31 by jgalizio          #+#    #+#             */
/*   Updated: 2024/11/10 18:29:22 by jgalizio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	update_brace_count(char c, char *open_braces)
{
	int	opening_index;
	int	closing_index;

	opening_index = ft_strchr_index("'\"([{", c);
	closing_index = ft_strchr_index("'\")]}", c);
	if (c == '\'' || c == '"')
	{
		if (c == '\'' && open_braces[0] == '0')
			open_braces[0] = '1';
		else if (c == '\'' && open_braces[0] == '1')
			open_braces[0] = '0';
		if (c == '"' && open_braces[1] == '0')
			open_braces[1] = '1';
		else if (c == '"' && open_braces[1] == '1')
			open_braces[1] = '0';
	}
	else
	{
		if (opening_index != -1)
			open_braces[opening_index]++;
		else if (closing_index != -1)
			open_braces[closing_index]--;
	}
}

static size_t	count_tokens(char const *s)
{
	size_t	counter;
	int		inside_token;
	char	*open_braces;

	counter = 0;
	inside_token = 0;
	open_braces = ft_strdup("00000");
	while (*s)
	{
		if (*s != ' ' && !inside_token)
		{
			inside_token = 1;
			counter++;
		}
		else if (*s == ' ' && !ft_strncmp(open_braces, "00000", 5))
			inside_token = 0;
		update_brace_count(*s, open_braces);
		s++;
	}
	free(open_braces);
	open_braces = NULL;
	return (counter);
}

static int	get_sublen(const char *s)
{
	char			*open_braces;
	size_t			subs_str_len;

	subs_str_len = 0;
	open_braces = ft_strdup("00000");
	while (s[subs_str_len]
		&& (s[subs_str_len] != ' ' || ft_strncmp(open_braces, "00000", 5)))
	{
		update_brace_count(s[subs_str_len], open_braces);
		subs_str_len++;
	}
	free(open_braces);
	open_braces = NULL;
	return (subs_str_len);
}

static char	**set_substrs(char const *s, char **str, size_t token_count)
{
	size_t	current_str;
	size_t	subs_str_len;

	current_str = 0;
	while (current_str < token_count && *s)
	{
		if (*s != ' ')
		{
			subs_str_len = get_sublen(s);
			str[current_str] = ft_calloc(subs_str_len + 1, sizeof(char));
			if (!str[current_str])
				return (NULL);
			ft_strlcpy(str[current_str], s, subs_str_len + 1);
			s += subs_str_len;
			current_str++;
		}
		else
			s++;
	}
	str[current_str] = NULL;
	return (str);
}

char	**command_split(char const *s)
{
	size_t	token_count;
	char	**str_splitted;

	token_count = count_tokens(s);
	str_splitted = ft_calloc((token_count + 1), sizeof(char *));
	if (!str_splitted)
		return (NULL);
	if (!set_substrs(s, str_splitted, token_count))
	{
		ft_free_matrix((void **)str_splitted);
		str_splitted = NULL;
		return (NULL);
	}
	return (str_splitted);
}
