/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasimoes <dasimoes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 16:53:57 by dasimoes          #+#    #+#             */
/*   Updated: 2025/12/23 01:06:32 by dasimoes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->control->check_lock);
	if (philo->control->check)
	{
		pthread_mutex_unlock(&philo->control->check_lock);
		return ;
	}
	pthread_mutex_unlock(&philo->control->check_lock);
	philo->life_time = get_time(philo->control);
	philo->meals++;
	notify(philo, philo->control, EATING);
	ft_usleep(philo->control->time_to_eat, philo->control);
	pthread_mutex_lock(&philo->action_lock);
	philo->action = SLEEPING;
	pthread_mutex_unlock(&philo->action_lock);
}

void	taking_fork(t_philo *philo)
{
	if (philo->control->number_philo == 1)
	{
		pthread_mutex_lock(&philo->fork);
		notify(philo, philo->control, TAKING_FORK);
		usleep(philo->control->time_to_die);
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
	pthread_mutex_lock(&philo->action_lock);
	philo->action = THINKING;
	pthread_mutex_unlock(&philo->action_lock);
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
	if (t_think < 2)
		t_think = 2;
	notify(philo, philo->control, THINKING);
	ft_usleep(t_think, philo->control);
	pthread_mutex_lock(&philo->action_lock);
	philo->action = TAKING_FORK;
	pthread_mutex_unlock(&philo->action_lock);
}
