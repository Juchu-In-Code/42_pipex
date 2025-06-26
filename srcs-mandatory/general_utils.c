/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgalizio <jgalizio@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 11:39:39 by jgalizio          #+#    #+#             */
/*   Updated: 2024/11/05 16:48:52 by jgalizio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_strchr_index(char *str, int char_to_find)
{
	char	*pos_found;

	pos_found = ft_strchr(str, char_to_find);
	if (!pos_found)
		return (-1);
	return (pos_found - str);
}

void	ft_free_matrix(void **mtx)
{
	size_t	i;

	i = 0;
	while (mtx[i])
	{
		free(mtx[i]);
		i++;
	}
	free(mtx);
}
