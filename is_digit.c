#include "monty.h"

/**
* is_digit - checks if all characters in a string are digits
* @str: input string
* Return: 0 if all characters are digits, else -1
*/

int is_digit(const char *str)
{
int i = 0;

if (*str == '-')
	i = 1;

while (str[i] != '\0')
{
	if (!isdigit(str[i]))
	return (-1);
	i++;
}

return (0);
}
