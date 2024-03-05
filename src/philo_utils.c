/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfofern <alfofern@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 19:41:45 by alfofern          #+#    #+#             */
/*   Updated: 2023/08/16 20:22:25 by alfofern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	ft_putstr_fd(char *s, int fd)
{
	while (*s)
		write (fd, s++, 1);
}

int	ft_error_fd(char *s, int rtn)
{
	ft_putstr_fd(s, 2);
	return (rtn);
}

void	free_struct(t_table	*table)
{
	int	i;

	i = -1;
	while (++i < table->n_phils)
	{
		pthread_mutex_destroy(&table->forks[i]);
		pthread_mutex_destroy(&table->philo[i].eatmutex);
	}
	free(table->philo);
	free(table->forks);
	pthread_mutex_destroy(&table->mutex);
	pthread_mutex_destroy(&table->deadmutex);
	pthread_mutex_destroy(&table->speakmutex);
}

int	ft_long_atoi(const char *str)
{	
	long	i;
	long	num;
	long	sign;

	i = 0;
	num = 0;
	sign = 1;
	while ((str[i] == ' ') || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -sign;
		i++;
	}
	while ((str[i] >= '0' && str[i] <= '9'))
	{
		num = (str[i] - '0' + num * 10);
		i++;
	}
	if ((num * sign) > 2147483647 || num * sign < -2147483648)
		ft_error_fd("|ö| one of the numbers is bigger than 2147483647\n", -2);
	return ((int)(num * sign));
}
