/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasimoes <dasimoes@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 15:59:32 by dasimoes          #+#    #+#             */
/*   Updated: 2025/12/04 03:52:17 by dasimoes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	act_decide(t_philo *philo)
{
	struct timeval		now;
	int					time;

	if (philo->action == TAKING_FORK)
		taking_fork(philo);
	else if (philo->action == SLEEPING)
		sleeping(philo);
	else if (philo->action == THINKING)
		thinking(philo);
	if (gettimeofday(&now, NULL) == -1)
		philo->control->error = "gettimeofday error";
	time = (now.tv_sec / 1000) - (philo->life_time.tv_sec / 1000); 
	if (time >= philo->control->time_to_die)
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
	if (!philo->life_time.tv_sec)
	{
		if (gettimeofday(&(philo->life_time), NULL) == -1)
			philo->control->error = "gettimeofday error";
	}
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
	while (cur->next != con->head && !con->check)
	{
		if (pthread_create(&(cur->id), NULL, act_philo, (void *)cur))
			con->error = "pthread_create error";
		cur = cur->next;
	}
	cur = con->head;
	while (cur->next != con->head)
	{
		if (pthread_join(cur->id, NULL))
			con->error = "pthread_join error";
		cur = cur->next;
	}
	if (pthread_join(con->checker, NULL))
		con->error = "pthread_join error";
}
