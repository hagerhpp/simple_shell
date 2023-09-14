#include "shell.h"

int cant_open(char *file_path);
int proc_file_commands(char *file_path, int *exe_ret);

/**
 * cant_open - a funx that if the file doesn't exist or lacks proper
 * permissions, print a cant open error
 * @file_path: the Path to the supposed file
 * Return: 127
 */
int cant_open(char *file_path)
{
	char *error, *hist_str;
	int lgth;

	hist_str = _itoa(hist);
	if (!hist_str)
		return (127);

	lgth = _strlen(name) + _strlen(hist_str) + _strlen(file_path) + 16;
	error = malloc(sizeof(char) * (lgth + 1));
	if (!error)
	{
		free(hist_str);
		return (127);
	}

	_strcpy(error, name);
	_strcat(error, ": ");
	_strcat(error, hist_str);
	_strcat(error, ": Can't open ");
	_strcat(error, file_path);
	_strcat(error, "\n");

	free(hist_str);
	write(STDERR_FILENO, error, lgth);
	free(error);
	return (127);
}

/**
 * proc_file_commands - a funx that takes a file and attempts to run
 * the commands stored
 * within
 * @file_path: the path to the file
 * @exe_ret: A return value of the last executed command
 * Return: If file couldn't be opened - 127
 * If malloc fails - -1
 * Otherwise the return value of the last command ran
 */

int proc_file_commands(char *file_path, int *exe_ret)
{
	ssize_t file, b_read, x;
	unsigned int line_size = 0;
	unsigned int old_size = 120;
	char *line, **args, **front;
	char buffer[120];
	int ret;

	hist = 0;
	file = open(file_path, O_RDONLY);
	if (file == -1)
	{
		*exe_ret = cant_open(file_path);
		return (*exe_ret);
	}
	line = malloc(sizeof(char) * old_size);
	if (!line)
		return (-1);
	do {
		b_read = read(file, buffer, 119);
		if (b_read == 0 && line_size == 0)
			return (*exe_ret);
		buffer[b_read] = '\0';
		line_size += b_read;
		line = _realloc(line, old_size, line_size);
		_strcat(line, buffer);
		old_size = line_size;
	} while (b_read);
	for (x = 0; line[x] == '\n'; x++)
		line[x] = ' ';
	for (; x < line_size; x++)
	{
		if (line[x] == '\n')
		{
			line[x] = ';';
			for (x += 1; x < line_size && line[x] == '\n'; x++)
				line[x] = ' ';
		}
	}
	variable_replacement(&line, exe_ret);
	handle_line(&line, line_size);
	args = _strtok(line, " ");
	free(line);
	if (!args)
		return (0);
	if (check_args(args) != 0)
	{
		*exe_ret = 2;
		free_args(args, args);
		return (*exe_ret);
	}
	front = args;
	for (x = 0; args[x]; x++)
	{
		if (_strncmp(args[x], ";", 1) == 0)
		{
			free(args[x]);
			args[x] = NULL;
			ret = call_args(args, front, exe_ret);
			args = &args[++x];
			x = 0;
		}
	}

	ret = call_args(args, front, exe_ret);

	free(front);
	return (ret);
}