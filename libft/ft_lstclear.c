/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgalizio <jgalizio@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 17:08:43 by jgalizio          #+#    #+#             */
/*   Updated: 2024/09/22 18:40:54 by jgalizio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	if (*lst && (*lst)->next)
		ft_lstclear(&(*lst)->next, del);
	ft_lstdelone((*lst), del);
	(*lst) = NULL;
}
