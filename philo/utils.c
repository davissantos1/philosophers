/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasimoes <dasimoes@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 13:30:37 by dasimoes          #+#    #+#             */
/*   Updated: 2025/12/09 18:07:53 by dasimoes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_strlen(char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

void	ft_putstr_fd(char *str, int fd)
{
	write(fd, str, ft_strlen(str));
}

long	get_time(t_control *control)
{
	struct timeval time;

	if (gettimeofday(&time, NULL) == -1)
		control->error = "gettimeofday error";
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	ft_atoi(char *str)
{
	long	result;
	int		i;

	i = -1;
	result = 0;
	while (str[++i])
	{
		if (!ft_isdigit(str[i]))
			return (-1);
		result = result * 10 + (str[i] - '0');
	}
	if (result > MAX_INT)
		return (-1);
	return ((int)result);
}
