#include "shell.h"

void free_args(char **args, char **front);
char *get_pid(void);
char *get_env_value(char *beginning, int len);
void variable_replacement(char **args, int *exe_ret);

/**
 * free_args - a funx that frees up memory taken by args
 * @args: the null-terminated double pointer containing commands/arguments
 * @front: the double pointer to the beginning of args
 */
void free_args(char **args, char **front)
{
	size_t i;

	for (i = 0; args[i] || args[i + 1]; i++)
		free(args[i]);

	free(front);
}

/**
 * get_pid - a funx that gets the current process ID
 * Description: it opens the stat file, a space-delimited file containing
 * information about the current process. The PID is the
 * first word in the file. The function reads the PID into
 * a buffer and replace the space at the end with a \0 byte
 * Return: a current process ID or NULL on failure
 */
char *get_pid(void)
{
	size_t x = 0;
	char *buffer;
	ssize_t file;

	file = open("/proc/self/stat", O_RDONLY);
	if (file == -1)
	{
		perror("Cant read file");
		return (NULL);
	}
	buffer = malloc(120);
	if (!buffer)
	{
		close(file);
		return (NULL);
	}
	read(file, buffer, 120);
	while (buffer[x] != ' ')
		x++;
	buffer[x] = '\0';

	close(file);
	return (buffer);
}

/**
 * get_env_value - a funx that gets the value corresponding to
 * an environmental variable
 * @beginning: an environmental variable to search for
 * @len: the length of the environmental variable to search for
 * Return: If the variable is not found - an empty string
 * Otherwise : a value of the environmental variable
 * Description: the variables are stored in the format VARIABLE=VALUE
 */
char *get_env_value(char *beginning, int len)
{
	char **var_addr;
	char *replacement = NULL, *temp, *var;

	var = malloc(len + 1);
	if (!var)
		return (NULL);
	var[0] = '\0';
	_strncat(var, beginning, len);

	var_addr = _getenv(var);
	free(var);
	if (var_addr)
	{
		temp = *var_addr;
		while (*temp != '=')
			temp++;
		temp++;
		replacement = malloc(_strlen(temp) + 1);
		if (replacement)
			_strcpy(replacement, temp);
	}

	return (replacement);
}

/**
 * variable_replacement - a funx that handles variable replacement
 * @line: the double pointer containing the command and arguments
 * @exe_ret: the pointer to the return value of the last executed command
 * Description: It replaces $$ with the current PID, $? with the return value
 * of the last executed program, and envrionmental variables
 * preceded by $ with their corresponding value
 */
void variable_replacement(char **line, int *exe_ret)
{
	int s, i = 0, lgth;
	char *replacement = NULL, *old_line = NULL, *new_line;

	old_line = *line;
	for (s = 0; old_line[s]; s++)
	{
		if (old_line[s] == '$' && old_line[s + 1] &&
				old_line[s + 1] != ' ')
		{
			if (old_line[s + 1] == '$')
			{
				replacement = get_pid();
				i = s + 2;
			}
			else if (old_line[s + 1] == '?')
			{
				replacement = _itoa(*exe_ret);
				i = s + 2;
			}
			else if (old_line[s + 1])
			{
				/* extract the variable name to search for */
				for (i = s + 1; old_line[i] &&
						old_line[i] != '$' &&
						old_line[i] != ' '; i++)
					;
				lgth = i - (s + 1);
				replacement = get_env_value(&old_line[s + 1], lgth);
			}
			new_line = malloc(s + _strlen(replacement)
					  + _strlen(&old_line[i]) + 1);
			if (!line)
				return;
			new_line[0] = '\0';
			_strncat(new_line, old_line, s);
			if (replacement)
			{
				_strcat(new_line, replacement);
				free(replacement);
				replacement = NULL;
			}
			_strcat(new_line, &old_line[i]);
			free(old_line);
			*line = new_line;
			old_line = new_line;
			s = -1;
		}
	}
}