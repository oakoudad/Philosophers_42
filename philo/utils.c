/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakoudad <oakoudad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 04:16:20 by oakoudad          #+#    #+#             */
/*   Updated: 2022/06/17 04:18:13 by oakoudad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	ft_printf(char *s, t_philo **philo)
{
	pthread_mutex_t	p;
	long			logtime;
	int				index;

	if (ft_die(&(*philo), (*philo)->time->to_die))
	{
		logtime = get_c_time() - (*philo)->time->open_time;
		index = (*philo)->index;
		p = (*philo)->time->print;
		pthread_mutex_lock(&p);
		printf("%ldms\t%d %s\n", logtime, index, s);
		pthread_mutex_unlock(&p);
	}
}

void	ft_usleep(t_philo *philo, long sleep_at)
{
	long	time;

	if (philo->time->is_die == 1 && ft_die(&philo, philo->time->to_die))
	{
		time = get_c_time() + sleep_at;
		usleep(sleep_at * 1000 * 0.9);
		while (get_c_time() < time)
			ft_die(&philo, philo->time->to_die);
	}
}

long	get_c_time(void)
{
	long			current_time;
	struct timeval	tme;

	gettimeofday(&tme, NULL);
	current_time = (tme.tv_sec * 1000) + tme.tv_usec / 1000;
	return (current_time);
}
