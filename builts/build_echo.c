/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_echo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilallali <ilallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 16:43:29 by ilallali          #+#    #+#             */
/*   Updated: 2025/06/08 18:29:15 by ilallali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h"

static int	check_n(char *str)
{
	int	i;

	i = 1;
	while (str[i])
	{
		if((str[i] == 'n'))
			i++;
		else
			return (1);
	}
	return (0);	
}

static int check_n_option(char **arg, int *first_arg_idx)
{
	int	i;
	int	flag;

	flag = 0;
	i = 1;
	while (arg[i])
	{
		if (arg[i][0] == '-' && check_n(arg[i]) == 0)
		{
			flag = 1;
			*first_arg_idx += 1;
		}
		else
			break;
		i++;
	}
    return (flag);
}

int exec_echo(t_cmd *command)
{
	int no_newline;
    int i;
	
    i = 1;
    no_newline = check_n_option(command->args, &i);
    while (command->args[i])
    {
        write(1, command->args[i], ft_strlen(command->args[i]));
        if (command->args[i + 1])
        {
            write(1, " ", 1);
        }
        i++;
    }
    if (no_newline == 0)
    {
        write(1, "\n", 1);
    }
    return (0);
}