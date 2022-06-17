#include "../philosopher.h"

t_philo	*ft_lstnew(int index)
{
	t_philo	*new;

	new = malloc(sizeof(t_philo));
	if (new == NULL)
		return (NULL);
	new->index = index;
	new->count =0;
	pthread_mutex_init(&new->fork, NULL);
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_philo	*ft_lstlast(t_philo *lst)
{
	t_philo	*current;

	current = lst;
	if (lst == NULL)
		return (NULL);
	while (current->next)
		current = current->next;
	return (current);
}

void	ft_lstadd_back(t_philo **lst, t_philo *new)
{
	t_philo *tmp;

	if (!new)
		return ;

	if (!(*lst))
		*lst = new;
	else
	{
		tmp = ft_lstlast(*lst);
		tmp->next = new;
		new->prev = tmp;
	}
}