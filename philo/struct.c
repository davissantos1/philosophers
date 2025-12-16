/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasimoes <dasimoes@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 13:55:11 by dasimoes          #+#    #+#             */
/*   Updated: 2025/12/15 15:09:19 by dasimoes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_philo	*create_philo(t_control *con, int number)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if(!philo)
		return (NULL);
	philo = memset(philo, 0, sizeof(t_philo));
	philo->num = number;
	if (number % 2 == 0)
		philo->action = SLEEPING;
	else
		philo->action = TAKING_FORK;
	philo->control = con;
	pthread_mutex_init(&philo->fork, NULL);
	return (philo);
}

t_control	*init_control(char **av)
{
	t_control	*control;

	control = malloc(sizeof(t_control));
	if (!control)
		return (NULL);
	control = memset(control, 0, sizeof(t_control));
	control->number_philo = ft_atoi(av[1]);
	control->time_to_die = ft_atoi(av[2]);
	control->time_to_eat = ft_atoi(av[3]);
	control->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		control->eating_times = ft_atoi(av[1]);
	else
		control->eating_times = -1;
	pthread_mutex_init(&control->print_lock, NULL);
	return (control);
}

t_philo	*init_philo(t_control *control)
{
	t_philo	*head;
	t_philo	*curr;
	t_philo	*temp;
	int		index;

	index = 1;
	head = create_philo(control, index);
	if (control->number_philo == 1)
		return (head);
	curr = create_philo(control, ++index);
	head->next = curr;
	curr->prev = head;
	while (++index <= control->number_philo)
	{
			temp = curr;
			curr = create_philo(control, index);
			curr->prev = temp;
			temp->next = curr;
	}
	curr->next = head;
	head->prev = curr;
	return (head);
}
