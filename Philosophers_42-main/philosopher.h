/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelmoham <eelmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 21:09:22 by eelmoham          #+#    #+#             */
/*   Updated: 2022/06/12 21:32:35 by eelmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef PHILOSOPHER_H
#define PHILOSOPHER_H

# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
#include <sys/time.h>

typedef struct s_info
{
	long	nb_philo;
	long	to_die;
	long	to_eat;
	long	to_sleep;
	long	limit;
	int		is_die;
	long	open_time;
	pthread_mutex_t print;
}	t_info;

typedef struct s_philo
{
	int index;
	pthread_t th;
	pthread_mutex_t fork;
	int				count;
	long			last_meal;
	struct s_info	time;
	struct s_philo *next;
	struct s_philo *prev;
}	t_philo;

long	ft_atoi(const char *str);
int		check_numbers(char **v);
int	check_info(t_info info, int ac);
t_philo	*ft_lstnew(int index);
t_philo	*ft_lstlast(t_philo *lst);
void	ft_lstadd_back(t_philo **lst, t_philo *new);
# endif