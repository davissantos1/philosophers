/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasimoes <dasimoes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 13:05:52 by dasimoes          #+#    #+#             */
/*   Updated: 2025/12/22 13:32:34 by dasimoes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_usleep(long time_in_ms, t_control *control)
{
	long	start_time;

	start_time = get_time(control);
	while ((get_time(control) - start_time) < time_in_ms)
	{
		pthread_mutex_lock(&control->status_lock);
		if (control->check)
		{
			pthread_mutex_unlock(&control->status_lock);
			return ; 
		}
		pthread_mutex_unlock(&control->status_lock);
		usleep(2000); 	
	}
}

long	get_time(t_control *control)
{
	struct timeval time;

	if (gettimeofday(&time, NULL) == -1)
		control->error = "gettimeofday error";
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}
