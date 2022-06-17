/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakoudad <oakoudad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 04:16:15 by oakoudad          #+#    #+#             */
/*   Updated: 2022/06/17 09:43:53 by oakoudad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	is_full(t_philo **philo)
{
	t_philo	*tmp;
	long	i;

	tmp = *philo;
	i = 0;
	if (tmp->time->limit != -1 && tmp->count >= tmp->time->limit)
	{
		while (tmp->next)
		{
			if (tmp->count >= tmp->time->limit)
				i++;
			tmp = tmp->next;
			if (tmp->index == 1)
				break ;
		}
		if (i == tmp->time->nb_philo)
		{
			tmp->time->is_out = 0;
			return (0);
		}
	}
	return (1);
}

void	print_dead(t_philo	**philo)
{
	t_philo	*tmp;

	tmp = *philo;
	tmp->time->is_die = 0;
	pthread_mutex_lock(&tmp->time->print);
	if (tmp->time->is_out)
	{
		tmp->time->is_out = 0;
		printf("%ldms\t", get_c_time() - tmp->time->open_time);
		printf("%d is dead\n", tmp->index);
	}
}

int	ft_die(t_philo **philo, long to_die)
{
	t_philo	*tmp;

	tmp = *philo;
	while (tmp->time->is_die == 1 && tmp)
	{
		if (tmp->time->limit != -1 && tmp->count >= tmp->time->limit)
		{
			tmp = tmp->next;
			if (tmp->index == 1)
				break ;
			continue ;
		}
		if (tmp->time->is_die == 1 && tmp->meal + to_die <= get_c_time())
		{
			print_dead(&tmp);
			return (0);
		}
		tmp = tmp->next;
		if (tmp->index == 1)
			break ;
	}
	if (tmp->time->is_die == 0)
		return (0);
	return (1);
}

int	check(t_philo	*philo)
{
	if (philo->count >= philo->time->limit)
	{
		pthread_mutex_lock(&philo->time->full);
		philo->time->is_full++;
		pthread_mutex_unlock(&philo->time->full);
	}
	if (philo->time->limit != -1 && philo->count >= philo->time->limit)
		return (1);
	return (0);
}

void	*func(void *p)
{
	t_philo	*philo;

	philo = (t_philo *)p;
	if ((philo->index % 2) == 0)
		usleep(50);
	while (philo->time->is_die)
	{
		if (check(philo))
			break ;
		pthread_mutex_lock(&philo->fork);
		ft_printf("is taking a fork", &philo);
		pthread_mutex_lock(&philo->next->fork);
		ft_printf("is taking a fork", &philo);
		ft_printf("is eating", &philo);
		philo->meal = get_c_time();
		ft_usleep(philo, philo->time->to_eat);
		pthread_mutex_unlock(&philo->fork);
		pthread_mutex_unlock(&philo->next->fork);
		ft_printf("is sleeping", &philo);
		ft_usleep(philo, philo->time->to_sleep);
		ft_printf("is thinking", &philo);
		philo->count++;
	}
	return (NULL);
}
