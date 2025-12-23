/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasimoes <dasimoes@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 15:59:32 by dasimoes          #+#    #+#             */
/*   Updated: 2025/12/22 21:59:35 by dasimoes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	act_decide(t_philo *philo)
{
	t_control	*con;

	con = philo->control;
	if (get_time(con) - philo->life_time >= con->time_to_die)
		philo->action = DYING;
	if (philo->action == TAKING_FORK)
		taking_fork(philo);
	else if (philo->action == SLEEPING)
		sleeping(philo);
	else if (philo->action == THINKING)
		thinking(philo);
	if (!philo->full && philo->meals == philo->control->eating_times)
	{
		philo->full = 1;
		philo->control->full_philo++;
	}
	pthread_mutex_lock(&philo->control->check_lock);
	if (philo->control->check)
	{
		pthread_mutex_unlock(&philo->control->check_lock);
		return (0);
	}
	pthread_mutex_unlock(&philo->control->check_lock);
	return (1);
}

void	*act_philo(void *ptr)
{
	t_philo				*philo;

	philo = (t_philo *) ptr;
	if (!philo->life_time)
		philo->life_time = get_time(philo->control);
	if (philo->num % 2 == 0)
		ft_usleep(philo->control->time_to_eat / 2, philo->control);
	while (act_decide(philo))
		;
	return (NULL);
}

void	*init_checker(void *control)
{
	t_control			*con;
	t_philo				*cur;

	con = (t_control *) control;
	cur = con->head;
	while (!con->check)
	{
		while (cur && !con->check)
		{
			pthread_mutex_lock(&con->check_lock);
			pthread_mutex_lock(&cur->action_lock);
			if (cur->action == DYING || con->full_philo == con->number_philo)
				con->check = 1;
			if (cur->action == DYING)
				notify(cur, con, DYING);
			pthread_mutex_unlock(&cur->action_lock);
			pthread_mutex_unlock(&con->check_lock);
			usleep(100);
			cur = cur->next;
			if (cur == con->head)
				break ;
		}
		usleep(1000);
	}
	return (NULL);
}

static void	init_threads(t_philo *cur, t_control *con)
{
	while (cur && !con->check)
	{
		if (pthread_create(&(cur->id), NULL, act_philo, (void *)cur))
			con->error = "pthread_create error";
		cur = cur->next;
		if (cur == con->head)
			break ;
	}
	if (pthread_create(&(con->checker), NULL, init_checker, (void *)con))
		con->error = "pthread_create error";
}

void	init_simulation(t_control *con)
{
	t_philo		*cur;

	cur = con->head;
	con->start_time = get_time(con);
	init_threads(cur, con);
	while (cur)
	{
		if (pthread_join(cur->id, NULL))
			con->error = "pthread_join error";
		cur = cur->next;
		if (cur == con->head)
			break ;
	}
	if (pthread_join(con->checker, NULL))
		con->error = "pthread_join error";
}
