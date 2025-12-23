/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasimoes <dasimoes@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 16:46:02 by dasimoes          #+#    #+#             */
/*   Updated: 2025/12/22 21:58:55 by dasimoes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*free_all(t_control *control)
{
	t_philo	*curr;
	t_philo	*temp;

	curr = control->head;
	while (curr != control->head->prev)
	{
		temp = curr->next;
		pthread_mutex_destroy(&curr->fork);
		pthread_mutex_destroy(&curr->action_lock);
		free(curr);
		curr = temp;
	}
	pthread_mutex_destroy(&control->print_lock);
	pthread_mutex_destroy(&control->check_lock);
	free(curr);
	free(control);
	return (NULL);
}
