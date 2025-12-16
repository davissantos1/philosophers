/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasimoes <dasimoes@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 15:59:32 by dasimoes          #+#    #+#             */
/*   Updated: 2025/12/15 15:11:12 by dasimoes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	act_decide(t_philo *philo)
{
	long	now;

	if (philo->action == TAKING_FORK)
		taking_fork(philo);
	else if (philo->action == SLEEPING)
		sleeping(philo);
	else if (philo->action == THINKING)
		thinking(philo);
	now = get_time(philo->control);
	if (now - philo->life_time >= philo->control->time_to_die)
	{
		philo->action = DYING;
		return (0);
	}
	return (1);
}

void	*act_philo(void *ptr)
{
	t_philo				*philo;

	philo = (t_philo *) ptr;
	if (!philo->life_time)
		philo->life_time = get_time(philo->control);
	while (act_decide(philo))
		;
	return (NULL);
}

void	*init_checker(void *control)
{
	pthread_mutex_t		mutex;
	t_control			*con;
	t_philo				*cur;

	con = (t_control *) control;
	cur = con->head;
	pthread_mutex_init(&mutex, NULL);
	while (1)
	{
		pthread_mutex_lock(&mutex);
		if (cur->action == DYING || con->eating_times == 0)
		{
			con->check = 1;
			if (cur->action == DYING)
				notify(cur, con, DYING);
			break ;
		}
		if (cur->next)
			cur = cur->next;
		pthread_mutex_unlock(&mutex);
		if (cur->next == con->head)
			usleep(5000);
	}
	pthread_mutex_destroy(&mutex);
	return (NULL);
}

void	init_simulation(t_control *con)
{
	t_philo		*cur;

	cur = con->head;
	if (pthread_create(&(con->checker), NULL, init_checker, (void *)con))
		con->error = "pthread_create error";
	con->start_time = get_time(con);
	while (cur && !con->check)
	{
		if (pthread_create(&(cur->id), NULL, act_philo, (void *)cur))
			con->error = "pthread_create error";
		cur = cur->next;
		if (cur == con->head)
			break ;
	}
	cur = con->head;
	while (cur && cur->next != con->head)
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
