/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakoudad <oakoudad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 04:16:02 by oakoudad          #+#    #+#             */
/*   Updated: 2022/06/17 09:52:22 by oakoudad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	init_info(t_info *info, char **av, int ac)
{
	info->nb_philo = ft_atoi(av[1]);
	info->to_die = ft_atoi(av[2]);
	info->to_eat = ft_atoi(av[3]);
	info->to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		info->limit = ft_atoi(av[5]);
	else
		info->limit = -1;
	info->is_die = 1;
	info->is_full = 0;
	info->open_time = get_c_time();
	info->is_out = 1;
	pthread_mutex_init(&info->print, NULL);
	pthread_mutex_init(&info->full, NULL);
}

void	init_philo(int nb_philo, t_philo **philo, t_info *info)
{
	int		i;
	t_philo	*new;
	t_philo	*tmp;

	i = 1;
	*philo = NULL;
	while (i <= nb_philo)
	{
		new = ft_lstnew(i);
		new->time = info;
		new->meal = get_c_time();
		ft_lstadd_back(philo, new);
		i++;
	}
	tmp = ft_lstlast(*philo);
	tmp->next = *philo;
	(*philo)->prev = tmp;
}

void	my_free(t_philo	**philo)
{
	t_philo	*head;
	t_philo	*tmp;

	usleep(75 * (*philo)->time->nb_philo);
	head = *philo;
	head->prev->next = NULL;
	while (head)
	{
		tmp = head->next;
		free(head);
		head = tmp;
	}
}

int	main(int ac, char **av)
{
	t_info	info;
	t_philo	*philo;
	t_philo	*head;

	if (ac == 5 || ac == 6)
		init_info(&info, av, ac);
	else
		return (printf("Bad Args"), 0);
	if (!check_numbers(av) || check_info(&info))
		return (printf("Bad Args"), 0);
	init_philo(info.nb_philo, &philo, &info);
	head = philo;
	while (head->next)
	{
		pthread_create(&head->th, NULL, &func, (void *)head);
		head = head->next;
		if (head->index == 1)
			break ;
		pthread_detach(head->th);
	}
	while (ft_die(&philo, info.to_die) && is_full(&philo))
		usleep(2000);
	my_free(&philo);
	return (0);
}
