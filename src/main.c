/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfofern <alfofern@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 19:32:38 by alfofern          #+#    #+#             */
/*   Updated: 2023/08/16 20:21:17 by alfofern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	checkargs(char *argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		i = -1;
		while (argv[++i])
			if (argv[i] < '0' || argv[i] > '9')
				return (ft_error_fd ("please use possitive numbers\n", -1));
	}
	return (ft_long_atoi(argv));
}

static int	init_table(t_table	*table, char **argv, int argc)
{
	table->argc = argc;
	table->tm_sleep = checkargs(argv[3]);
	table->tm_dead = checkargs(argv[1]);
	table->tm_eat = checkargs(argv[2]);
	table->n_phils = checkargs(argv[0]);
	if (table->tm_eat < 0 || table->tm_dead < 0
		|| table->n_phils < 0)
		return (5);
	if (table->n_phils == 0)
		return (ft_error_fd ("please include at least one philosopher\n", 2));
	if (table->n_phils == 1)
	{
		printf("1 has taken a fork\n");
		usleep(table->tm_dead);
		printf("%d i is dead\n", table->tm_dead + 1);
		return (1);
	}
	table->n_meals = -1;
	if (argv[4])
		table->n_meals = checkargs(argv[4]);
	table->end = 0;
	table->tm_start = timer();
	return (0);
}

static int	ft_mutex_init(t_table	*table)
{
	int	i;

	if (pthread_mutex_init(&table->mutex, 0))
		return (ft_error_fd("mutex failed\n", 1));
	if (pthread_mutex_init(&table->deadmutex, 0))
		return (ft_error_fd("mutex failed\n", 1));
	if (pthread_mutex_init(&table->speakmutex, 0))
		return (ft_error_fd("mutex failed\n", 1));
	table->forks = malloc(sizeof(pthread_mutex_t) * table->n_phils);
	if (!table->forks)
		return (ft_error_fd("Forks memory malloc failed\n", 2));
	i = -1;
	while (++i < table->n_phils)
	{
		if (pthread_mutex_init(&table->forks[i], 0))
		{
			free_struct(table);
			return (ft_error_fd("Failed creating forks\n", 3));
		}
	}
	return (0);
}

static int	philos_init(t_table	*table)
{
	int	i;

	table->philo = malloc(sizeof(t_philos) * table->n_phils);
	if (!table->philo)
		return (ft_error_fd("Philos memory allocated failed\n", 1));
	i = -1;
	while (++i < table->n_phils)
	{
		if (pthread_mutex_init(&table->philo[i].eatmutex, 0))
		{
			free_struct(table);
			return (ft_error_fd("Failed creating eatmutex\n", 3));
		}
		pthread_mutex_lock(&table->philo[i].eatmutex);
		table->philo[i].last_meal = 0;
		table->philo[i].n_meal = 0;
		pthread_mutex_unlock(&table->philo[i].eatmutex);
		table->philo[i].table = table;
		table->philo[i].id = i + 1;
		if (pthread_create(&table->philo[i].philo, 0, ph_th, &table->philo[i]))
			return (ft_error_fd("Error creating philo\n", 1));
	}
	if (pthread_create(&table->philo_th, 0, checker, table))
		return (ft_error_fd("Error creating thread\n", 1));
	return (0);
}

// void    ft_leaks(void)
// {
//     system ("leaks -q philo");
// }
//	atexit(ft_leaks); //include this sentence into the main function

int	main(int argc, char *argv[])
{
	t_table	table;
	int		init;
	int		i;

	printf("%s", (char *)&(HEADER));
	if (argc != 5 && argc != 6)
		return (ft_putstr_fd ("invalid number of arguments\n", 2), 1);
	init = init_table(&table, &argv[1], argc);
	if (init == 0 && table.n_meals == 0)
		return (printf("every philosopher has eaten 0 times\n"), 0);
	if (init == 0)
	{
		if (pthread_mutex_init(&table.mutex, 0))
			return (ft_error_fd("mutex_init failed\n", 1));
		ft_mutex_init(&table);
		philos_init(&table);
		pthread_join(table.philo_th, 0);
		i = -1;
		while (++i < table.n_phils)
			pthread_join(table.philo[i].philo, 0);
		free_struct(&table);
	}
	return (0);
}
