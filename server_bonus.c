/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebabaogl <ebabaogl@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 10:07:45 by ebabaogl          #+#    #+#             */
/*   Updated: 2024/12/25 14:33:33 by ebabaogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include "ft_printf.h"

static void	handle_signal(int sig, siginfo_t *info, void *ucontext)
{
	static unsigned char	chr = 0;
	static unsigned int		pos = 0;

	(void)ucontext;
	if (sig == SIGUSR1)
		chr <<= 1;
	else if (sig == SIGUSR2)
		chr = (chr << 1) | 1;
	pos++;
	if (pos == 8)
	{
		ft_printf("%c", chr);
		if (chr == '\0')
			if (kill(info->si_pid, SIGUSR2) == -1)
				exit(EXIT_FAILURE);
		chr = 0;
		pos = 0;
	}
	kill(info->si_pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = handle_signal;
	if (sigaction(SIGUSR1, &sa, NULL) == -1
		|| sigaction(SIGUSR2, &sa, NULL) == -1)
		exit(EXIT_FAILURE);
	ft_printf("> PID: %d\n", getpid());
	while (1)
		pause();
}
