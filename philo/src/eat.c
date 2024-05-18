/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszabo <bszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 22:01:14 by bszabo            #+#    #+#             */
/*   Updated: 2024/05/18 07:30:03 by bszabo           ###   ########.fr       */
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
	if (data->died == false && data->nb_of_full_philos < data->nb_of_philos)
	{
		pthread_mutex_unlock(&data->lock);
		print_status(philo, "is eating");
		pthread_mutex_lock(&data->lock);
		philo->last_meal_time = get_current_time();
		if (philo->last_meal_time == -1)
			return (ERR);
		philo->meals_eaten++;
		if (philo->meals_eaten == data->nb_of_meals)
			data->nb_of_full_philos++;
		pthread_mutex_unlock(&data->lock);
		sleep_ms(data->time_to_eat);
	}
	else
		pthread_mutex_unlock(&data->lock);
	return (OK);
}

// handle the eating process (take forks -> eat -> put down forks)
// return OK if successful, ERR if not
int	philo_eat(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(&data->lock);
	if (data->died == false && data->nb_of_full_philos < data->nb_of_philos)
	{
		pthread_mutex_unlock(&data->lock);
		take_forks(philo);
		if (eat(philo) == ERR)
			return (ERR);
		put_down_forks(philo);
	}
	else
		pthread_mutex_unlock(&data->lock);
	return (OK);
}
