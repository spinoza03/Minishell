/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilallali <ilallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 16:19:34 by ilallali          #+#    #+#             */
/*   Updated: 2025/06/19 16:19:54 by ilallali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h"

int count_commands(t_cmd *cmd_list)
{
    int count;

    count = 0;
    while (cmd_list)
    {
        count++;
        cmd_list = cmd_list->next;
    }
    return (count);
}