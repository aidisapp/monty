#include "monty.h"

/**
 * get_instruction - Get Monty bytecode instructions.
 * @token: bytecode operator input
 * Return: pointer to operation function
 */
void (*get_instruction(char *token))(stack_t **head, unsigned int line_num)
{
	int count;
	instruction_t instruction_s[] = {
			{"pall", pall},
			{NULL, NULL}};

	count = 0;
	while (instruction_s[count].f != NULL)
	{
		if (strcmp(token, instruction_s[count].opcode) == 0)
			return (instruction_s[count].f);
		count++;
	}
	return (NULL);
}

/**
 * main - entry into interpreter
 * @argc: argument count
 * @argv: arguments
 * Return: 0 on success
 */
int main(int argc, char *argv[])
{
	int file_descriptor, is_push = 0;
	unsigned int line_number = 1;
	ssize_t bytes_read;
	char *buffer, *token;
	stack_t *stack_head = NULL;

	if (argc != 2)
	{
		printf("USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}

	file_descriptor = open(argv[1], O_RDONLY);
	if (file_descriptor == -1)
	{
		printf("Error: Can't open file %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}

	buffer = malloc(sizeof(char) * 10000);
	if (!buffer)
		return (0);

	bytes_read = read(file_descriptor, buffer, 10000);
	if (bytes_read == -1)
	{
		free(buffer);
		close(file_descriptor);
		exit(EXIT_FAILURE);
	}

	token = strtok(buffer, "\n\t\a\r ;:");
	while (token != NULL)
	{
		if (is_push == 1)
		{
			push(&stack_head, line_number, token);
			is_push = 0;
			token = strtok(NULL, "\n\t\a\r ;:");
			line_number++;
			continue;
		}
		else if (strcmp(token, "push") == 0)
		{
			is_push = 1;
			token = strtok(NULL, "\n\t\a\r ;:");
			continue;
		}
		else
		{
			if (get_instruction(token) != 0)
			{
				get_instruction(token)(&stack_head, line_number);
			}
			else
			{
				free_list(&stack_head);
				printf("L%d: unknown instruction %s\n", line_number, token);
				exit(EXIT_FAILURE);
			}
		}
		line_number++;
		token = strtok(NULL, "\n\t\a\r ;:");
	}

	free_list(&stack_head);
	free(buffer);
	close(file_descriptor);
	return (0);
}

