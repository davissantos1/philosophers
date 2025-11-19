/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasimoes <dasimoes@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 16:46:02 by dasimoes          #+#    #+#             */
/*   Updated: 2025/11/17 16:51:50 by dasimoes         ###   ########.fr       */
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
		free(curr);
		curr = temp;
	}
	free(curr);
	free(control);
	return (NULL);
}
	
