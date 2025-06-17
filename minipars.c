#include "exec.h"

// --- Helper: Correct t_cmd Allocator ---
// This function correctly allocates and initializes a t_cmd structure
// according to your exec.h definition.
// Your `parse_to_cmd.c` has a new_cmd that needs adjustment.
// Use this logic for creating new t_cmd nodes.
static t_redirs *new_redir_node(char *filename, t_tkn_type type)
{
    t_redirs *node;
    
    node = malloc(sizeof(t_redirs));
    if (!node)
        return (NULL);
    node->filename = ft_strdup(filename); // Assuming you have ft_strdup from Libft
    node->type = type;
    node->next = NULL;
    return (node);
}

// Adds a redirection node to the end of a redirection list
static void add_redir_to_list(t_redirs **list, t_redirs *new_node)
{
    t_redirs *current;

    if (!list || !new_node)
        return;
    if (!*list)
    {
        *list = new_node;
        return;
    }
    current = *list;
    while (current->next)
        current = current->next;
    current->next = new_node;
}

// Frees a list of redirection nodes
static void free_redir_list(t_redirs *list)
{
    t_redirs *tmp;

    while (list)
    {
        tmp = list->next;
        free(list->filename);
        free(list);
        list = tmp;
    }
}

// Your existing new_cmd function is fine
t_cmd   *new_cmd_for_parser(void)
{
    t_cmd   *cmd;

    cmd = (t_cmd *)malloc(sizeof(t_cmd));
    if (!cmd)
        return (NULL);
    cmd->args = NULL;
    cmd->pre_redirs = NULL;
    cmd->post_redirs = NULL;
    cmd->next = NULL;
    return (cmd);
}

// A more complete free_cmd_structure that handles pipelines and redirections
void    free_cmd_structure(t_cmd *cmd_list)
{
    t_cmd *tmp;

    while (cmd_list)
    {
        tmp = cmd_list->next;
        if (cmd_list->args)
        {
            for (int i = 0; cmd_list->args[i]; i++)
            {
                free(cmd_list->args[i]);
            }
            free(cmd_list->args);
        }
        if (cmd_list->pre_redirs)
            free_redir_list(cmd_list->pre_redirs);
        if (cmd_list->post_redirs)
            free_redir_list(cmd_list->post_redirs);
        free(cmd_list);
        cmd_list = tmp;
    }
}


// --- Main Parser Logic ---

#define MAX_ARGS_PER_CMD 128 // Max arguments for one command in a pipeline
#define MAX_CMDS_IN_PIPE 32  // Max commands in a pipeline

// This helper parses a single command string (a substring between pipes)
// It identifies arguments and redirection tokens.
static t_cmd *parse_single_command_segment(char *segment)
{
    t_cmd *cmd = new_cmd_for_parser();
    char *token;
    char **args = malloc(sizeof(char*) * MAX_ARGS_PER_CMD);
    int arg_count = 0;

    token = strtok(segment, " \t\n\r");
    while (token != NULL)
    {
        // Check for redirection tokens
        if (strcmp(token, ">") == 0)
        {
            token = strtok(NULL, " \t\n\r");
            if (token)
                add_redir_to_list(&cmd->post_redirs, new_redir_node(token, red_out));
        }
        else if (strcmp(token, ">>") == 0)
        {
            token = strtok(NULL, " \t\n\r");
            if (token)
                add_redir_to_list(&cmd->post_redirs, new_redir_node(token, red_apnd));
        }
        else if (strcmp(token, "<") == 0)
        {
            token = strtok(NULL, " \t\n\r");
            if (token)
                add_redir_to_list(&cmd->pre_redirs, new_redir_node(token, red_in));
        }
        else if (strcmp(token, "<<") == 0) // --- ADDED THIS BLOCK ---
        {
            token = strtok(NULL, " \t\n\r"); // The next token is the DELIMITER
            if (token)
            {
                // For heredoc, the "filename" is the delimiter.
                // We create a node with the special HEREDOC type.
                add_redir_to_list(&cmd->pre_redirs, new_redir_node(token, HEREDOC));
            }
        }
        else
        {
            // It's a regular argument
            args[arg_count++] = ft_strdup(token);
        }
        token = strtok(NULL, " \t\n\r");
    }
    args[arg_count] = NULL;
    cmd->args = args;
    return cmd;
}

// The main parser function that you call from main.c
// It now handles pipes.
t_cmd *simple_parser_to_cmd(char *line_input)
{
    char *line_copy;
    char *command_segments[MAX_CMDS_IN_PIPE];
    int cmd_count = 0;
    char *segment_token;
    t_cmd *head = NULL;
    t_cmd *current_cmd = NULL;

    if (!line_input || !*line_input)
        return (NULL);

    line_copy = ft_strdup(line_input);

    // First, split the entire line by the pipe '|' character
    segment_token = strtok(line_copy, "|");
    while (segment_token != NULL && cmd_count < MAX_CMDS_IN_PIPE)
    {
        command_segments[cmd_count++] = segment_token;
        segment_token = strtok(NULL, "|");
    }

    // Now, parse each command segment individually
    for (int i = 0; i < cmd_count; i++)
    {
        t_cmd *new_node = parse_single_command_segment(command_segments[i]);
        if (!head)
        {
            head = new_node;
            current_cmd = head;
        }
        else
        {
            current_cmd->next = new_node;
            current_cmd = new_node;
        }
    }

    free(line_copy);
    return (head);
}