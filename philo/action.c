/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasimoes <dasimoes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 16:53:57 by dasimoes          #+#    #+#             */
/*   Updated: 2025/12/16 15:57:29 by dasimoes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->control->status_lock);
	notify(philo, philo->control, EATING);
	usleep(philo->control->time_to_eat);
	philo->life_time = get_time(philo->control);
	philo->action = SLEEPING;
	philo->meals++;
	pthread_mutex_unlock(&philo->control->status_lock);
}

void	taking_fork(t_philo *philo)
{
	if (philo->control->number_philo == 1)
	{
		pthread_mutex_lock(&philo->fork);
		notify(philo, philo->control, TAKING_FORK);
		usleep(philo->control->time_to_die * 1000);
		pthread_mutex_unlock(&philo->fork);
		return ;
	}
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
	usleep(200);
	philo->action = TAKING_FORK;
}
