/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasimoes <dasimoes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 16:53:57 by dasimoes          #+#    #+#             */
/*   Updated: 2025/12/04 03:36:37 by dasimoes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	eating(t_philo *philo)
{
	static int			count = 0;
	pthread_mutex_t		mutex;

	if (count == philo->control->number_philo)
	{
		philo->control->eating_times--;
		count = 0;
	}
	notify(philo, philo->control, EATING);
	usleep(philo->control->eating_times);
	if (gettimeofday(&(philo->life_time), NULL) == -1)
		philo->control->error = "gettimeofday error";
	pthread_mutex_init(&mutex, NULL);
	pthread_mutex_lock(&mutex);
	philo->prev->rfork++;
	philo->lfork--;
	pthread_mutex_unlock(&mutex);
	pthread_mutex_destroy(&mutex);
	philo->action = SLEEPING;
	count++;
}

void	taking_fork(t_philo *philo)
{
	pthread_mutex_t		mutex;

	pthread_mutex_init(&mutex, NULL);
	pthread_mutex_lock(&mutex);
	philo->rfork++;
	pthread_mutex_unlock(&mutex);
	notify(philo, philo->control, TAKING_FORK);
	pthread_mutex_lock(&mutex);
	philo->prev->rfork--;
	philo->lfork++;
	pthread_mutex_unlock(&mutex);
	pthread_mutex_destroy(&mutex);
	notify(philo, philo->control, TAKING_FORK);
	eating(philo);
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
