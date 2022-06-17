#include "../philosopher.h"

int	check_info(t_info *info)
{
	long l;

	l = 2147483649;
	if (info->nb_philo == l || info->to_die == l ||
		info->to_eat == l || info->to_sleep == l ||
		info->limit == l)
		return (1);
	if (info->nb_philo <= 0 || info->to_die <= 0 ||
		info->to_eat <= 0 || info->to_sleep <= 0)
		return (1);
	return 0;
}