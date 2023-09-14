#include "shell.h"

char *fill_path_dir(char *path);
list_t *get_path_dir(char *path);

/**
 * get_location - a funx that locates a command in the PATH
 * @command: A command to locate
 * Return: If an error occurs or the command cannot be located - NULL
 * Otherwise : a full pathname of the command
 */
char *get_location(char *command)
{
	char **path, *temp;
	list_t *dirs, *head;
	struct stat st;

	path = _getenv("PATH");
	if (!path || !(*path))
		return (NULL);

	dirs = get_path_dir(*path + 5);
	head = dirs;

	while (dirs)
	{
		temp = malloc(_strlen(dirs->dir) + _strlen(command) + 2);
		if (!temp)
			return (NULL);

		_strcpy(temp, dirs->dir);
		_strcat(temp, "/");
		_strcat(temp, command);

		if (stat(temp, &st) == 0)
		{
			free_list(head);
			return (temp);
		}

		dirs = dirs->next;
		free(temp);
	}

	free_list(head);

	return (NULL);
}

/**
 * fill_path_dir - funx that copies path but also replaces
 * leading/sandwiched/trailing
 * colons (:) with current working directory
 * @path: A colon-separated list of directories
 * Return: A copy of path with any leading/sandwiched/trailing colons replaced
 * with the current working directory
 */
char *fill_path_dir(char *path)
{
	int i, lgth = 0;
	char *path_copy, *pwd;

	pwd = *(_getenv("PWD")) + 4;
	for (i = 0; path[i]; i++)
	{
		if (path[i] == ':')
		{
			if (path[i + 1] == ':' || i == 0 || path[i + 1] == '\0')
				lgth += _strlen(pwd) + 1;
			else
				lgth++;
		}
		else
			lgth++;
	}
	path_copy = malloc(sizeof(char) * (lgth + 1));
	if (!path_copy)
		return (NULL);
	path_copy[0] = '\0';
	for (i = 0; path[i]; i++)
	{
		if (path[i] == ':')
		{
			if (i == 0)
			{
				_strcat(path_copy, pwd);
				_strcat(path_copy, ":");
			}
			else if (path[i + 1] == ':' || path[i + 1] == '\0')
			{
				_strcat(path_copy, ":");
				_strcat(path_copy, pwd);
			}
			else
				_strcat(path_copy, ":");
		}
		else
		{
			_strncat(path_copy, &path[i], 1);
		}
	}
	return (path_copy);
}

/**
 * get_path_dir - funx that tokenizes a colon-separated list of
 * directories into a list_s linked list
 * @path: A colon-separated list of directories
 * Return: the pointer to the initialized linked list
 */
list_t *get_path_dir(char *path)
{
	int dex;
	char **dirs, *path_copy;
	list_t *head = NULL;

	path_copy = fill_path_dir(path);
	if (!path_copy)
		return (NULL);
	dirs = _strtok(path_copy, ":");
	free(path_copy);
	if (!dirs)
		return (NULL);

	for (dex = 0; dirs[dex]; dex++)
	{
		if (add_node_end(&head, dirs[dex]) == NULL)
		{
			free_list(head);
			free(dirs);
			return (NULL);
		}
	}

	free(dirs);

	return (head);
}