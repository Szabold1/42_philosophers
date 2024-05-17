/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszabo <bszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 22:01:14 by bszabo            #+#    #+#             */
/*   Updated: 2024/05/17 10:49:33 by bszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// eat if possible (print status, update last meal time, and meals eaten)
// return OK if successful, ERR if not
static int	eat(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(&data->lock);
	if (data->died || data->nb_of_full_philos == data->nb_of_philos)
		return (pthread_mutex_unlock(&data->lock), ERR);
	else
	{
		pthread_mutex_unlock(&data->lock);
		print_status(philo, "is eating");
		philo->last_meal_time = get_current_time();
		if (philo->last_meal_time == -1)
			return (ERR);
		philo->meals_eaten++;
		// printf("philo %d meals eaten: %d\n", philo->id, philo->meals_eaten);
		pthread_mutex_lock(&data->lock);
		if (philo->meals_eaten == data->nb_of_meals)
			data->nb_of_full_philos++;
		// printf("full philos: %d\n", data->nb_of_full_philos);
		pthread_mutex_unlock(&data->lock);
		sleep_ms(data->time_to_eat);
	}
	return (OK);
}

// handle the eating process (take forks -> eat -> put down forks)
// return OK if successful, ERR if not
int	philo_eat(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(&data->lock);
	if (data->died || data->nb_of_full_philos == data->nb_of_philos)
		return (pthread_mutex_unlock(&data->lock), ERR);
	pthread_mutex_unlock(&data->lock);
	take_forks(philo);
	if (eat(philo) == ERR)
		return (ERR);
	put_down_forks(philo);
	return (OK);
}
