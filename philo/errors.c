/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasimoes <dasimoes@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 13:08:14 by dasimoes          #+#    #+#             */
/*   Updated: 2025/11/24 22:11:31 by dasimoes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	error(int type)
{
	if (type != NO_ERROR)
		ft_putstr_fd("Philosophers error: ", 2);
	if (type == ARG_TYPE_ERROR)
		ft_putstr_fd("character args are not supported", 2);
	else if (type == ARG_AMOUNT_ERROR)
		ft_putstr_fd("not enough arguments", 2);
	else if (type == ARG_BLANK)
		ft_putstr_fd("provide necessary arguments", 2);
	else if (type == MEMORY_ERROR)
		ft_putstr_fd("memory allocation error", 2);
	else if (type == EXECUTION_ERROR)
		ft_putstr_fd("an execution error occured", 2);
	ft_putstr_fd("\n", 2);
	return (type);
}
