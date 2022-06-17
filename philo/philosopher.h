/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakoudad <oakoudad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 04:47:51 by oakoudad          #+#    #+#             */
/*   Updated: 2022/06/17 08:56:06 by oakoudad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_info
{
	long			nb_philo;
	long			to_die;
	long			to_eat;
	long			to_sleep;
	long			limit;
	int				is_die;
	int				is_full;
	long			open_time;
	int				is_out;
	pthread_mutex_t	print;
	pthread_mutex_t	full;
}	t_info;

typedef struct s_philo
{
	int				index;
	pthread_t		th;
	pthread_mutex_t	fork;
	long			count;
	long			meal;
	struct s_info	*time;
	struct s_philo	*next;
	struct s_philo	*prev;
}	t_philo;

long	ft_atoi(const char *str);
int		check_numbers(char **v);
int		check_info(t_info *info);
t_philo	*ft_lstnew(int index);
t_philo	*ft_lstlast(t_philo *lst);
void	ft_lstadd_back(t_philo **lst, t_philo *new);
void	ft_printf(char *s, t_philo **philo);
void	ft_usleep(t_philo *philo, long sleep_at);
int		is_full(t_philo **philo);
long	get_c_time(void);
int		ft_die(t_philo **philo, long time_to_die);
void	*func(void *p);
#endif