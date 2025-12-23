/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasimoes <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 15:58:07 by dasimoes          #+#    #+#             */
/*   Updated: 2025/12/23 18:48:30 by dasimoes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_simulation(t_control *con)
{
	t_philo		*cur;

	cur = con->head;
	con->start_time = get_time(con);
	init_threads(cur, con);
	while (cur)
	{
		if (pthread_join(cur->id, NULL))
			con->error = "pthread_join error";
		cur = cur->next;
		if (cur == con->head)
			break ;
	}
	if (pthread_join(con->checker, NULL))
		con->error = "pthread_join error";
}

int	main(int ac, char **av)
{
	t_control	*control;

	if (ac == 5 || ac == 6)
	{
		if (!check_args(av) || ft_atoi(av[1]) == 0)
			return (error(ARG_NUM_ERROR));
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
