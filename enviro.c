#include "shell.h"

char **_copyenv(void);
void free_env(void);
char **_getenv(const char *var);

/**
 * _copyenv - a funx that creates a copy of the environment.
 * Return: if an error occurs - NULLO/w - a double pointer to the new copy
 */
char **_copyenv(void)
{
	char **new_environ;
	size_t size;
	int dex;

	for (size = 0; environ[size]; size++)
		;

	new_environ = malloc(sizeof(char *) * (size + 1));
	if (!new_environ)
		return (NULL);

	for (dex = 0; environ[dex]; dex++)
	{
		new_environ[dex] = malloc(_strlen(environ[dex]) + 1);

		if (!new_environ[dex])
		{
			for (dex--; dex >= 0; dex--)
				free(new_environ[dex]);
			free(new_environ);
			return (NULL);
		}
		_strcpy(new_environ[dex], environ[dex]);
	}
	new_environ[dex] = NULL;

	return (new_environ);
}

/**
 * free_env - a funx that frees the the environment copy
 */
void free_env(void)
{
	int dex;

	for (dex = 0; environ[dex]; dex++)
		free(environ[dex]);
	free(environ);
}

/**
 * _getenv - a funx that gets an environmental variable from the PATH
 * @var: the name of the environmental variable to get
 * Return: if the environmental variable does not exist - NULL
 * Otherwise - a pointer to the environmental variable
 */
char **_getenv(const char *var)
{
	int dex, lgth;

	lgth = _strlen(var);
	for (dex = 0; environ[dex]; dex++)
	{
		if (_strncmp(var, environ[dex], lgth) == 0)
			return (&environ[dex]);
	}

	return (NULL);
}