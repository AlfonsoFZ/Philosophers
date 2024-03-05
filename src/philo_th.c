/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_th.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfofern <alfofern@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 20:20:38 by alfofern          #+#    #+#             */
/*   Updated: 2023/08/16 19:59:27 by alfofern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	muted_printf(t_table *table, char *str, int time, int id)
{
	pthread_mutex_lock(&table->deadmutex);
	if (!table->end)
	{
		pthread_mutex_lock(&table->speakmutex);
		printf("%d %d %s\n", time, id, str);
		pthread_mutex_unlock(&table->speakmutex);
	}
	pthread_mutex_unlock(&table->deadmutex);
}

static void	take_forks_and_eat_big(t_philos *philo, t_table *table)
{
	if (philo->id % 2 == 1)
	{
		pthread_mutex_lock(&table->forks[philo->r_fork]);
		muted_printf(table, "has taken a fork", timer_dif(table), philo->id);
		pthread_mutex_lock(&table->forks[philo->l_fork]);
		muted_printf(table, "has taken a fork", timer_dif(table), philo->id);
	}
	else
	{
		pthread_mutex_lock(&table->forks[philo->l_fork]);
		muted_printf(table, "has taken a fork", timer_dif(table), philo->id);
		pthread_mutex_lock(&table->forks[philo->r_fork]);
		muted_printf(table, "has taken a fork", timer_dif(table), philo->id);
	}
	pthread_mutex_lock(&table->philo[philo->r_fork].eatmutex);
	philo->last_meal = timer_dif(table);
	philo->n_meal++;
	pthread_mutex_unlock(&table->philo[philo->r_fork].eatmutex);
	muted_printf(table, "is eating", philo->last_meal, philo->id);
	to_sleep(table, table->tm_eat);
	pthread_mutex_unlock(&table->forks[philo->r_fork]);
	pthread_mutex_unlock(&table->forks[philo->l_fork]);
}

static void	take_forks_and_eat(t_philos *philo, t_table *table)
{
	pthread_mutex_lock(&table->forks[philo->r_fork]);
	muted_printf(table, "has taken a fork", timer_dif(table), philo->id);
	pthread_mutex_lock(&table->forks[philo->l_fork]);
	muted_printf(table, "has taken a fork", timer_dif(table), philo->id);
	pthread_mutex_lock(&table->philo[philo->r_fork].eatmutex);
	philo->last_meal = timer_dif(table);
	philo->n_meal++;
	pthread_mutex_unlock(&table->philo[philo->r_fork].eatmutex);
	muted_printf(table, "is eating", philo->last_meal, philo->id);
	to_sleep(table, table->tm_eat);
	pthread_mutex_unlock(&table->forks[philo->r_fork]);
	pthread_mutex_unlock(&table->forks[philo->l_fork]);
}

static	void	take_a_nap(t_philos *philo, t_table *table)
{
	muted_printf(table, "is sleeping", timer_dif(table), philo->id);
	to_sleep(table, table->tm_sleep);
	muted_printf(table, "is thinking", timer_dif(table), philo->id);
}

void	*ph_th(void *phil)
{
	t_philos	*philo;
	t_table		*table;

	philo = phil;
	table = philo->table;
	philo->r_fork = philo->id - 1;
	philo->l_fork = philo->id % table->n_phils;
	if (philo->id % 2 == 0)
		usleep(50);
	while (1)
	{
		pthread_mutex_lock(&table->deadmutex);
		if (table->end)
			return (pthread_mutex_unlock(&table->deadmutex), NULL);
		pthread_mutex_unlock(&table->deadmutex);
		if (philo->n_meal >= table->n_meals && table->n_meals > 0)
			break ;
		if (table->n_phils < 10)
			take_forks_and_eat(philo, table);
		else
			take_forks_and_eat_big(philo, table);
		take_a_nap(philo, table);
	}
	return (0);
}
