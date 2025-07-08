/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilallali <ilallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 19:31:45 by ilallali          #+#    #+#             */
/*   Updated: 2025/07/08 13:03:40 by ilallali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h"

void sigint_handler(int signum)
{
    // The subject is very specific about what can happen in a signal handler.
    // We should not call complex functions like printf or malloc here.
    // The functions allowed inside a handler are very limited.
    // A safe approach is to just set a global flag, but for this specific
    // "new prompt" behavior, we can use the functions provided by readline.
    
    (void)signum; // We don't need the signal number for this simple handler.

    write(1, "\n", 1); // Move to a new line
    rl_on_new_line(); // Tell readline we are on a new line
    rl_replace_line("", 0); // Replace the existing buffer with an empty string
    rl_redisplay(); // Redisplay the prompt and the empty buffer
}

void initialize_signals(void)
{
    struct sigaction sa_int;

    // Set up the handler for SIGINT (Ctrl-C)
    sa_int.sa_handler = sigint_handler;
    sigemptyset(&sa_int.sa_mask); // Don't block any other signals during handling
    sa_int.sa_flags = 0;

    // Apply the handler. If sigaction fails, print an error.
    if (sigaction(SIGINT, &sa_int, NULL) == -1)
    {
        perror("minishell: sigaction");
    }

    // TODO later: We will also need to ignore SIGQUIT (Ctrl-\)
    // signal(SIGQUIT, SIG_IGN);
}

void	set_execution_signals(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}
