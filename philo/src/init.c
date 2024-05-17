/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszabo <bszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 10:21:45 by bszabo            #+#    #+#             */
/*   Updated: 2024/05/16 11:29:28 by bszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// initialize the forks
// return OK if successful, ERR if not
static int	init_forks(t_data *data)
{
	int	i;

	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_of_philos);
	if (data->forks == NULL)
		return (err_msg(MALLOC_ERR), ERR);
	i = 0;
	while (i < data->nb_of_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (err_msg(MUTEX_INIT_ERR), ERR);
		i++;
	}
	return (OK);
}

// initialize the philos struct
// return OK if successful, ERR if not
static int	init_philos(t_data *data)
{
	int	i;

	data->philos = malloc(sizeof(t_philo) * data->nb_of_philos);
	if (data->philos == NULL)
		return (err_msg(MALLOC_ERR), ERR);
	i = 0;
	while (i < data->nb_of_philos)
	{
		data->philos[i].id = i + 1;
		if (i == 0)
			data->philos[i].fork_left_index = data->nb_of_philos - 1;
		else
			data->philos[i].fork_left_index = i - 1;
		data->philos[i].fork_right_index = i;
		data->philos[i].last_meal_time = -1;
		data->philos[i].meals_eaten = 0;
		data->philos[i].data = data;
		i++;
	}
	return (OK);
}

// initialize the data struct and the philosophers
// return OK if successful, ERR if not
int	init(char *argv[], t_data *data)
{
	data->nb_of_philos = atoi_philo(argv[1]);
	if (data->nb_of_philos < 1)
		return (err_msg("Invalid number of philosophers"), ERR);
	data->time_to_die = atoi_philo(argv[2]);
	data->time_to_eat = atoi_philo(argv[3]);
	data->time_to_sleep = atoi_philo(argv[4]);
	if (argv[5])
		data->nb_of_meals = atoi_philo(argv[5]);
	else
		data->nb_of_meals = -1;
	data->start_time = -1;
	data->nb_of_full_philos = 0;
	data->died = false;
	if (init_forks(data) == ERR)
		return (ERR);
	if (pthread_mutex_init(&data->print_lock, NULL) != 0)
		return (err_msg(MUTEX_INIT_ERR), ERR);
	if (pthread_mutex_init(&data->lock, NULL) != 0)
		return (err_msg(MUTEX_INIT_ERR), ERR);
	if (init_philos(data) == ERR)
		return (ERR);
	return (OK);
}
