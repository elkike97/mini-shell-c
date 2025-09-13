/* $begin shellmain */
#include "csapp.h"

#define MAXARGS   128

/* function prototypes */
void eval(char*cmdline);
int parseline(char *buf, char **argv);
int builtin_command(char **argv); 
char *vars[10] = {0}; /*this will contain the variables that are set*/
char* ptr; /*pointer to malloc string*/
int artic; /*number of vars*/
int lengthVars;
char *tracker;
char newString[50];


int main() 
{
	vars = (char *)malloc(10 * sizeof(char));
    char cmdline[MAXLINE]; /* command line */

    while (1) {//creates an infinite loop to keep the shell running
	/* read */
	printf("> "); //print a prompt for the user to know to proceed and write                  
	Fgets(cmdline, MAXLINE, stdin); //reads a line of input from stdin and stores it in cmdline
	if (feof(stdin))//checks if the EOF has been reached
	    exit(0);//if EOF has been reached, exits the shell

	/* evaluate */
	eval(cmdline);//calls the eval function defined below
    } 
}
/* $end shellmain */
  
/* $begin eval */
/* eval - evaluate a command line */
void eval(char *cmdline) 
{
    char *argv[MAXARGS]; /* argv for execve() */
    char buf[MAXLINE];   /* holds modified command line */
    int bg;              /* should the job run in bg or fg? */
    pid_t pid;           /* process id */
    
    strcpy(buf, cmdline);//function copies content of cmdline into buf->
	//modifies buf but leaves cmdline pristine
    bg = parseline(buf, argv); //splits the command line into arguments and->
	//stores them in the argv array and ->
	//checks if command should be run in the background or foreground ->
	//if command ends in & then background
	//otherwise bg is set to 0, indicating foreground
	//converts the command line into an array of stringss in argv
    if (argv[0] == NULL) //after parsing, check this to see if the input was an empty line
	return;   /* ignore empty lines */

    if (!builtin_command(argv)) { //if the command is NOT a built in command
	//so if its not a builtin, the code inside the if statement executes
	//so it basically says, execute if command is NOT A BUILTIN COMMAND
	//CODE EXECUTED INSIDE THE IF STATEMENT ONLY IF THE COMMAND IS NOT A BUILTIN
	if ((pid = Fork()) == 0) {   /* child runs user job */ //so new process created and->
	//as child gets the 0, runs the if statement
		//so create a new process to run the user specified command
	    if (execve(argv[0], argv, environ) < 0) {//execve is a system call used to execute a program
		//replaces the current rp
		//parameters of execve:
		//path to executable file (or name), array of argument strings, environment variables in the form of key=value

        int length2 = sizeof(vars) / sizeof(vars[0]);
        for (int i = 0; i < length2; i++){
            if (strcmp(vars[i], "PATH") == 0){
                tracker = strchr(vars[i], '=');
                vars[i] = tracker + 1;
                strcpy(newString, vars[i]);
            }
        }

        strcpy(string3, newString);
        strcpy(string3, argv[0]);
        if (execve(string3, argv, environ) < 0){
            printf("not found");
        }


		printf("%s: Command not found.\n", argv[0]);//showcasing that its not a builtin command
		exit(0);
	    }
	}

	/* parent waits for foreground job to terminate */
	if (!bg) {//bg determines if process runs in background 1 or foreground 0
	    int status;
	    if (waitpid(pid, &status, 0) < 0)//if error (waitpid returns negative value)
		unix_error("waitfg: waitpid error");
	}
	else
	    printf("%d %s", pid, cmdline);//return pid of ended processes
    }
    return;
}

/* if first arg is a builtin command, run it and return true */
int builtin_command(char **argv) 
{
    if (!strcmp(argv[0], "quit")) /* quit command */
	exit(0);  
    if (!strcmp(argv[0], "&"))    /* ignore singleton & */
	return 1;
    return 0;                     /* not a builtin command */
}
/* $end eval */

/*PLACE THE VARIABLE FUNCTION HERE*/
void variable_fun(const char *texto)//purpose: save a variable in the argv array
{
	//find an emtpy element in the array vars
	//call malloc and store the string there


	//ACTUAL INSTRUCTIONS:

	//check for space in the vars array, so do an if statement

	//int lengthVars = sizeof(vars)/sizeof(vars[0]);
	for (int p =0; p < 10; p++){
	if (vars[p]== NULL){

	int lenga = strlen(texto);
	//allocate memory for the new string
	ptr = (char *)malloc(sizeof(lenga + 1) * sizeof(char));
	//copy the string into the allocated memory
	strcpy(ptr, texto);
	//store the pointer to the allocated memory in the vars array
    vars[p++]= ptr;
		
	}
	printf("no more space");
	}

	
	//
	
	return;

}
/*END THE VARIABLE FUNCTION HERE*/

/*START OF SET SECTION*/
void print_set(char *array)
{
	
    /*
	int length = sizeof(array) / sizeof(array[0]);
	for (int i =0; i < length; i++)
	{
		printf("%s\n", array[i]);
	}
	return 0;
    */
   printf("%s\n", vars);
}

/*END OF SET SECTION*/

/* $begin parseline */
/* parseline - parse the command line and build the argv array */
int parseline(char *buf, char **argv) 
{
    char *delim;         /* points to first space delimiter */
    int argc;            /* number of args */
    int bg;              /* background job? */
	char *delim2;		 /* points to first equal sign */
	char *equalizer;		 /* points to the first set*/
	char *setDelim;		 /*mvv*/

    buf[strlen(buf)-1] = ' ';  /* replace trailing '\n' with space */
    while (*buf && (*buf == ' ')) /* ignore leading spaces */
	buf++;//if you encounter a leading space, move the pointer to the right

    /* build the argv list */
    argc = 0;
    while ((delim = strchr(buf, ' '))) {//with strchr set to look for spaces, it ->
	//will return a pointer to the first occurence of a space in the string ->
	//this pointer is assigned to delim
	argv[argc++] = buf;//assign argument to the array and increment the counter
	*delim = '\0';//substitute spaces with 0's. End of current argument. So each space ->
	//is substituted with that
	buf = delim + 1;//as we are skipping over spaces, buf is moved to the start of the next token
	while (*buf && (*buf == ' ')) /* ignore spaces */
	       buf++;
    }
    argv[argc] = NULL;//once done parsing, make the array NULL terminated
    
    if (argc == 0)  /* ignore blank line *///done if the command line was empty
	return 1;

	//do the variable stuff, after the ARGV list has been assembled
	 int length = sizeof(argv)/sizeof(argv[0]);
	 for (int f =0; f < length; f++){
		if ((delim2 = strstr(argv[f], "set")) != NULL){
			for (int g =0; g< length; g++){
				if ((equalizer = strstr(argv[g], "=")) != NULL){
					variable_fun(buf);
				}
			}
		}
	 }


	//set section:
	//tips: make sure you put conditions so that only set without arguments is taken
	//maybe do a condition for an argv array that will only have 2 elements, SET and NULL

	if (argc <= 2){
		for(int a =0; a < length ; a++){
			if ((setDelim = strstr(argv[a], "set")) != NULL){
				print_set(vars);
			}
		}
	}




    /* should the job run in the background? */
    if ((bg = (*argv[argc-1] == '&')) != 0)
	argv[--argc] = NULL;

    return bg;//this is a 1 or a 0 and it tells the system if the process is bg or fg
}
/* $end parseline */


