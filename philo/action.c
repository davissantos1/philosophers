/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasimoes <dasimoes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 16:53:57 by dasimoes          #+#    #+#             */
/*   Updated: 2025/12/16 00:51:35 by dasimoes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	eating(t_philo *philo)
{
	static int			count = 0;

	if (count == philo->control->number_philo)
	{
		philo->control->eating_times--;
		count = 0;
	}
	notify(philo, philo->control, EATING);
	usleep(philo->control->time_to_eat);
	philo->life_time = get_time(philo->control);
	philo->action = SLEEPING;
	count++;
}

void	taking_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork);
	notify(philo, philo->control, TAKING_FORK);
	pthread_mutex_lock(&philo->prev->fork);
	notify(philo, philo->control, TAKING_FORK);
	eating(philo);
	pthread_mutex_unlock(&philo->prev->fork);
	pthread_mutex_unlock(&philo->fork);
}


void	sleeping(t_philo *philo)
{
	notify(philo, philo->control, SLEEPING);
	usleep(philo->control->time_to_sleep);
	philo->action = THINKING;

}
void	thinking(t_philo *philo)
{
	notify(philo, philo->control, THINKING);
	usleep(2000);
	philo->action = TAKING_FORK;
}
