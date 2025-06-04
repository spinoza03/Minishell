/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nodes_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilallali <ilallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 14:40:32 by ilallali          #+#    #+#             */
/*   Updated: 2025/06/02 14:41:08 by ilallali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h"

void del_env_node_content(t_env_copy *node)
{
    if (!node)
        return;
    if (node->key)
    {
        free(node->key);
        node->key = NULL;
    }
    if (node->value)
    {
        free(node->value);
        node->value = NULL;
    }
}
