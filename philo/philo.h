/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasimoes <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 15:50:49 by dasimoes          #+#    #+#             */
/*   Updated: 2025/11/20 14:36:25 by dasimoes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

// External includes
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

// Enums
typedef enum e_error
{
	NO_ERROR,
	ARG_TYPE_ERROR,
	ARG_AMOUNT_ERROR,
	ARG_BLANK,
	MEMORY_ERROR,
	RACE_ERROR,
	OTHER_ERROR
}	t_error;

typedef enum e_action
{
	TOOK_FORK,
	EATING,
	SLEEPING,
	THINKING,
	DIED
}	t_action;

// Structs
typedef struct s_control
{
	t_philo	*head;
	char	*error;
	int		number_philo;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		eating_times;
}	t_control;

typedef struct s_philo
{
	t_action		action;
	pthread_t		*id;
	int				num;
	int				fork;
	int				meals;
	struct s_philo	*next;
	struct s_philo	*prev;
}	t_philo;

//Prototypes
t_control	*init_control(char **av);
t_philo		*init_philo(t_control *control);
int			check_args(char **av);
int			ft_isdigit(char c);
int			ft_atoi(char *str);
void		ft_putstr_fd(char *str, int fd);
int			ft_strlen(char *str);
int			error(int type);
void		*free_all(t_control *control);
void		notify(t_philo *philo, t_control *control, t_action act);
void		init_simulation(t_control *control);
void		notify(t_philo *philo, t_control *control, t_action act);

#endif
