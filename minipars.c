#include "exec.h"

// --- Helper: Correct t_cmd Allocator ---
// This function correctly allocates and initializes a t_cmd structure
// according to your exec.h definition.
// Your `parse_to_cmd.c` has a new_cmd that needs adjustment.
// Use this logic for creating new t_cmd nodes.
t_cmd   *new_cmd_for_parser(void)
{
    t_cmd   *cmd;

    cmd = (t_cmd *)malloc(sizeof(t_cmd));
    if (!cmd)
        return (NULL);
    cmd->args = NULL;
    cmd->pre_redirs = NULL;  // As per your exec.h
    cmd->post_redirs = NULL; // As per your exec.h
    cmd->next = NULL;
    return (cmd);
}

// --- Helper: Free t_cmd Structure ---
void    free_cmd_structure(t_cmd *cmd)
{
    if (!cmd)
        return;

    // Free the args array and its strings
    if (cmd->args)
    {
        for (int i = 0; cmd->args[i] != NULL; i++)
        {
            free(cmd->args[i]);
        }
        free(cmd->args);
    }

    // TODO: Later, you will need to free pre_redirs and post_redirs lists here
    // if (cmd->pre_redirs) free_redirs_list(cmd->pre_redirs);
    // if (cmd->post_redirs) free_redirs_list(cmd->post_redirs);
    
    // TODO: Later, if cmd->next is used for pipelines, you'll free the list
    // if (cmd->next) free_cmd_structure(cmd->next); // Or an iterative free

    free(cmd);
}


// --- Our Very Simple Parser (Simulates Friend's Parser for Single Commands) ---
// Takes a line and returns a t_cmd structure.
// For now, only handles space-separated arguments, no quotes, no pipes, no redirections.
// Assumes the first word is the command (absolute path for Day 1).
#define MAX_MOCK_ARGS 32 // Maximum arguments our simple parser will handle for one command

t_cmd   *simple_parser_to_cmd(char *line_input)
{
    t_cmd   *cmd_struct;
    char    *line_copy;
    char    *token;
    char    **temp_args;
    int     arg_count = 0;

    if (!line_input || !*line_input)
        return (NULL);

    cmd_struct = new_cmd_for_parser();
    if (!cmd_struct)
        return (NULL);

    line_copy = strdup(line_input); // strtok modifies the string, so we use a copy
    if (!line_copy)
    {
        perror("minishell: strdup for simple_parser");
        free_cmd_structure(cmd_struct);
        return (NULL);
    }

    // First, count arguments to allocate exact space for cmd_struct->args
    char *count_copy = strdup(line_copy); // Another copy for counting
    if (!count_copy) {
        perror("minishell: strdup for count_copy");
        free(line_copy);
        free_cmd_structure(cmd_struct);
        return (NULL);
    }
    token = strtok(count_copy, " \t\n\r");
    while (token != NULL)
    {
        arg_count++;
        token = strtok(NULL, " \t\n\r");
    }
    free(count_copy);

    if (arg_count == 0) // Empty line or only whitespace
    {
        free(line_copy);
        free_cmd_structure(cmd_struct);
        return (NULL);
    }
    
    // Allocate the args array (+1 for NULL terminator)
    cmd_struct->args = (char **)malloc(sizeof(char *) * (arg_count + 1));
    if (!cmd_struct->args)
    {
        perror("minishell: malloc for args array");
        free(line_copy);
        free_cmd_structure(cmd_struct);
        return (NULL);
    }

    // Now, populate the args array
    arg_count = 0; // Reset for populating
    token = strtok(line_copy, " \t\n\r"); // Use the first copy of the line
    while (token != NULL && arg_count < MAX_MOCK_ARGS)
    {
        cmd_struct->args[arg_count] = strdup(token);
        if (!cmd_struct->args[arg_count])
        {
            perror("minishell: strdup for argument");
            // Free already strdup'd args
            for (int i = 0; i < arg_count; i++)
                free(cmd_struct->args[i]);
            free(cmd_struct->args); // Free the array itself
            cmd_struct->args = NULL; // Avoid double free in free_cmd_structure
            free(line_copy);
            free_cmd_structure(cmd_struct);
            return (NULL);
        }
        arg_count++;
        token = strtok(NULL, " \t\n\r");
    }
    cmd_struct->args[arg_count] = NULL; // NULL-terminate the args array for execve

    free(line_copy); // Free the duplicated input line

    // cmd_struct->pre_redirs, post_redirs, and next are already NULL from new_cmd_for_parser
    return (cmd_struct);
}
