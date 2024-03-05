/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfofern <alfofern@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 19:32:27 by alfofern          #+#    #+#             */
/*   Updated: 2023/08/16 20:30:31 by alfofern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static int	is_dead(t_table *table, int i)
{
	pthread_mutex_lock(&table->philo[i].eatmutex);
	if (timer_dif(table) - table->philo[i].last_meal > table->tm_dead)
	{
		table->end = 1;
		pthread_mutex_unlock(&table->deadmutex);
		printf("%d %d is dead\n", timer_dif(table), (i + 1));
		pthread_mutex_unlock(&table->philo[i].eatmutex);
		return (1);
	}
	else
	{
		pthread_mutex_unlock(&table->philo[i].eatmutex);
		pthread_mutex_unlock(&table->deadmutex);
	}
	return (0);
}

static int	need_to_eat(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->n_phils)
	{
		pthread_mutex_lock(&table->philo[i].eatmutex);
		if (table->philo[i].n_meal < table->n_meals)
			return (pthread_mutex_unlock(&table->philo[i].eatmutex), 0);
		pthread_mutex_unlock(&table->philo[i].eatmutex);
	}
	if (table->n_meals == 1)
		printf("Every philosopher has eaten once\n");
	else if (table->n_meals == 2)
		printf("Every philosopher has eaten twice\n");
	else
		printf("Every philosopher has eaten %d times\n", table->n_meals);
	return (1);
}

static void	checker_2(t_table *table, int i)
{
	pthread_mutex_lock(&table->deadmutex);
	while (++i < table->n_phils && !table->end)
	{
		is_dead(table, i);
		pthread_mutex_lock(&table->deadmutex);
	}
	pthread_mutex_unlock(&table->deadmutex);
	pthread_mutex_lock(&table->deadmutex);
	if (!table->end && table->n_meals > 0 && need_to_eat(table))
	{
		table->end = 1;
		pthread_mutex_unlock(&table->deadmutex);
	}
	pthread_mutex_unlock(&table->deadmutex);
}

void	*checker(void *tab)
{
	t_table	*table;
	int		i;

	table = tab;
	while (1)
	{
		pthread_mutex_lock(&table->deadmutex);
		if (table->end)
			return (pthread_mutex_unlock(&table->deadmutex), NULL);
		pthread_mutex_unlock(&table->deadmutex);
		i = -1;
		checker_2(table, i);
	}
	return (NULL);
}
