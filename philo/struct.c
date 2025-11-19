/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasimoes <dasimoes@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 13:55:11 by dasimoes          #+#    #+#             */
/*   Updated: 2025/11/17 16:44:48 by dasimoes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_philo	*create_philo(t_control	*control, int number)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if(!philo)
		return (NULL);
	philo = memset(philo, 0, sizeof(t_philo));
	philo->num = number;
	philo->fork = 1;
	if (pthread_create(philo->id, NULL, NULL, NULL))
		control->error = "pthread error";
	if (number % 2 == 0)
		philo->status = THINKING;
	else
		philo->status = EATING;
	return (philo);
}

t_control	*init_control(char **av)
{
	t_control	*control;

	control = malloc(sizeof(t_control));
	if (!control)
		return (NULL);
	control = memset(control, 0, sizeof(t_control));
	control->number_philo = ft_itoa(av[1]);
	control->time_to_die = ft_itoa(av[2]);
	control->time_to_eat = ft_itoa(av[3]);
	control->time_to_sleep = ft_itoa(av[4]);
	if (av[5])
		control->eat_quantity = ft_itoa(av[1]);
	else
		control->eat_quantity = EAT_QUANTITY;
	return (control);
}

t_philo	*init_philo(t_control *control)
{
	t_philo	*head;
	t_philo	*curr;
	t_philo	*temp;
	int		index;

	index = 0;
	while (++index <= control->number_philo)
	{
		if (index == 1)
		{
			head = create_philo(control, index);
			temp = create_philo(control, ++index);
			head->next = temp;
			temp->prev = head;
		}
		else
		{
			curr = create_philo(control, index);
			curr->prev = temp;
			temp->next = curr;
			temp = curr;
		}
	}
}
