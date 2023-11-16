#include "monty.h"
info_t info;
char *resize(int i, int *n, char *buf);

/**
 *_getline - reads a line of characters from a stream
 *@buffer: buffer to store the line
 *@n: buffer size
 *@stream: where to read the line
 *Return: 0 on success and -1 on failure
 */
ssize_t _getline(char **buffer, int *n, FILE *stream)
{
	int i = 0, ch;

	if (*buffer == NULL || *n == 0)
	{
		*buffer = malloc(5);
		if (*buffer == NULL)
		{
			free(buffer);
			return (-1);
		}
		*n = 5;
	}
	while (1)
	{
		ch = fgetc(stream);
		if (ch == EOF)
		{
			if (i == 0)
			{
				free(*buffer);
				return (-1);
			}
			else
			{
				(*buffer)[i] = '\0';
				return (0);
			}
		}
		/* resize the buffer if not enough*/
		if (i >= (*n - 1))
		{
			*buffer = resize(i, n, *buffer);
		}
		(*buffer)[i++] = ch; /* add character to buffer */
		if (ch == '\n') /* check if the character is a new line char */
		{
			(*buffer)[i] = '\0';
			return (0);
		}
	}
}

/**
 *resize - resize the buffer
 *@i: the iterator
 *@n: size of buffer
 *@buf: previous buffer
 *Return: new buffer created
 */
char *resize(int i, int *n, char *buf)
{
        char *new;
        int new_size = (*n * 2);
	(void)i;

        new = realloc(buf, new_size);
        if (new == NULL)
        {
                free(new);
                return (NULL);
        }
        *n = new_size;

        return (new);
}

/**
 * treat_monty - Treat The Monty File
 * @filename: Filename From Argument
 * Return: Data Of The Monty File
 */
int treat_monty(char *filename)
{
	ssize_t n_r = 1;
	int len = 0;
	stack_t *stack = NULL;

	info.fn = filename;
	info.fp = fopen(info.fn, "r");
	if (info.fp == NULL)
		handle_error(3);
	while ((n_r = _getline(&info.cmd, &len, info.fp)) > 0)
	{
		if (*info.cmd == '\n')
			continue;
		info.l_number++;
		free(info.arg);
		if (split() < 0)
			continue;
		if (info.arg == NULL)
			continue;
		excute_monty(&stack);
	}
	free_info();
	free_list(stack);
	return (0);
}
/**
 * split - Split The Line Into Command and Arguments
 *
 *Return: 0 On Success 1 On Failure
 */
int split(void)
{
	char *token;
	size_t bufsize = 20, i = 0;

	info.arg = malloc(bufsize * sizeof(char *));
	if (info.arg == NULL)
		handle_error(1);
	token = strtok(info.cmd, DELIMITER);
	while (token)
	{
		info.arg[i++] = token;
		if (i >= bufsize)
		{
			info.arg = _realloc(info.arg, bufsize, bufsize * 2);
			if (info.arg == NULL)
			{
				handle_error(1);
			}
		}
		token = strtok(NULL, DELIMITER);
	}
	info.arg[i] = NULL;
	if (**info.arg == '#')
		return (-1);
	return (0);
}
#include "monty.h"
/**
 * excute_monty - Verifie Monty Command And Excute it
 * @stack: Stack or Queue
 * Return: 0 On Valid Command 1 On Commant Not Found
 */
int excute_monty(stack_t **stack)
{
	instruction_t command[] = {
		{"push", push_monty},
		{"pall", pall_monty},
		{"pint", pint_monty},
		{"pop", pop_monty},
		{"swap", swap_monty},
		{"add", add_monty},
		{"nop", nop_monty},
		{"sub", sub_monty},
		{"div", div_monty},
		{"mul", mul_monty},
		{"mod", mod_monty},
		{"#", nop_monty},
		{"pchar", pchar_monty},
		{"pstr", pstr_monty},
		{"rotl", rotl_monty},
		{"rotr", rotr_monty},
		{"stack", _stack},
		{"queue", _queue},
		{NULL, NULL}
	};
	int i = 0;

	while ((command + i)->opcode)
	{
		if (strcmp((command + i)->opcode, *info.arg) == 0)
		{
			(command + i)->f(stack, info.l_number);
			return (0);
		}
		i++;
	}
	handle_error(4);
	return (1);
}
