#ifndef MONTY_H
#define MONTY_H

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

/**
 * struct stack_s - doubly linked list representation of a stack (or queue)
 * @n: integer
 * @prev: points to the previous element of the stack (or queue)
 * @next: points to the next element of the stack (or queue)
 *
 * Description: doubly linked list node structure
 * for stack, queues, LIFO, FIFO
 */
typedef struct stack_s
{
        int n;
        struct stack_s *prev;
        struct stack_s *next;
} stack_t;

/**
 * struct instruction_s - opcode and its function
 * @opcode: the opcode
 * @f: function to handle the opcode
 *
 * Description: opcode and its function
 * for stack, queues, LIFO, FIFO
 */
typedef struct instruction_s
{
        char *opcode;
        void (*f)(stack_t **stack, unsigned int line_number);
} instruction_t;

/*helpers.c */
int dlistint_len(stack_t *stack);
int delete_dnodeint_at_index(stack_t **head, int index);

/* rot.c */
void rotl_monty(stack_t **stack, unsigned int line_number);
void rotr_monty(stack_t **stack, unsigned int line_number);

/* pr_str.c */
void pstr_monty(stack_t **stack, unsigned int line_number);

/* pr_char.c */
void pchar_monty(stack_t **stack, unsigned int line_number);
void pchar_error(void);
void pchar_error_2(void);

/* command.c */
void push_monty(stack_t **stack, unsigned int line_number);
void pall_monty(stack_t **stack, unsigned int line_number);
void pint_monty(stack_t **stack, unsigned int line_number);
void pop_monty(stack_t **stack, unsigned int line_number);

/* error.c */
void handle_error(int code);
void malloc_fail(void);
void file_perm(void);
void unknown_command(void);

/* error2 */
void push_use(void);
void pint_error(void);
void pop_error(void);
void swap_error(void);

/* errors3 */
void add_error(void);
void sub_error(void);
void monty_usage(void);
void div_error(void);

/* even_more_commands */
void div_monty(stack_t **stack, unsigned int line_number);
void mul_monty(stack_t **stack, unsigned int line_number);
void mod_monty(stack_t **stack, unsigned int line_number);

/* info.c */
int treat_monty(char *filename);
int split(void);
int excute_monty(stack_t **stack);

/* mem_mgt */
void free_info(void);
void free_list(stack_t *stack);

/* monnty_helpers.c */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char *_memcpy(char *dest, char *src, unsigned int n);
void *fill_an_array(void *a, int el, unsigned int len);
int _isdigit(char *str);

/* monty_main.c */
int main(int argc, char **argv);

/* more_commands.c */
void swap_monty(stack_t **stack, unsigned int line_number);
void add_monty(stack_t **stack, unsigned int line_number);
void nop_monty(stack_t **stack, unsigned int line_number);
void sub_monty(stack_t **stack, unsigned int line_number);

/* more_errors.c */
void _zero(void);
void mul_error(void);
void mod_error(void);

/* stack.c */
void _stack(stack_t **stack, unsigned int line_number);
void _queue(stack_t **stack, unsigned int line_number);
void add_node_lifo(stack_t **stack, stack_t *n_node);
void add_node_fifo(stack_t **stack, stack_t *n_node);

#endif
