/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszabo <bszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 09:51:14 by bszabo            #+#    #+#             */
/*   Updated: 2024/05/17 09:54:32 by bszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// check continuously for the end of the simulation
// return true if a philosopher died or all philosophers ate all meals
static bool	check_end(t_data *data)
{
	int	i;

	while (1)
	{
		i = 0;
		while (i < data->nb_of_philos)
		{
			pthread_mutex_lock(&data->lock);
			if (data->nb_of_full_philos == data->nb_of_philos)
			{
				// print_status(&data->philos[i], "ALL PHILOSOPHERS ATE ALL MEALS");
				return (pthread_mutex_unlock(&data->lock), true);
			}
			if (get_current_time()
				- data->philos[i].last_meal_time > data->time_to_die)
			{
				print_status(&data->philos[i], "died");
				data->died = true;
				pthread_mutex_unlock(&data->lock);
				return (true);
			}
			pthread_mutex_unlock(&data->lock);
			usleep(1000);
			i++;
		}
	}
	return (false);
}

// join the threads of the philosophers
static void	join_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_of_philos)
	{
		pthread_join(data->philos[i].thread_id, NULL);
		i++;
	}
}

// start simulation by creating the threads for the philosophers
// return OK if successful, ERR if not
int	simulation(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_of_philos)
	{
		data->start_time = get_current_time();
		if (data->start_time == -1)
			return (ERR);
		data->philos[i].last_meal_time = data->start_time;
		if (pthread_create(&data->philos[i].thread_id, NULL, &routine,
			&data->philos[i]) != 0)
			return (err_msg(THREAD_CREATE_ERR), ERR);
		i++;
	}
	check_end(data);
	join_threads(data);
	return (OK);
}
