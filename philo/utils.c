/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwehbe <miwehbe@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 18:32:31 by miwehbe           #+#    #+#             */
/*   Updated: 2025/08/20 18:32:31 by miwehbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *nptr)
{
	int	sign;
	int	result;

	sign = 1;
	result = 0;
	while ((*nptr >= 9 && *nptr <= 13) || *nptr == 32)
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			sign = -1;
		nptr++;
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		result = result * 10 + (*nptr - '0');
		nptr++;
	}
	return (sign * result);
}

int	is_number(const char *c)
{
  int i=0;
  while(c[i])
  {
    if ((c[i] < '0' || c[i] > '9'))
			return (0);
		i++;
  }
  return (1);
}

size_t get_time(void)
{
	struct timeval time;
	if(gettimeofday(&time,NULL)==-1)
	{
		write(2,"error getting time\n",19);
		return (0);
	}
	return (time.tv_sec *1000 + time.tv_usec/1000);
}
