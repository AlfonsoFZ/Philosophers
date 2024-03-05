/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfofern <alfofern@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 21:43:11 by alfofern          #+#    #+#             */
/*   Updated: 2023/08/14 19:57:22 by alfofern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# define HEADER ("\n\
\033[91;1m\
═════════════════════════════════════════════════════════════════════════════════════════════\n\
██████╗ ██╗  ██╗██╗██╗      ██████╗ ███████╗ ██████╗ ██████╗ ██╗  ██╗███████╗██████╗ ███████╗\n\033[93;1m\
██╔══██╗██║  ██║██║██║     ██╔═══██╗██╔════╝██╔═══██╗██╔══██╗██║  ██║██╔════╝██╔══██╗██╔════╝\n\
██████╔╝███████║██║██║     ██║   ██║███████╗██║   ██║██████╔╝███████║█████╗  ██████╔╝███████╗\n\
██╔═══╝ ██╔══██║██║██║     ██║   ██║╚════██║██║   ██║██╔═══╝ ██╔══██║██╔══╝  ██╔══██╗╚════██║\n\033[91;1m\
██║     ██║  ██║██║███████╗╚██████╔╝███████║╚██████╔╝██║     ██║  ██║███████╗██║  ██║███████║\n\
╚═╝     ╚═╝  ╚═╝╚═╝╚══════╝ ╚═════╝ ╚══════╝ ╚═════╝ ╚═╝     ╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝╚══════╝\n\
═════════════════════════════════════════════════════════════════════════════════════════════\
 \n\
\033[37;1m\
                                    	== By ==                                         \n\
\033[1m\
                                        Alfofern                                       \n\
\n\033[0m")

typedef struct s_philo
{
	int					id;
	int					n_meal;
	int					last_meal;
	void				*table;
	int					r_fork;
	int					l_fork;
	pthread_t			philo;
	pthread_mutex_t		eatmutex;
}				t_philos;

typedef struct table
{
	int				i;
	int				argc;
	int				n_phils;
	int				tm_dead;
	int				tm_eat;
	int				tm_sleep;
	int				n_meals;
	int				end;
	int				tm_start;
	pthread_mutex_t	*forks;
	pthread_mutex_t	mutex;
	pthread_mutex_t	deadmutex;
	pthread_mutex_t	speakmutex;
	pthread_t		philo_th;
	t_philos		*philo;

}				t_table;

int		timer(void);
void	ft_putstr_fd(char *s, int fd);
int		ft_error_fd(char *s, int rtn);
int		ft_long_atoi(const char *str);
void	free_struct(t_table	*table);
void	*checker(void *ph);
void	*ph_th(void *ph);
int		timer_dif(t_table *table);
void	to_sleep(t_table *table, int time);
void	muted_printf(t_table *table, char *str, int time, int id);

#endif