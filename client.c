/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebabaogl <ebabaogl@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 13:36:10 by ebabaogl          #+#    #+#             */
/*   Updated: 2024/12/25 15:17:06 by ebabaogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include "ft_printf.h"

int	g_signal_received = 0;

static int	ft_atoi(char *str)
{
	int	res;

	res = 0;
	while (*str >= '0' && *str <= '9')
	{
		res *= 10;
		res += *str - '0';
		str++;
	}
	return (res);
}

static void	send_char(int pid, char c)
{
	int	i;

	i = 8;
	while (i--)
	{
		if ((c >> i) & 1)
		{
			if (kill(pid, SIGUSR2) == -1)
				exit(EXIT_FAILURE);
		}
		else
		{
			if (kill(pid, SIGUSR1) == -1)
				exit(EXIT_FAILURE);
		}
		while (!g_signal_received)
			;
		g_signal_received = 0;
	}
}

static void	handle_response(int sig)
{
	(void)sig;
	g_signal_received = 1;
}

int	main(int argc, char **argv)
{
	struct sigaction	sa;
	int					pid;

	if (argc != 3)
		exit(EXIT_FAILURE);
	pid = ft_atoi(argv[1]);
	if (pid == 0)
		exit(EXIT_FAILURE);
	sigemptyset(&sa.sa_mask);
	sa.sa_handler = handle_response;
	sa.sa_flags = 0;
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
		exit(EXIT_FAILURE);
	while (*argv[2])
		send_char(pid, *argv[2]++);
	send_char(pid, '\n');
	send_char(pid, '\0');
}
