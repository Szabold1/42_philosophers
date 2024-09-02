/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszabo <bszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 13:24:58 by bszabo            #+#    #+#             */
/*   Updated: 2024/09/02 08:12:10 by bszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// handle the sleeping process (print status and sleep for time_to_sleep)
static void	philo_sleep(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(&data->lock);
	if (data->died == false && data->nb_of_full_philos < data->nb_of_philos)
	{
		pthread_mutex_unlock(&data->lock);
		print_status(philo, "is sleeping");
		sleep_ms(data->time_to_sleep, data);
	}
	else
		pthread_mutex_unlock(&data->lock);
}

// handle the thinking process (print status)
static void	philo_think(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(&data->lock);
	if (data->died == false && data->nb_of_full_philos < data->nb_of_philos)
	{
		pthread_mutex_unlock(&data->lock);
		print_status(philo, "is thinking");
		usleep(200);
	}
	else
		pthread_mutex_unlock(&data->lock);
}

// routine for the philosopher threads
// each philosopher will try to eat, sleep, and think in a loop until
// the simulation is done or a philosopher died
void	*routine(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)arg;
	data = philo->data;
	if (data->nb_of_philos == 1)
		return (print_status(philo, "has taken a fork"),
			sleep_ms(data->time_to_die, data), (NULL));
	pthread_mutex_lock(&data->lock);
	while (data->died == false && data->nb_of_full_philos < data->nb_of_philos)
	{
		if (data->nb_of_meals != -1 && philo->meals_eaten >= data->nb_of_meals)
			break ;
		pthread_mutex_unlock(&data->lock);
		philo_eat(philo);
		philo_sleep(philo);
		if (data->nb_of_philos % 2 != 0 && data->time_to_eat
			> data->time_to_sleep && data->time_to_eat
			+ data->time_to_sleep < data->time_to_die)
			sleep_ms(data->time_to_sleep, data);
		philo_think(philo);
		pthread_mutex_lock(&data->lock);
	}
	pthread_mutex_unlock(&data->lock);
	return (NULL);
}
