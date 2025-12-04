/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   notify.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasimoes <dasimoes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 13:00:09 by dasimoes          #+#    #+#             */
/*   Updated: 2025/12/04 03:40:18 by dasimoes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	notify(t_philo *philo, t_control *control, t_action act)
{
	int				time;
	int				diff;
	struct timeval	curr;

	time = gettimeofday(&curr, NULL);
	if (!philo->last_action.tv_sec)
		philo->last_action = curr;
	diff = curr.tv_sec * 1000 - philo->last_action.tv_sec * 1000;
	printf("\n%i %i ", diff, philo->num);
	if (act == EATING)
		printf("is eating");
	else if (act == THINKING)
		printf("is thinking");
	else if (act == SLEEPING)
		printf("is sleeping");
	else if (act == TAKING_FORK)
		printf("has taken a fork");
	else if (act == DYING)
		printf("died");
	philo->action = act;
	philo->last_action = curr;
	if (time == -1)
		control->error = "gettimeofday error";
}
