/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   notify.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasimoes <dasimoes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 13:00:09 by dasimoes          #+#    #+#             */
/*   Updated: 2025/12/17 13:48:38 by dasimoes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	print_message(int num, int time, t_action act)
{
	printf("\n%i %i ", time, num);
	if (act == EATING)
		printf("is eating");
	else if (act == THINKING)
		printf("is thinking");
	else if (act == SLEEPING)
		printf("is sleeping");
	else if (act == TAKING_FORK)
		printf("has taken a fork");
	else if (act == DYING)
		printf("died\n");
}

void	notify(t_philo *philo, t_control *control, t_action act)
{
	long			time;

	pthread_mutex_lock(&control->print_lock);
	philo->last_action = get_time(control);
	time = philo->last_action - control->start_time;
	if (!control->check)
		print_message(philo->num, time, act);
	pthread_mutex_unlock(&control->print_lock);
}
