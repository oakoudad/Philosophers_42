/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakoudad <oakoudad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 04:16:25 by oakoudad          #+#    #+#             */
/*   Updated: 2022/06/17 04:51:23 by oakoudad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosopher.h"

size_t	ft_strlen(const char	*s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

long	ft_atoi(const char *str)
{
	int		sign;
	long	r;

	sign = 1;
	r = 0;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		r = r * 10 + *str - '0';
		if (r * sign >= 2147483648 || r * sign <= -2147483649)
			return (2147483649);
		str++;
	}
	if (r * sign < 0)
		return (2147483649);
	return (r * sign);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	valid_str(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '-' || str[0] == '+')
		i++;
	if (ft_strlen(str) == 1 && (str[0] == '-' || str[0] == '+'))
		return (0);
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

int	check_numbers(char **v)
{
	int	i;

	i = 1;
	while (v[i])
	{
		if (v[i][0] == 0)
			return (0);
		if (valid_str(v[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}
