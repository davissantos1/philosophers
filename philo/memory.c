/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasimoes <dasimoes@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 16:46:02 by dasimoes          #+#    #+#             */
/*   Updated: 2025/12/23 21:46:29 by dasimoes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*free_all(t_control *control)
{
	t_philo	*curr;
	t_philo	*temp;

	curr = control->head->next;
	temp = control->head->prev;
	pthread_mutex_destroy(&control->head->fork);
	pthread_mutex_destroy(&control->head->action_lock);
	free(control->head);
	while (curr)
	{
		pthread_mutex_destroy(&curr->fork);
		pthread_mutex_destroy(&curr->action_lock);
		free(curr);
		if (curr == temp)
			break ;
		curr = curr->next;
	}
	pthread_mutex_destroy(&control->print_lock);
	pthread_mutex_destroy(&control->check_lock);
	free(control);
	return (NULL);
}
