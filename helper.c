
#include "helper.h"

/******************************************************************************
* prints the device's username
******************************************************************************/
void print_user()
{
	printf("%s> ", getenv("USER"));
}

/******************************************************************************
* gets character
******************************************************************************/
char getch(FILE *fp)
{
	if (fp != NULL)
	{
		return fgetc(fp);
	}

	system("stty -echo");
	system("stty -icanon");
	char ch = getchar();
	system("stty sane");
  	return ch;
}

/******************************************************************************
* deletes the current character.
******************************************************************************/
void delete(int len, char* line)
{
	line[len] = '\0';
	printf("\b \b");
}

/******************************************************************************
* Determines which special character is processed.
******************************************************************************/
char switch_keypad(char ch)
{
	switch(ch)
	{
		case 'A': return KEYUP;
		case 'B': return KEYDOWN;
		case 'C': return KEYRIGHT;
		case 'D': return KEYLEFT;
		default:  return ch;
	}
}

/******************************************************************************
* Trims whitespace.
******************************************************************************/
char* trim(char *word, int len) {

	while (word[0] == WHITE_SPACE) {
		++word;
		--len;
	}
	while ((word + len - 1)[0] == WHITE_SPACE) --len;

	if (len < 1) return NULL;

	char *trimmed = (char *)malloc(len + 1);
	memcpy(trimmed, word, len);
	trimmed[len] = '\0';

	return trimmed;
}

/******************************************************************************
* Returns the number of tokens
******************************************************************************/
int get_arg_number(char *cmd) {

	int i = 0, j = 1;

	while (i < strlen(cmd)) if (cmd[++i] == WHITE_SPACE) ++j;

	return j;
}

/******************************************************************************
* transforms commands to a char***
******************************************************************************/
char*** transform_linked_list_to_3d_char(struct linked_list *commands,
	int number_of_commands) {

	char ***argv = (char***)malloc(sizeof(char**) * (number_of_commands + 1)),
		*cmd;

	struct linked_list *temp;
	int number_of_arguments;

	argv[number_of_commands] = NULL;

	for (int i = 0; i < number_of_commands; ++i)
	{		
		cmd = (char*)commands->value;
		number_of_arguments = get_arg_number(cmd);

		argv[i] = (char**)malloc(sizeof(char*) * (number_of_arguments + 1));
		argv[i][number_of_arguments] = NULL;

		for (int j = 0, k, m = 0, n = 0; j < number_of_arguments; ++m)
		{
			if (cmd[m] == WHITE_SPACE || cmd[m] == '\0') {
				k = m - n + 1;

				argv[i][j] = (char*)malloc(sizeof(char) * k);
				memcpy(argv[i][j], cmd + n, k - 1);
				argv[i][j++][k - 1] = '\0';
				n = m + 1;
			}
		}

		free(commands->value);
		temp = commands;
		commands = commands->next;
		free(temp);
	}

	return argv;
}

void print(FILE *fp, char *fmt, int j)
{
	char msg[MAX_STR_LEN];

	sprintf(msg, fmt, j);

	printf("%s", msg);
	fprintf(fp, "%s", msg);
}

void print_exceed_memory(FILE *fp, int j)
{
	print(fp, "Unable to run job #%d. Memory requirements exceed system"
		" capabilities\n", j);
}

void print_insufficient_memory(FILE *fp, int j)
{
	print(fp, "Unable to run job #%d. Insufficient memory resources\n", j);
}
void print_starting(FILE *fp, int j)
{
	print(fp, "Starting job #%d\n", j);
}
void print_completed(FILE *fp, int j)
{
	print(fp, "Job #%d completed\n", j);
}

void print_memory_status(FILE *fp, int mem)
{
	print(fp, "Memory at %d\n", mem);
}
void print_allocate_memory(FILE *fp, int mem, int req)
{
	print(fp, "Allocating %d\n", req);
	print_memory_status(fp, mem);
}
void print_deallocate_memory(FILE *fp, int mem, int req)
{
	print(fp, "Deallocating %d\n", req);
	print_memory_status(fp, mem);
}