/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   notify.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasimoes <dasimoes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 13:00:09 by dasimoes          #+#    #+#             */
/*   Updated: 2025/11/19 15:33:00 by dasimoes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	notify(t_philo *philo, t_control *control, t_action act)
{
	struct timeval *time;

	gettimeofday(time, NULL);
	printf("\n%i %i ", time->tv_sec * 1000, philo->num);
	if (act == EATING)
		printf("is eating");
	else if (act == THINKING)
		printf("is thinking");
	else if (act == SLEEPING)
		printf("is sleeping");
	else if (act == TOOK_FORK)
		printf("has taken a fork");
	else if (act == DIED)
		printf("died");
	philo->action = act;
}
