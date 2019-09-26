#include "monty.h"

/**
 * execute_script - reads instructions from bytecod file and executes them
 */
void execute_script(void)
{
	char *line = NULL;
	size_t len = 0;
	int i;
	unsigned int line_number = 0;
	instruction_t ops[] = {
		{"push", stack_push}, {"pall", stack_pall}, {"pint", stack_pint},
		{"pop", stack_pop}, {"swap", stack_swap}, {"add", stack_add},
		{"nop", stack_nop}, {"sub", stack_sub}, {"div", stack_div},
		{"mul", stack_mul}, {"mod", stack_mod}, {"pchar", stack_pchar},
		{"pstr", stack_pstr}, {"rotl", stack_rotl}, {"rotr", stack_rotr},
		{NULL, NULL}
	};
	stack_t *stack = NULL;

	while (getline(&line, &len, mem.pScript) != -1)
	{
		line_number++;
		if (line[0] == '#')
			continue;
		/* Finds opcode in ops[] */
		mem.token = strtok(line, " \n");
		for (i = 0; ops[i].opcode != NULL; i++)
		{
			if (strcmp(ops[i].opcode, mem.token) == 0)
			{
				mem.n = strtok(NULL, " \n");
				ops[i].f(&stack, line_number);
				break;
			}
		}
		if (ops[i].opcode == NULL)
		{
			fprintf(stderr, "L%d: unknown instruction %s\n", line_number, mem.token);
			free_all(stack);
			exit(EXIT_FAILURE);
		}
	}
	free_all(stack);
}
