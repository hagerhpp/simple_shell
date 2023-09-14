#include "shell.h"

char *_strchr(char *s, char c);
int _strspn(char *s, char *accept);
int _strcmp(char *s1, char *s2);
int _strncmp(const char *s1, const char *s2, size_t n);

/**
 * _strchr - a funx that locates a character in a string
 * @s: A string to be searched
 * @c: A character to be located
 * Return: If c is found - a pointer to the first occurence
 * if c is not found - NULL
 */
char *_strchr(char *s, char c)
{
	int dex;

	for (dex = 0; s[dex]; dex++)
	{
		if (s[dex] == c)
			return (s + dex);
	}

	return (NULL);
}

/**
 * _strspn - a funx that gets the length of a prefix substring
 * @s: A string to be searched
 * @accept: A prefix to be measured
 * Return: A number of bytes in s which
 * consist only of bytes from accept
 */
int _strspn(char *s, char *accept)
{
	int bytes = 0;
	int dex;

	while (*s)
	{
		for (dex = 0; accept[dex]; dex++)
		{
			if (*s == accept[dex])
			{
				bytes++;
				break;
			}
		}
		s++;
	}
	return (bytes);
}

/**
 * _strcmp - a funx that compares two strings
 * @s1: A first string to be compared
 * @s2: A second string to be compared
 * Return: positive byte difference if s1 > s2
 * 0 if s1 = s2
 * Negative byte difference if s1 < s2
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}

	if (*s1 != *s2)
		return (*s1 - *s2);

	return (0);
}

/**
 * _strncmp - a funx that compare two strings
 * @s1: A pointer to a string
 * @s2: A pointer to a string
 * @n: A first n bytes of the strings to compare
 * Return: Less than 0 if s1 is shorter than s2
 * 0 if s1 and s2 match
 * Greater than 0 if s1 is longer than s2
 */
int _strncmp(const char *s1, const char *s2, size_t n)
{
	size_t i;

	for (i = 0; s1[i] && s2[i] && i < n; i++)
	{
		if (s1[i] > s2[i])
			return (s1[i] - s2[i]);
		else if (s1[i] < s2[i])
			return (s1[i] - s2[i]);
	}
	if (i == n)
		return (0);
	else
		return (-15);
}