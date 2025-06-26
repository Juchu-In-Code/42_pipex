/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgalizio <jgalizio@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 16:36:33 by jgalizio          #+#    #+#             */
/*   Updated: 2024/11/09 17:59:25 by jgalizio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*get_valid_path_for_cmd(char *command, char **path)
{
	char	*added_slash;
	char	*current_path;
	int		i;

	i = 0;
	if (ft_strchr(command, '/'))
		if (access(command, F_OK | X_OK) == 0)
			return (command);
	while (path[i])
	{
		added_slash = ft_strjoin(path[i], "/");
		if (!added_slash)
			return (NULL);
		current_path = ft_strjoin(added_slash, command);
		free (added_slash);
		added_slash = NULL;
		if (!current_path)
			return (NULL);
		if (access(current_path, F_OK) == 0)
			return (current_path);
		free(current_path);
		current_path = NULL;
		i++;
	}
	return (NULL);
}

char	**create_path_env(char **env)
{
	int	i;

	i = 0;
	while (env[i] && ft_strncmp(env[i], "PATH=", 5))
		i++;
	if (!env[i] || ft_strncmp(env[i], "PATH=", 5) || !env[i][5])
		exit_error(NULL, "PATH enviroment variables not found.", 5);
	return (ft_split(&env[i][5], ':'));
}
