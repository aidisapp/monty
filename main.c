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
			{"pint", pint},
			{"pall", pall},
			{"pop", pop},
			{"swap", swap},
			{"add", add_op},
			{"nop", nop},
			{"sub", sub_op},
			{"div", div_op},
			{"mul", mul_op},
			{"mod", mod_op},
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
 * process_file - Read the Monty ByteCodes file and process each line.
 * @file: File pointer to the Monty ByteCodes file
 * @stack_head: Pointer to the head of the stack
 */

void process_file(FILE *file, stack_t **stack_head)
{
	unsigned int line_number = 1;
	char *buffer = malloc(sizeof(char) * BUFFER_SIZE), *token;
	ssize_t bytes_read;

	if (!buffer)
	{
		fclose(file);
		exit(EXIT_FAILURE);
	}

	while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, file)) > 0)
	{
		token = strtok(buffer, "\n\t\a\r ;:");

		while (token != NULL)
		{
			process_token(token, stack_head, line_number);
			token = strtok(NULL, "\n\t\a\r ;:");
			line_number++;
		}
	}

	free(buffer);
}

/**
 * process_token - Process a token from the Monty ByteCodes file.
 * @token: Token to be processed
 * @stack_head: Pointer to the head of the stack
 * @line_num: Current line number in the Monty ByteCodes file
 */

void process_token(char *token, stack_t **stack_head, unsigned int line_num)
{
	void (*operator_function)(stack_t **stack, unsigned int line_num);

	if (strcmp(token, "push") == 0)
	{
		push(stack_head, line_num, strtok(NULL, "\n\t\a\r ;:"));
	}
	else
	{
		operator_function = get_instruction(token);
		if (operator_function != NULL)
		{
			operator_function(stack_head, line_num);
		}
		else
		{
			free_list(stack_head);
			fprintf(stderr, "L%d: unknown instruction %s\n", line_num, token);
			exit(EXIT_FAILURE);
		}
	}
}

/**
 * main - Main entry point into the interpreter.
 * @argc: Number of command-line arguments
 * @argv: Array of command-line arguments
 * Return: 0 on success, EXIT_FAILURE on failure
 */

int main(int argc, char *argv[])
{
	FILE *file;
	stack_t *stack_head;

	if (argc != 2)
	{
		fprintf(stderr, "USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}

	file = fopen(argv[1], "r");

	if (file == NULL)
	{
		fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}

	stack_head = NULL;

	process_file(file, &stack_head);

	free_list(&stack_head);
	fclose(file);

	return (0);
}
