/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilallali <ilallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 17:19:47 by ilallali          #+#    #+#             */
/*   Updated: 2025/06/14 17:27:45 by ilallali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h"

static int is_numeric_string(const char *str)
{
    int i;

    i = 0;
    if (!str || str[i] == '\0')
        return (0);
    if (str[i] == '-' || str[i] == '+')
        i++;
    if (str[i] == '\0') // Case where string is only "+" or "-"
        return (0);
    while (str[i])
    {
        if (str[i] < '0' || str[i] > '9')
            return (0);
        i++;
    }
    return (1);
}
int exec_exit(t_cmd *command, t_env_copy **env_list)
{
    int exit_code;

    exit_code = 0;
    write(1, "exit\n", 5);
    if (command->args[1])
    {
        if (is_numeric_string(command->args[1]))
        {
            if (command->args[2])
            {
                ft_putstr_fd("minishell: exit: too many arguments\n", 2);
                return (1);
            }
            exit_code = ft_atoi(command->args[1]);
        }
        else
        {
            write(2, "minishell: exit: ", 17);
            write(2, command->args[1], ft_strlen(command->args[1]));
            write(2, ": numeric argument required\n", 28);
            exit_code = 255;
        }
    }
    // TODO: Need a function to free the 'command' list (pipeline) from the parser.
    env_lstclear(env_list);
    rl_clear_history();
    exit(exit_code);
    return (1); 
}
