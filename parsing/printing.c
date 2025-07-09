/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mteffahi <mteffahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 22:03:44 by mteffahi          #+#    #+#             */
/*   Updated: 2025/07/05 22:04:13 by mteffahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdio.h>

// Function to print redirections (pre_redirs or post_redirs)
void print_redirs(t_redirs *redir_list, const char *label) {
    while (redir_list) {
        printf("    %s: filename='%s', type=%d\n", label, redir_list->filename, redir_list->type);
        redir_list = redir_list->next;
    }
}

// Function to print the t_cmd linked list
void print_cmd_list(t_cmd *cmd_list) {
    int cmd_num = 1;

    while (cmd_list) {
        printf("=== Command #%d ===\n", cmd_num);

        // Print arguments
        if (cmd_list->args) {
            printf("  args: ");
            for (int i = 0; cmd_list->args[i]; i++) {
                printf("'%s' ", cmd_list->args[i]);
            }
            printf("\n");
        } else {
            printf("  args: (none)\n");
        }

        // Print redirections
        if (cmd_list->pre_redirs)
            print_redirs(cmd_list->pre_redirs, "pre_redir");
        else
            printf("  pre_redirs: (none)\n");

        if (cmd_list->post_redirs)
            print_redirs(cmd_list->post_redirs, "post_redir");
        else
            printf("  post_redirs: (none)\n");

        // Move to next command
        cmd_list = cmd_list->next;
        cmd_num++;
    }
}
