/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasimoes <dasimoes@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 15:59:32 by dasimoes          #+#    #+#             */
/*   Updated: 2025/11/25 13:14:01 by dasimoes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*act_philo(void *ptr)
{
	struct timeval		now;
	t_philo				*philo;
	int					time;

	philo = (t_philo *) ptr;
	if (!philo->lifetime.tv_sec)
	{
		if (gettimeofday(&(philo->lifetime), NULL) == -1)
			philo->control->error = "gettimeofday error";
	}
	if (philo->action == TAKING_FORK)
		taking_fork(philo);
	else if (philo->action == SLEEPING)
		sleeping(philo);
	else if (philo->action == THINKING)
		thinking(philo);
	if (gettimeofday(&now, NULL) == -1)
		philo->control->error = "gettimeofday error";
	time = (now.tv_sec / 1000) - (philo->lifetime.tv_sec / 1000); 
	if (time >= philo->control->time_to_die)
		philo->action = DYING;
	return (NULL);
}

void	*init_checker(void *control)
{
	t_control	*con;
	t_philo		*cur;

	con = (t_control *) control;
	cur = con->head;
	while (1)
	{
		if (cur->action == DYING || con->eating_times == 0)
		{
			con->check = 1;
			if (cur->action == DYING)
				notify(cur, con, DYING);
			break ;
		}
		if (cur->next == con->head)
			usleep(5000);
		cur = cur->next;
	}
	return (NULL);
}

void	init_simulation(t_control *con)
{
	t_philo		*cur;

	cur = con->head;
	if (pthread_create(&(con->checker), NULL, init_checker, (void *)con))
		con->error = "pthread_create error";
	while (!con->check)
	{
		while (cur->next != con->head && !con->check)
		{
			if (pthread_create(&(cur->id), NULL, act_philo, (void *)cur))
				con->error = "pthread_create error";
			cur = cur->next;
		}
		cur = con->head;
		while (cur->next != con->head && !con->check)
		{
			if (pthread_join(cur->id, NULL))
				con->error = "pthread_join error";
			cur = cur->next;
		}
	}
	if (pthread_join(con->checker, NULL))
		con->error = "pthread_join error";
}
