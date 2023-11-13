
/*
 * CS354: Shell project
 *
 * Template file.
 * You will need to add more code here to execute the command table.
 *
 * NOTE: You are responsible for fixing any bugs this code may have!
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pwd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <string.h>
#include <signal.h>
#include <string.h>
#include <fcntl.h>
#include <chrono>
#include <ctime>
#include <time.h>    
#include "command.h"
int next_dir = 0;
char *path_to_current_directory[128];
void Child_log(int num);


void add_dir_to_path(char *directory)
{
	if (directory == NULL)
		next_dir = 0;
	else if (strcmp(directory, "..") == 0)
		next_dir--;
	else
		path_to_current_directory[next_dir++] = strdup(directory);
}


int changeCurrentDirectory()
{
	int returnValue;
	char *path = Command::_currentSimpleCommand->_arguments[1];

	if (path)
		returnValue = chdir(path);
	else
		returnValue = chdir(getenv("HOME"));

	if (returnValue == 0 || !path)
		add_dir_to_path(path);

	Command::_currentCommand.clear();
	return returnValue;
}



SimpleCommand::SimpleCommand()
{
	// Creat available space for 5 arguments
	_numberOfAvailableArguments = 5;
	_numberOfArguments = 0;
	_arguments = (char **) malloc( _numberOfAvailableArguments * sizeof( char * ) );
}

void
SimpleCommand::insertArgument( char * argument )
{
	if ( _numberOfAvailableArguments == _numberOfArguments  + 1 ) {
		// Double the available space
		_numberOfAvailableArguments *= 2;
		_arguments = (char **) realloc( _arguments,
				  _numberOfAvailableArguments * sizeof( char * ) );
	}
	
	_arguments[ _numberOfArguments ] = argument;

	// Add NULL argument at the end
	_arguments[ _numberOfArguments + 1] = NULL;
	
	_numberOfArguments++;
}

Command::Command()
{
	// Create available space for one simple command
	_numberOfAvailableSimpleCommands = 1;
	_simpleCommands = (SimpleCommand **)
		malloc( _numberOfSimpleCommands * sizeof( SimpleCommand * ) );

	_numberOfSimpleCommands = 0;
	_outFile = 0;
	_inputFile = 0;
	_errFile = 0;
	_background = 0;
	_append = 0;
}

void
Command::insertSimpleCommand( SimpleCommand * simpleCommand )
{
	if ( _numberOfAvailableSimpleCommands == _numberOfSimpleCommands ) {
		_numberOfAvailableSimpleCommands *= 2;
		_simpleCommands = (SimpleCommand **) realloc( _simpleCommands,
			 _numberOfAvailableSimpleCommands * sizeof( SimpleCommand * ) );
	}
	
	_simpleCommands[ _numberOfSimpleCommands ] = simpleCommand;
	_numberOfSimpleCommands++;
}

void
Command:: clear()
{
	for ( int i = 0; i < _numberOfSimpleCommands; i++ ) {
		for ( int j = 0; j < _simpleCommands[ i ]->_numberOfArguments; j ++ ) {
			free ( _simpleCommands[ i ]->_arguments[ j ] );
		}
		
		free ( _simpleCommands[ i ]->_arguments );
		free ( _simpleCommands[ i ] );
	}

	if ( _outFile ) {
		free( _outFile );
	}

	if ( _inputFile ) {
		free( _inputFile );
	}

	if ( _errFile ) {
		free( _errFile );
	}

	_numberOfSimpleCommands = 0;
	_outFile = 0;
	_inputFile = 0;
	_errFile = 0;
	_background = 0;
	_append = 0;
}

void
Command::print()
{
	printf("\n\n");
	printf("              COMMAND TABLE                \n");
	printf("\n");
	printf("  #   Simple Commands\n");
	printf("  --- ----------------------------------------------------------\n");
	
	for ( int i = 0; i < _numberOfSimpleCommands; i++ ) {
		printf("  %-3d ", i );
		for ( int j = 0; j < _simpleCommands[i]->_numberOfArguments; j++ ) {
			printf("\"%s\" \t", _simpleCommands[i]->_arguments[ j ] );
		}
	}

	printf( "\n\n" );
	printf( "  Output       Input        Error        Background\n" );
	printf( "  ------------ ------------ ------------ ------------\n" );
	printf( "  %-12s %-12s %-12s %-12s\n", _outFile?_outFile:"default",
		_inputFile?_inputFile:"default", _errFile?_errFile:"default",
		_background?"YES":"NO");
	printf( "\n\n" );
	
}

void
Command::ChangeDir(char* dir)
{
	char current[1024];
	int dirCheck = chdir(dir);
	printf("current directory is %s\n",getcwd(current,1024));
	if(dir == NULL){	
		chdir(getenv("HOME"));
	} else if (dirCheck < 0){
		perror("CD ERROR");
	}else{ 
		chdir(dir);
	}
	printf("new directory is %s\n",getcwd(current,100));				
}						    	     

void
Command::execute()
{
	
	// Don't do anything if there are no simple commands
	
	if ( _numberOfSimpleCommands == 0 ) {
		prompt();
		return;
	}

	
	// Print contents of Command data structure
	print();
	// Add execution here
	
	int defaultin = dup( 0 );
	int defaultout = dup( 1 );
	int defaulterr = dup( 2 );
	int outfd ;
	int errfd ;
	int inpfd ;
	int inputstream;
	int outputstream;

	if(_inputFile)
		{
			inpfd = open(_inputFile, O_RDONLY, 0777);
		}
		else
		{
			inpfd = dup(inputstream);
		}
	for (int i=0 ; i < _numberOfSimpleCommands; i++)
	{

		if(!strcmp(_simpleCommands[i]->_arguments[0],"exit"))
		{
			printf("\n Exiting Program Peacefully\n");
			exit(0);
		}

		 if(!strcmp( _simpleCommands[0]->_arguments[0], "cd" )){
			printf("\n");
			if (changeCurrentDirectory() == -1)
				printf("\033[31mError occurred. Make sure the directory you entered is valid\033[0m\n");
			continue;
			//ChangeDir(_simpleCommands[0]->_arguments[0]);
			
	    	// int ret;
	   		// if(_simpleCommands[0]->_numberOfArguments == 1){
	      	// 	ret = chdir(getenv("HOME"));

	    	// }else{
	      	// 	ret = chdir(_simpleCommands[0]->_arguments[1]);
			// }if(ret < 0)
	      	// 	printf("No existing directory \n");
	    	// 	clear();
	    	// 	prompt();
	    	// return;
	  }
// _________________________________________________________________________________________________
	
		dup2(inpfd,0);
		close(inpfd);
		
		if (i != _numberOfSimpleCommands-1)
		{
			int fdpipe[2];
			pipe(fdpipe);
			outfd = fdpipe[1];
			inpfd = fdpipe[0];
		}
		else
		{
			if(_outFile)
			{
					
				if (_append)
				{
					outfd = open(_outFile, O_WRONLY | O_CREAT | O_APPEND, 0777);
				}
				else
				{
					outfd = open(_outFile, O_WRONLY | O_CREAT | O_TRUNC, 0777);
				}
				if ( outfd < 0 ) 
				{
				perror( "ERROR IN OUTPUT FILE" );
				exit( 2 );
				}
				
			}
			else if(_errFile)
			{			
				if (_append)
					{
						errfd = open(_errFile, O_WRONLY | O_CREAT | O_APPEND, 0777);
					}
					else
					{
						errfd = open(_errFile, O_WRONLY | O_CREAT | O_TRUNC, 0777);
					}
				if ( errfd < 0 ) 
					{
					perror( "ERROR in file");
					exit( 2 );
					}
				dup2(errfd,2);
				close(errfd);
			}
			else
			{
				outfd = dup(defaultout);
				close(defaultout);
			}
		}
		
		dup2(outfd,1);
		close(outfd);
		
		pid_t pid = fork();
		
	if (pid == -1 ) 
		{
		perror( "Child was not forked\n");
		exit( 2 );
		}

	if (pid == 0) 
		{	
			
			execvp(_simpleCommands[i]->_arguments[0],_simpleCommands[i]->_arguments);
		}
	else
		{	
			signal(SIGCHLD, Child_log);
			if (!_background)
			{
			waitpid(pid, NULL,  WUNTRACED | WCONTINUED);
			}
			
		}
	}
	dup2( defaultin, 0 );
	dup2( defaultout, 1 );
	dup2( defaulterr, 2 );
	close( defaultin );
	close( defaultout );
	close( defaulterr );
	
	
	
	// For every simple command fork a new process
	// Setup i/o redirection
	// and call execvp

	// Clear to prepare for next command
	clear();
	
	// Print new prompt
	prompt();
}

// Shell implementation


void
Command::prompt()
{
	printf("Karasna-shell>");
	fflush(stdout);
}

Command Command::_currentCommand;
SimpleCommand * Command::_currentSimpleCommand;

int yyparse(void);




int 
main()
{
	signal(SIGINT, SIG_IGN);
	Command::_currentCommand.prompt();
	yyparse();
	return 0;
}

void Child_log(int num)
{
	//printf("child terminated\n");
	
	FILE* log = fopen("children_log.txt","a");
	time_t T = time(NULL);
	fprintf(log," child terminated at: %s\n",ctime(&T));
	fclose(log);
	
}
