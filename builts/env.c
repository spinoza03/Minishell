/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilallali <ilallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 18:56:53 by ilallali          #+#    #+#             */
/*   Updated: 2025/05/25 19:08:43 by ilallali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	builtins_builder(char *inp)
{
	if(strcmp(inp, "env"))
		exec_env();
	else if(strcmp(inp, "echo"))
		exec_echo();
	else if(strcmp(inp, "cat"))
		exec_cat();
	else if(strcmp(inp, "cd"))
		exec_cd();
	else if(strcmp(inp, "export"))
		exec_echo();
	else if(strcmp(inp, "unset"))
		exec_echo();
}