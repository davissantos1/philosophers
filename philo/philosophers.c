/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasimoes <dasimoes@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 15:59:32 by dasimoes          #+#    #+#             */
/*   Updated: 2025/12/26 15:27:58 by dasimoes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	act_decide(t_philo *philo)
{
	t_control	*con;

	con = philo->control;
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
	t_philo		*philo;
	t_control	*con;
	int			status;

	status = 1;
	philo = (t_philo *) ptr;
	con = philo->control;
	if (!philo->life_time)
		philo->life_time = get_time(philo->control);
	if (philo->num % 2 == 0)
		ft_usleep(philo->control->time_to_eat / 2, philo->control);
	while (status)
	{
		pthread_mutex_lock(&philo->action_lock);
		if (get_time(con) - philo->life_time >= con->time_to_die)
			philo->action = DYING;
		pthread_mutex_unlock(&philo->action_lock);
		status = act_decide(philo);
	}
	return (NULL);
}

static void	run_checker(t_philo *cur, t_control *con)
{
	int	action_check;

	while (cur && !con->check)
	{
		action_check = 0;
		pthread_mutex_lock(&con->check_lock);
		pthread_mutex_lock(&cur->action_lock);
		if (cur->action == DYING || con->full_philo == con->number_philo)
			con->check = 1;
		pthread_mutex_unlock(&cur->action_lock);
		pthread_mutex_unlock(&con->check_lock);
		pthread_mutex_lock(&cur->action_lock);
		action_check = cur->action;
		pthread_mutex_unlock(&cur->action_lock);
		if (action_check == DYING)
			notify(cur, con, DYING);
		usleep(100);
		cur = cur->next;
		if (cur == con->head)
			break ;
	}
}

void	*init_checker(void *control)
{
	t_control			*con;
	t_philo				*cur;

	con = (t_control *) control;
	while (!con->check)
	{
		cur = con->head;
		run_checker(cur, con);
		usleep(2000);
	}
	return (NULL);
}

void	init_threads(t_philo *cur, t_control *con)
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
