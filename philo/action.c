/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasimoes <dasimoes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 16:53:57 by dasimoes          #+#    #+#             */
/*   Updated: 2025/12/22 13:11:41 by dasimoes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->control->status_lock);
	if (philo->control->check)
	{
		pthread_mutex_unlock(&philo->control->status_lock);
		return ;
	}
	philo->life_time = get_time(philo->control);
	philo->meals++;
	pthread_mutex_unlock(&philo->control->status_lock);
	notify(philo, philo->control, EATING);
	ft_usleep(philo->control->time_to_eat, philo->control);
	philo->action = SLEEPING;
}

void	taking_fork(t_philo *philo)
{
	if (philo->control->number_philo == 1)
	{
		pthread_mutex_lock(&philo->fork);
		notify(philo, philo->control, TAKING_FORK);
		ft_usleep(philo->control->time_to_die, philo->control);
		pthread_mutex_unlock(&philo->fork);
		return ;
	}
	if (philo->num % 2 == 0)
	{
		pthread_mutex_lock(&philo->fork);
		notify(philo, philo->control, TAKING_FORK);
		pthread_mutex_lock(&philo->prev->fork);
	}
	else
	{
		pthread_mutex_lock(&philo->prev->fork);
		notify(philo, philo->control, TAKING_FORK);
		pthread_mutex_lock(&philo->fork);
	}
	notify(philo, philo->control, TAKING_FORK);
	eating(philo);
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(&philo->prev->fork);
}

void	sleeping(t_philo *philo)
{
	notify(philo, philo->control, SLEEPING);
	ft_usleep(philo->control->time_to_sleep, philo->control);
	philo->action = THINKING;

}

void	thinking(t_philo *philo)
{
	long	t_eat;
	long	t_sleep;
	long	t_think;

	t_eat = philo->control->time_to_eat;
	t_sleep = philo->control->time_to_sleep;
	t_think = 0;
	if (t_eat > t_sleep)
		t_think = (t_eat - t_sleep);
	if (t_think < 5)
		t_think = 5;
	notify(philo, philo->control, THINKING);
	ft_usleep(t_think, philo->control);
	philo->action = TAKING_FORK;
}
