/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszabo <bszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 15:37:40 by bszabo            #+#    #+#             */
/*   Updated: 2024/05/21 16:13:27 by bszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// check number of arguments and if they are valid
// return OK if valid, ERR if invalid
int	check_args(int argc, char *argv[])
{
	int	i;
	int	tmp;

	if (argc != 5 && argc != 6)
		return (err_msg("Invalid number of arguments"), ERR);
	i = 1;
	while (i < argc)
	{
		tmp = atoi_philo(argv[i]);
		if (tmp == ERR || (i == 1 && tmp < 1) || (i == 1 && tmp > 220) || (i == 5 && tmp < 1))
			return (err_msg("Invalid argument"), ERR);
		i++;
	}
	return (OK);
}

// Arguments:	(1.)number_of_philosophers
// 				(2.)time_to_die
// 				(3.)time_to_eat
// 				(4.)time_to_sleep
// 				(5.)[number_of_times_each_philosopher_must_eat]
int	main(int argc, char *argv[])
{
	t_data	data;

	if (check_args(argc, argv) == ERR)
		return (1);
	if (init(argv, &data) == ERR)
		return (1);
	if (simulation(&data) == ERR)
		return (clean_up(&data), 1);
	return (clean_up(&data), 0);
}
