int open_log();
int log_write(char *prg_name, int type, char *msg);
void close_log();
int display_log(char* log_prg_name);

#define INFO 1
#define WARNING 2
#define ERROR 3