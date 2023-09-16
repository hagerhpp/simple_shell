#include "shell.h"

int _strlen(const char *s);
char *_strcpy(char *dest, const char *src);
char *_strcat(char *dest, const char *src);
char *_strncat(char *dest, const char *src, size_t n);

/**
 * _strlen - a funx that returns the length of a string
 * @s: the pointer to the characters string
 * Return: A length of the character string
 */
int _strlen(const char *s)
{
	int lgth = 0;

	if (!s)
		return (lgth);
	for (lgth = 0; s[lgth]; lgth++)
		;
	return (lgth);
}

/**
 * _strcpy - a funx that copies the string pointed to by src, including the
 * terminating null byte, to the buffer pointed by des
 * @dest: A pointer to the destination of copied string
 * @src: A pointer to the src of the source string
 * Return: Pointer to dest
 */
char *_strcpy(char *dest, const char *src)
{
	size_t i;

	for (i = 0; src[i] != '\0'; i++)
		dest[i] = src[i];
	dest[i] = '\0';
	return (dest);
}

/**
 * _strcat - a funx that concantenates two strings
 * @dest: A pointer to destination string
 * @src: A pointer to source string
 * Return: the pointer to destination string
 */
char *_strcat(char *dest, const char *src)
{
	char *destTemp;
	const char *srcTemp;

	destTemp = dest;
	srcTemp =  src;

	while (*destTemp != '\0')
		destTemp++;

	while (*srcTemp != '\0')
		*destTemp++ = *srcTemp++;
	*destTemp = '\0';
	return (dest);
}

/**
 * _strncat - a funx that concantenates two strings where n number
 * of bytes are copied from source
 * @dest: A pointer to destination string
 * @src: A pointer to source string
 * @n: the n bytes to copy from src
 * Return: the pointer to destination string
 */
char *_strncat(char *dest, const char *src, size_t n)
{
	size_t dest_len = _strlen(dest);
	size_t i;

	for (i = 0; i < n && src[i] != '\0'; i++)
		dest[dest_len + i] = src[i];
	dest[dest_len + i] = '\0';
	return (dest);
}
