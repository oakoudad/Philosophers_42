#include "philosopher.h"

long  get_c_time()
{
	long current_time;
	struct timeval tme;

	gettimeofday(&tme, NULL);
	current_time = (tme.tv_sec * 1000) + tme.tv_usec /1000;
	return (current_time);
}

void	ft_printf(char *s, t_philo **philo);

int ft_die(t_philo **philo, long time_to_die)
{
	t_philo *tmp;

	tmp = *philo;
	while(tmp->time.is_die == 1 && tmp)
	{
		if (tmp->time.is_die == 1 && tmp->last_meal + time_to_die <= get_c_time())
		{
			tmp->time.is_die = 0;
			pthread_mutex_lock(&tmp->time.print);
			printf("%ldms\t%d is dead\n", get_c_time() - tmp->time.open_time, tmp->index);
			return 0;
		}
		tmp = tmp->next;
		if (tmp->index == 1)
			break ;
	}
	if (tmp->time.is_die == 0)
		return 0;
	return 1;
}

void	ft_printf(char *s, t_philo **philo)
{
	pthread_mutex_t p;
	long logtime;
	int index;

	if(ft_die(&(*philo), (*philo)->time.to_die))
	{
		logtime = get_c_time() - (*philo)->time.open_time;
		index = (*philo)->index;
		p = (*philo)->time.print;
		pthread_mutex_lock(&p);
		printf("%ldms\t%d %s\n", logtime, index, s);
		pthread_mutex_unlock(&p);
	}
}

void ft_usleep(t_philo *philo, long sleep_at)
{
	long time;

	if(philo->time.is_die == 1 && ft_die(&philo, philo->time.to_die))
	{
		time = get_c_time() + sleep_at;
		usleep(sleep_at * 1000 * 80 / 100);
		while (get_c_time() < time)
			ft_die(&philo, philo->time.to_die);
	}
}

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
	info->open_time = get_c_time();
	pthread_mutex_init(&info->print, NULL);
	pthread_mutex_init(&info->dead, NULL);
}

void	init_philo(int nb_philo, t_philo **philo, t_info info)
{
	int i;
	t_philo *new;
	t_philo *tmp;

	i = 1;
	*philo = NULL;
	while (i <= nb_philo)
	{
		new = ft_lstnew(i);
		new->time = info;
		new->last_meal = get_c_time();
		ft_lstadd_back(philo, new);
		i++;
	}
	tmp = ft_lstlast(*philo);
	tmp->next = *philo;
	(*philo)->prev = tmp;
}
void *func(void *p)
{
	t_philo *philo;

	philo = (t_philo *)p;
	if ((philo->index % 2) == 0)
			usleep(50);
	while (philo->time.is_die)
	{
		if (philo->time.limit != -1 && philo->count >= philo->time.limit)
			break;
		pthread_mutex_lock(&philo->fork);
		ft_printf("is taking a fork", &philo);
		pthread_mutex_lock(&philo->next->fork);
		ft_printf("is taking a fork", &philo);
		ft_printf("is eating", &philo);
		philo->count++;
		ft_usleep(philo, philo->time.to_eat);
		philo->last_meal = get_c_time();
		pthread_mutex_unlock(&philo->fork);
		pthread_mutex_unlock(&philo->next->fork);
		ft_printf("is sleeping", &philo);
		ft_usleep(philo, philo->time.to_sleep);
		ft_printf("is thinking", &philo);
	}
	return(NULL);
}
int ifall_eating(t_philo **philo)
{
	int i;
	t_philo *tmp;

	i = 0;
	tmp = *philo;
	while(tmp->next)
	{
		if (tmp->count >= tmp->time.limit)
			i++;
		tmp = tmp->next;
		if (tmp->index == 1)
			break ;
	}
	if (i == tmp->time.limit){
		printf("i = %d\n", i);
		return (0);
	}
	return (1);
}
int	main(int ac, char **av)
{
	t_info	info;
	t_philo *philo;
	t_philo *tmp;

	init_info(&info, av, ac);
	if (!check_numbers(av) || !(ac == 5 || ac == 6) || check_info(info, ac))
		return (printf("Bad Args"), 0);
	init_philo(info.nb_philo, &philo, info);
	tmp = philo;
	while (tmp->next)
	{
		pthread_create(&tmp->th, NULL, &func, (void *)tmp);
		tmp = tmp->next;
		if (tmp->index == 1)
			break ;
	}
	while(philo->time.is_die && ft_die(&philo, philo->time.to_die) && ifall_eating(&philo))
		usleep(100);
	return (0);
}
