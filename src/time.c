/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfofern <alfofern@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 19:44:22 by alfofern          #+#    #+#             */
/*   Updated: 2023/08/16 20:22:52 by alfofern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	timer(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000));
}

int	timer_dif(t_table *table)
{
	return (timer() - table->tm_start);
}

void	to_sleep(t_table *table, int time)
{
	int	sleep_init;

	sleep_init = timer_dif(table);
	pthread_mutex_lock(&table->deadmutex);
	while (timer_dif(table) - sleep_init < time && table->end == 0)
	{
		pthread_mutex_unlock(&table->deadmutex);
		usleep (5);
		pthread_mutex_lock(&table->deadmutex);
	}
	pthread_mutex_unlock(&table->deadmutex);
}
