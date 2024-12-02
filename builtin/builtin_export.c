/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abinti-a <abinti-a@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 10:58:14 by abinti-a          #+#    #+#             */
/*   Updated: 2024/12/02 09:26:32 by abinti-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 * Print error message for export
 */
static void	print_export_error(char *arg)
{
	ft_putstr_fd("minishell: export: '", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
}

/**
 * Function to add a new variable to env
 *
 * 1. Get the number of variables in existing env
 * 2. Duplicate the new variable to end of env
 * 3. Add NULL terminator at the end
 */
int	add_to_env(char **env, const char *new_var)
{
	int		size;
	char	*new_str;

	size = get_env_size(env);
	new_str = ft_strdup(new_var);
	if (!new_str)
		return (1);
	env[size] = new_str;
	env[size + 1] = NULL;
	return (0);
}

/**
 * Function to update/add value of a variable
 *
 * 1. Get variable name length
 * 2. Copy variable name to var_name
 * 3. Check for if the variable name is valid
 * 4. Update value for variable if it already exists
 * 5. If variable is new, add variable to env
 */
static int	handle_equal(char **env, char *arg, char *equal_sign)
{
	char	var_name[PATH_MAX];
	int		name_len;

	name_len = equal_sign - arg;
	ft_strlcpy(var_name, arg, name_len + 1);
	if (!valid_var_name(var_name))
	{
		print_export_error(arg);
		return (1);
	}
	if (!update_env_value(env, var_name, equal_sign + 1))
		return (add_to_env(env, arg));
	return (0);
}

/**
 * Main builtin_export function
 *
 * 1. Check for arguments
 * 2. If no arguments, print env in alphabetical order
 * 3. If theres arguments, loop through the arguments.
 * 4. Check for '=' in the argument. If exists, call handle_equal
 * 5. If theres no '=', check for valid variable name
 * 6. Add valid variable to env
 */
int	builtin_export(char **args, t_mshell *shell)
{
	int		i;
	char	*equal_sign;

	if (!args[1])
		return (print_sorted_env(shell->env));
	i = 1;
	while (args[i])
	{
		equal_sign = ft_strchr(args[i], '=');
		if (equal_sign && handle_equal(shell->env, args[i], equal_sign))
			return (1);
		else if (!equal_sign)
		{
			if (!valid_var_name(args[i]))
			{
				print_export_error(args[i]);
				return (1);
			}
			if (add_to_env(shell->env, args[i]))
				return (1);
		}
		i++;
	}
	return (0);
}

// int main(int argc, char **argv, char **envp)
// {
//     (void)argc;
//     (void)argv;
// 	t_mshell shell;

//     shell.env = copy_env(envp);
// 	printf("Initial env:\n");
// 	builtin_env(NULL, &shell);
// 	printf("\n");

//     printf("Test: Add new variable\n");
//     char *args1[] = {"export", "NEW_VAR=value", NULL};
//     builtin_export(args1, &shell);
// 	builtin_env(NULL, &shell);
// 	printf("\n");

//     // printf("Test: Update existing variable\n");
//     // char *args2[] = {"export", "NEW_VAR=updated_value", NULL};
//     // builtin_export(args2, &shell);
// 	// builtin_env(NULL, &shell);
// 	// printf("\n");

//     // printf("Test: Invalid variable\n");
//     // char *args3[] = {"export", "2INVALID=value", NULL};
//     // builtin_export(args3, &shell);
// 	// builtin_env(NULL, &shell);
// 	// printf("\n");

// 	// printf("Test: variable without value\n");
// 	// char *args4[] = {"export", "No_value", NULL};
// 	// builtin_export(args4, &shell);
// 	// printf("\n");
// 	// builtin_env(NULL, &shell);
// 	// printf("\n");

//     printf("Final Environment:\n");
//     char *args5[] = {"export", NULL};
//     builtin_export(args5, &shell);

//     free_array(shell.env);

//     return (0);
// }
