/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasimoes <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 15:58:07 by dasimoes          #+#    #+#             */
/*   Updated: 2025/11/17 16:52:50 by dasimoes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_control	*control;
	
	if (ac == 3 || ac == 4)
	{
		if (!check_args(av))
			return (error(ARG_TYPE_ERROR));
		control = init_control(av);
		if (!control)
			return (error(MEMORY_ERROR));
		init_simulation(control);
	}
	else if (ac == 1)
		return (error(ARG_BLANK));
	else
		return (error(ARG_AMOUNT_ERROR));
	free_all(control);
	return (0);
}
