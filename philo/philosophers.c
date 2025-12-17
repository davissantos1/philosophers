/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasimoes <dasimoes@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 15:59:32 by dasimoes          #+#    #+#             */
/*   Updated: 2025/12/17 18:29:50 by dasimoes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	act_decide(t_philo *philo)
{
	if (philo->action == TAKING_FORK)
		taking_fork(philo);
	else if (philo->action == SLEEPING)
		sleeping(philo);
	else if (philo->action == THINKING)
		thinking(philo);
	pthread_mutex_lock(&philo->control->status_lock);
	if (philo->control->check)
	{
		pthread_mutex_unlock(&philo->control->status_lock);
		return (0); 
	}
	pthread_mutex_unlock(&philo->control->status_lock);
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
	int					eat_count;
	t_control			*con;
	t_philo				*cur;

	con = (t_control *) control;
	cur = con->head;
	eat_count = 0;
	while (!con->check)
	{
		while (cur && !con->check)
		{
			pthread_mutex_lock(&con->status_lock);
			if (get_time(con) - cur->life_time >= con->time_to_die)
				cur->action = DYING;
			if (cur->action == DYING || eat_count == con->number_philo)
				con->check = 1;
			if (cur->meals == con->eating_times)
			{
				eat_count++;
				cur->meals++;
			}
			pthread_mutex_unlock(&con->status_lock);
			if (cur->action == DYING)
				notify(cur, con, DYING);
			cur = cur->next;
			if (cur == con->head)
				break ;
		}
		usleep(1000);
	}
	return (NULL);
}

static void init_threads(t_philo *cur, t_control *con)
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
	while (cur)
	{
		cur->life_time = get_time(con);
		cur = cur->next;
		if (cur == con->head)
			break ;
	}
	cur = con->head;
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
