/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasimoes <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 15:50:49 by dasimoes          #+#    #+#             */
/*   Updated: 2025/12/23 18:48:26 by dasimoes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

// External includes
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

// Macros
# define MAX_INT 2147483647

// Enums
typedef enum e_error
{
	NO_ERROR,
	ARG_NUM_ERROR,
	ARG_AMOUNT_ERROR,
	ARG_BLANK,
	MEMORY_ERROR,
	EXECUTION_ERROR
}	t_error;

typedef enum e_action
{
	TAKING_FORK,
	EATING,
	SLEEPING,
	THINKING,
	DYING
}	t_action;

// Structs
typedef struct s_philo
{
	pthread_t			id;
	t_action			action;
	int					num;
	int					meals;
	int					full;
	long				life_time;
	long				last_action;
	struct s_control	*control;
	struct s_philo		*next;
	struct s_philo		*prev;
	pthread_mutex_t		fork;
	pthread_mutex_t		action_lock;
}	t_philo;

typedef struct s_control
{
	pthread_t		checker;
	t_philo			*head;
	char			*error;
	int				check;
	long			start_time;
	int				full_philo;
	int				number_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				eating_times;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	check_lock;
}	t_control;

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
void		init_simulation(t_control *con);
void		notify(t_philo *philo, t_control *control, t_action act);
void		thinking(t_philo *philo);
void		sleeping(t_philo *philo);
void		taking_fork(t_philo *philo);
long		get_time(t_control *control);
void		ft_usleep(long time_in_ms, t_control *control);
void		init_threads(t_philo *cur, t_control *con);

#endif
