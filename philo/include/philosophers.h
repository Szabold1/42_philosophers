/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszabo <bszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 15:37:28 by bszabo            #+#    #+#             */
/*   Updated: 2024/04/30 16:32:34 by bszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdio.h>
# include <pthread.h>

/* ************************************************************ Define macros */
# define OK 0
# define ERR -1
# define MAX_INT 2147483647

/* ****************************************************** Function prototypes */
// File: utils.c
void	err_msg(char *msg);
int		atoi_philo(char *str);

#endif