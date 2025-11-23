/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasimoes <dasimoes@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 15:59:32 by dasimoes          #+#    #+#             */
/*   Updated: 2025/11/20 14:54:18 by dasimoes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*act_philo(void *control)
{
	t_control	*c;

	c = (t_control *) control;
	
}

void	init_simulation(t_control *control)
{
	t_philo	*cur;

	control->head = init_philo(control);
	cur = control->head;
	while (cur->next != control->head)
	{
		if (pthread_create(cur->id, NULL, act_philo, (void *)control))
			control->error = "pthread error";
		pthread_join(cur->id, NULL);
		cur = cur->next;
	}
	
	
}
