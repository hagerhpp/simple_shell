#include "shell.h"

void handle_line(char **line, ssize_t read);
ssize_t get_new_len(char *line);
void logical_ops(char *line, ssize_t *new_len);

/**
 * handle_line - a funx that partitions a line read from standard input
 * as needed
 * @line: the pointer to a line read from standard input
 * @read: a length of line
 * Description: the spaces are inserted to separate ";", "||", and "&&"
 * Replaces "#" with '\0'
 */
void handle_line(char **line, ssize_t read)
{
	char *old_line, *new_line;
	char previous, current, next;
	size_t i, x;
	ssize_t new_len;

	new_len = get_new_len(*line);
	if (new_len == read - 1)
		return;
	new_line = malloc(new_len + 1);
	if (!new_line)
		return;
	x = 0;
	old_line = *line;
	for (i = 0; old_line[i]; i++)
	{
		current = old_line[i];
		next = old_line[i + 1];
		if (i != 0)
		{
			previous = old_line[i - 1];
			if (current == ';')
			{
				if (next == ';' && previous != ' ' && previous != ';')
				{
					new_line[x++] = ' ';
					new_line[x++] = ';';
					continue;
				}
				else if (previous == ';' && next != ' ')
				{
					new_line[x++] = ';';
					new_line[x++] = ' ';
					continue;
				}
				if (previous != ' ')
					new_line[x++] = ' ';
				new_line[x++] = ';';
				if (next != ' ')
					new_line[x++] = ' ';
				continue;
			}
			else if (current == '&')
			{
				if (next == '&' && previous != ' ')
					new_line[x++] = ' ';
				else if (previous == '&' && next != ' ')
				{
					new_line[x++] = '&';
					new_line[x++] = ' ';
					continue;
				}
			}
			else if (current == '|')
			{
				if (next == '|' && previous != ' ')
					new_line[x++]  = ' ';
				else if (previous == '|' && next != ' ')
				{
					new_line[x++] = '|';
					new_line[x++] = ' ';
					continue;
				}
			}
		}
		else if (current == ';')
		{
			if (i != 0 && old_line[i - 1] != ' ')
				new_line[x++] = ' ';
			new_line[x++] = ';';
			if (next != ' ' && next != ';')
				new_line[x++] = ' ';
			continue;
		}
		new_line[x++] = old_line[i];
	}
	new_line[x] = '\0';

	free(*line);
	*line = new_line;
}

/**
 * get_new_len - a funx that gets the new length of a line partitioned
 * by ";", "||", "&&&", or "#"
 * @line: A line to check
 * Return: A new length of the line
 * Description: cuts short lines containing '#' comments with '\0'
 */
ssize_t get_new_len(char *line)
{
	size_t j;
	ssize_t new_len = 0;
	char current, next;

	for (j = 0; line[j]; j++)
	{
		current = line[j];
		next = line[j + 1];
		if (current == '#')
		{
			if (j == 0 || line[j - 1] == ' ')
			{
				line[j] = '\0';
				break;
			}
		}
		else if (j != 0)
		{
			if (current == ';')
			{
				if (next == ';' && line[j - 1] != ' ' && line[j - 1] != ';')
				{
					new_len += 2;
					continue;
				}
				else if (line[j - 1] == ';' && next != ' ')
				{
					new_len += 2;
					continue;
				}
				if (line[j - 1] != ' ')
					new_len++;
				if (next != ' ')
					new_len++;
			}
			else
				logical_ops(&line[j], &new_len);
		}
		else if (current == ';')
		{
			if (j != 0 && line[j - 1] != ' ')
				new_len++;
			if (next != ' ' && next != ';')
				new_len++;
		}
		new_len++;
	}
	return (new_len);
}

/**
 * logical_ops - a funx that checks a line for logical operators
 * "||" or "&&"
 * @line: the pointer to the character to check in the line
 * @new_len: a pointer to new_len in get_new_len function
 */
void logical_ops(char *line, ssize_t *new_len)
{
	char previous, current, next;

	previous = *(line - 1);
	current = *line;
	next = *(line + 1);

	if (current == '&')
	{
		if (next == '&' && previous != ' ')
			(*new_len)++;
		else if (previous == '&' && next != ' ')
			(*new_len)++;
	}
	else if (current == '|')
	{
		if (next == '|' && previous != ' ')
			(*new_len)++;
		else if (previous == '|' && next != ' ')
			(*new_len)++;
}
}
