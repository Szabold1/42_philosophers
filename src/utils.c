/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszabo <bszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 15:58:26 by bszabo            #+#    #+#             */
/*   Updated: 2024/08/31 12:49:22 by bszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// print an error message to stderr
void	err_msg(char *msg)
{
	int	len;

	len = 0;
	while (msg[len])
		len++;
	write(2, "Error: ", 7);
	write(2, msg, len);
	write(2, "\n", 1);
}

// convert a string to an integer and return it
// return ERR if 'str' is not a valid positive integer
int	atoi_philo(char *str)
{
	long long	num;
	int			i;

	num = 0;
	i = 0;
	if (!str || !str[0] || str[0] == '-' || str[0] == '+')
		return (ERR);
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (ERR);
		num = num * 10 + (str[i] - '0');
		if (num > MAX_INT)
			return (ERR);
		i++;
	}
	return (num);
}

// get the current time in milliseconds
// 1 second = 1000 milliseconds (ms)
long long	get_current_time(void)
{
	struct timeval	time;
	long long		time_ms;

	gettimeofday(&time, NULL);
	time_ms = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (time_ms);
}

// print the status of the philosopher with the current timestamp in ms
void	print_status(t_philo *philo, char *status)
{
	t_data		*data;
	long long	time;

	data = philo->data;
	time = get_current_time() - data->start_time;
	if (data->should_die)
		time += 2;
	pthread_mutex_lock(&data->print_lock);
	if (!data->died || status[0] == 'd')
		printf("%lld %d %s\n", time, philo->id, status);
	pthread_mutex_unlock(&data->print_lock);
}

// sleep for 'time' milliseconds
void	sleep_ms(int time, t_data *data)
{
	long long	start_time;
	long long	end_time;

	start_time = get_current_time();
	end_time = start_time + time;
	while (start_time < end_time)
	{
		pthread_mutex_lock(&data->lock);
		if (data->died || data->nb_of_full_philos == data->nb_of_philos)
		{
			pthread_mutex_unlock(&data->lock);
			return ;
		}
		pthread_mutex_unlock(&data->lock);
		usleep(100);
		start_time = get_current_time();
	}
}
