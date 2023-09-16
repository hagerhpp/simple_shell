#include "shell.h"

int token_len(char *str, char *delim);
int count_tokens(char *str, char *delim);
char **_strtok(char *line, char *delim);

/**
 * token_len - a funx that locates the delimiter index marking the end
 * of the first token contained within a string
 * @str: A string to be searched
 * @delim: A delimiter character
 * Return: the delimiter index marking the end of
 * the intitial token pointed to be str
 */
int token_len(char *str, char *delim)
{
	int dex = 0, lgth = 0;

	while (*(str + dex) && *(str + dex) != *delim)
	{
		lgth++;
		dex++;
	}
	return (lgth);
}

/**
 * count_tokens - a funx that counts the number of delimited
 * words contained within a string
 * @str: A string to be searched
 * @delim: A delimiter character
 * Return: the number of words contained within str
 */
int count_tokens(char *str, char *delim)
{
	int dex, tokens = 0, lgth = 0;

	for (dex = 0; *(str + dex); dex++)
		lgth++;

	for (dex = 0; dex < lgth; dex++)
	{
		if (*(str + dex) != *delim)
		{
			tokens++;
			dex += token_len(str + dex, delim);
		}
	}
	return (tokens);
}

/**
 * _strtok - a funx that tokenizes a string
 * @line: A string
 * @delim: A delimiter character to tokenize the string by
 * Return: a pointer to an array containing the tokenized words
 */
char **_strtok(char *line, char *delim)
{
	char **ptr;
	int dex = 0, tokens, t, letters, l;

	tokens = count_tokens(line, delim);
	if (tokens == 0)
		return (NULL);

	ptr = malloc(sizeof(char *) * (tokens + 2));
	if (!ptr)
		return (NULL);

	for (t = 0; t < tokens; t++)
	{
		while (line[dex] == *delim)
			dex++;

		letters = token_len(line + dex, delim);

		ptr[t] = malloc(sizeof(char) * (letters + 1));
		if (!ptr[t])
		{
			for (dex -= 1; dex >= 0; dex--)
				free(ptr[dex]);
			free(ptr);
			return (NULL);
		}

		for (l = 0; l < letters; l++)
		{
			ptr[t][l] = line[dex];
			dex++;
		}

		ptr[t][l] = '\0';
	}
	ptr[t] = NULL;
	ptr[t + 1] = NULL;

return (ptr);
}
