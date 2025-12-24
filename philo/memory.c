/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasimoes <dasimoes@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 16:46:02 by dasimoes          #+#    #+#             */
/*   Updated: 2025/12/23 22:34:54 by dasimoes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*free_all(t_control *control)
{
	t_philo	*curr;
	t_philo	*temp;
	int		i;

	i = 1;
	if (!control)
		return (NULL);
	curr = control->head;
	while (i <= control->number_philo)
	{
		temp = curr->next;
		pthread_mutex_destroy(&curr->fork);
		pthread_mutex_destroy(&curr->action_lock);
		free(curr);
		curr = temp;
		i++;
	}
	pthread_mutex_destroy(&control->print_lock);
	pthread_mutex_destroy(&control->check_lock);
	free(control);
	return (NULL);
}
