/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgalizio <jgalizio@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 11:39:39 by jgalizio          #+#    #+#             */
/*   Updated: 2024/11/05 21:08:10 by jgalizio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exit_error(char *err, char *msg, int exit_code)
{
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
