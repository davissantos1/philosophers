/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   notify.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasimoes <dasimoes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 13:00:09 by dasimoes          #+#    #+#             */
/*   Updated: 2025/11/24 21:49:15 by dasimoes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	notify(t_philo *philo, t_control *control, t_action act)
{
	struct timeval *time;

	time = NULL;
	if (gettimeofday(time, NULL) == -1)
		control->error = "gettimeofday error";
	printf("\n%li %i ", time->tv_sec * 1000, philo->num);
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
}
