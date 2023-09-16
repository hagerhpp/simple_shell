#include "shell.h"

int shellby_alias(char **args, char __attribute__((__unused__)) **front);
void set_alias(char *var_name, char *value);
void print_alias(alias_t *alias);

/**
 * shellby_alias - a funx that builtin command that either prints all
 * specific aliases
 * @args: an array of arguments
 * @front: a double pointer to the beginning of args
 * Return: if an error occurs - -1
 * otherwise : 0
 */
int shellby_alias(char **args, char __attribute__((__unused__)) **front)
{
	alias_t *temp = aliases;
	int y, ret = 0;
	char *value;

	if (!args[0])
	{
		while (temp)
		{
			print_alias(temp);
			temp = temp->next;
		}
		return (ret);
	}
	for (y = 0; args[y]; y++)
	{
		temp = aliases;
		value = _strchr(args[y], '=');
		if (!value)
		{
			while (temp)
			{
				if (_strcmp(args[y], temp->name) == 0)
				{
					print_alias(temp);
					break;
				}
				temp = temp->next;
			}
			if (!temp)
				ret = create_error(args + y, 1);
		}
		else
			set_alias(args[y], value);
	}
	return (ret);
}

/**
 * set_alias - a funx that will either set an existing alias 'name' with
 * a new value 'value' or creates a new alias with 'name' and 'value'
 * @var_name: a name of the alias
 * @value: a value of the alias. First character is a '='
 */
void set_alias(char *var_name, char *value)
{
	alias_t *temp = aliases;
	int len, x, j;
	char *new_value;

	*value = '\0';
	value++;
	len = _strlen(value) - _strspn(value, "'\"");
	new_value = malloc(sizeof(char) * (len + 1));
	if (!new_value)
		return;
	for (x = 0, j = 0; value[x]; x++)
	{
		if (value[x] != '\'' && value[x] != '"')
			new_value[j++] = value[x];
	}
	new_value[j] = '\0';
	while (temp)
	{
		if (_strcmp(var_name, temp->name) == 0)
		{
			free(temp->value);
			temp->value = new_value;
			break;
		}
		temp = temp->next;
	}
	if (!temp)
		add_alias_end(&aliases, var_name, new_value);
}

/**
 * print_alias - a funx that prints the alias in the format name='value'
 * @alias: a pointer to an alias
 */
void print_alias(alias_t *alias)
{
	char *alias_string;
	int len = _strlen(alias->name) + _strlen(alias->value) + 4;

	alias_string = malloc(sizeof(char) * (len + 1));
	if (!alias_string)
		return;
	_strcpy(alias_string, alias->name);
	_strcat(alias_string, "='");
	_strcat(alias_string, alias->value);
	_strcat(alias_string, "'\n");

	write(STDOUT_FILENO, alias_string, len);
	free(alias_string);
}

/**
 * replace_aliases - a funx that goes through the arguments and
 * replace any matching alias with their value
 * @args: 2D pointer to the arguments
 * Return: 2D pointer to the arguments
 */
char **replace_aliases(char **args)
{
	alias_t *temp;
	int x;
	char *new_value;

	if (_strcmp(args[0], "alias") == 0)
		return (args);
	for (x = 0; args[x]; x++)
	{
		temp = aliases;
		while (temp)
		{
			if (_strcmp(args[x], temp->name) == 0)
			{
				new_value = malloc(sizeof(char) * (_strlen(temp->value) + 1));
				if (!new_value)
				{
					free_args(args, args);
					return (NULL);
				}
				_strcpy(new_value, temp->value);
				free(args[x]);
				args[x] = new_value;
				x--;
				break;
			}
			temp = temp->next;
		}
	}

	return (args);
}
