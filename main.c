/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilallali <ilallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 17:32:05 by ilallali          #+#    #+#             */
/*   Updated: 2025/05/31 14:12:40 by ilallali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int main(void)
{
    char *input;
	// t_cmd *cmds;
	// create_env(envp);
    while (1)
    {
        input = readline("minishell$ ");
        if (!input)
        {
            printf("exit\n");
            break;
        }
        if (*input) // Non-empty input
            add_history(input);
        if (strcmp(input, "exit") == 0)
        {
            free(input);
            break;
        }
		tokens = mock_tokens(input);
        free(input);
    }
	while (tokens)
	{
		printf("%s | type: %d\n", tokens->vl, tokens->tkn_typ);
		tokens = tokens->next; 
	}
	
    return 0;
}
