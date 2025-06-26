/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgalizio <jgalizio@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 11:14:33 by jgalizio          #+#    #+#             */
/*   Updated: 2024/11/09 15:31:24 by jgalizio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static ssize_t	heredoc_open(void)
{
	ssize_t	heredoc_file;

	heredoc_file = open(".heredoc", O_WRONLY | O_TRUNC | O_CREAT, 0664);
	if (access(".heredoc", F_OK | W_OK) < 0)
	{
		call_error ("pipex", "here_doc cannot be created or written to.");
		return (-1);
	}
	return (heredoc_file);
}

static void	heredoc_manager(char *delim)
{
	char	*line;
	int		delim_len;
	ssize_t	hdoc_fd;

	delim_len = ft_strlen(delim);
	hdoc_fd = heredoc_open();
	if (hdoc_fd != -1)
	{
		while (1)
		{
			write(1, "pipe heredoc> ", 14);
			line = get_next_line(0);
			if (!line)
				return ;
			if (!ft_strncmp(line, delim, delim_len) && line[delim_len] == '\n')
			{
				free(line);
				break ;
			}
			write(hdoc_fd, line, ft_strlen(line));
			free(line);
		}
		close(hdoc_fd);
	}
}

static ssize_t	open_input_file(char *av, int heredoc)
{
	if (heredoc && access(".heredoc", F_OK | R_OK) != -1)
		return (open(".heredoc", O_RDONLY));
	if (access(av, F_OK | R_OK) == 0)
		return (open(av, O_RDONLY));
	call_error ("Invalid input file", "file not found or cannot be read from.");
	return (-1);
}

static ssize_t	open_output_file(char *av, int heredoc)
{
	ssize_t	file_output;

	if (heredoc)
		file_output = open(av, O_WRONLY | O_APPEND | O_CREAT, 0664);
	else
		file_output = open(av, O_WRONLY | O_TRUNC | O_CREAT, 0664);
	if (access(av, F_OK | W_OK) < 0)
	{
		call_error ("Invalid output file", "cannot be written to.");
		return (-1);
	}
	return (file_output);
}

void	open_files(t_pipex *pipex, int ac, char **av)
{
	if (pipex->heredoc)
		heredoc_manager(av[2]);
	pipex->file_in = open_input_file(av[1], pipex->heredoc);
	pipex->file_out = open_output_file(av[ac - 1], pipex->heredoc);
	if (pipex->file_in < 0 || pipex->file_out < 0)
	{
		if (pipex->file_in >= 0)
			close(pipex->file_in);
		if (pipex->file_out >= 0)
			close(pipex->file_out);
		if (pipex->heredoc)
			unlink(".heredoc");
		exit(1);
	}
}
