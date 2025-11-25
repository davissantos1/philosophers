/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasimoes <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 15:58:07 by dasimoes          #+#    #+#             */
/*   Updated: 2025/11/24 22:14:10 by dasimoes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_control	*control;
	
	if (ac == 5 || ac == 6)
	{
		if (!check_args(av))
			return (error(ARG_TYPE_ERROR));
		control = init_control(av);
		if (!control)
			return (error(MEMORY_ERROR));
		control->head = init_philo(control);
		if (!control->head)
			return (error(MEMORY_ERROR));
		init_simulation(control);
		if (control->error)
		{
			printf("philosophers: %s\n", control->error);
			return (EXECUTION_ERROR);
		}
	}
	else if (ac == 1)
		return (error(ARG_BLANK));
	else
		return (error(ARG_AMOUNT_ERROR));
	free_all(control);
	return (0);
}
