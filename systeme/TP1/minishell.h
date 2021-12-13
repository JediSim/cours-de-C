#define SIZE_BUFFER 9999
#define HOME "/home"

#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"

int getcmd(char* CMD_LINE, char** CMD_ELEMS);

int eqcmd(char* cmd, char* value);

void action_quit();

void action_pwd();

void action_ls();

void action_exec(char *exe, char **cmd);

int isIn(char* value, char** string);

void isPipe(char** CMD_ELEMS);