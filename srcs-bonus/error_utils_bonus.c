/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgalizio <jgalizio@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 20:34:39 by jgalizio          #+#    #+#             */
/*   Updated: 2024/11/07 17:35:27 by jgalizio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	exit_error(char *err, char *msg, int exit_code)
{
	if (!*err)
		err = "<Empty field>";
	if (!msg)
		perror(err);
	else if (!err && !msg)
		perror("[!]\t Error: ");
	else if (!err)
		ft_fprintf(2, "[!]\t Error: %s\n", msg);
	else
		ft_fprintf(2, "[!]\t%s: %s\n", err, msg);
	exit(exit_code);
}

void	call_error(char *err, char *msg)
{
	if (!msg)
		perror(err);
	else if (!err && !msg)
		perror("[!]\t Error: ");
	else if (!err)
		ft_fprintf(2, "[!]\t Error: %s\n", msg);
	else
		ft_fprintf(2, "[!]\t%s: %s\n", err, msg);
}
