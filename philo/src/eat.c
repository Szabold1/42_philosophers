/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszabo <bszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 22:01:14 by bszabo            #+#    #+#             */
/*   Updated: 2024/05/29 13:25:44 by bszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// take the right fork if the philosopher can
static void	take_right_fork(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(&data->forks[philo->fork_right_index]);
	pthread_mutex_lock(&data->lock);
	if (data->died == false && data->nb_of_full_philos < data->nb_of_philos)
	{
		pthread_mutex_unlock(&data->lock);
		print_status(philo, "has taken a fork");
	}
	else
		pthread_mutex_unlock(&data->lock);
}

// take the left fork if the philosopher can
static void	take_left_fork(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(&data->forks[philo->fork_left_index]);
	pthread_mutex_lock(&data->lock);
	if (data->died == false && data->nb_of_full_philos < data->nb_of_philos)
	{
		pthread_mutex_unlock(&data->lock);
		print_status(philo, "has taken a fork");
	}
	else
		pthread_mutex_unlock(&data->lock);
}

// eat if possible (print status, update last meal time, and meals eaten)
static void	eat(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(&data->lock);
	if (data->died == false && data->nb_of_full_philos < data->nb_of_philos)
	{
		pthread_mutex_unlock(&data->lock);
		print_status(philo, "is eating");
		pthread_mutex_lock(&data->lock);
		philo->meals_eaten++;
		if (philo->meals_eaten == data->nb_of_meals)
			data->nb_of_full_philos++;
		philo->last_meal_time = get_current_time();
		pthread_mutex_unlock(&data->lock);
		sleep_ms(data->time_to_eat, data);
	}
	else
		pthread_mutex_unlock(&data->lock);
}

// handle the eating process (take forks -> eat -> put down forks)
void	philo_eat(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	if (philo->id % 2 == 0)
	{
		take_left_fork(philo);
		take_right_fork(philo);
		eat(philo);
		pthread_mutex_unlock(&data->forks[philo->fork_right_index]);
		pthread_mutex_unlock(&data->forks[philo->fork_left_index]);
	}
	else
	{
		take_right_fork(philo);
		take_left_fork(philo);
		eat(philo);
		pthread_mutex_unlock(&data->forks[philo->fork_left_index]);
		pthread_mutex_unlock(&data->forks[philo->fork_right_index]);
	}
}
