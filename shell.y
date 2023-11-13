
/*
 * CS-413 Spring 98
 * shell.y: parser for shell
 *
 * This parser compiles the following grammar:
 *
 *	cmd [arg]* [> filename]
 *
 * you must extend it to understand the complete shell grammar
 *
 */

%token	<string_val> WORD

%token 	NOTOKEN GREAT NEWLINE PIPE APPEND SMALL ERROR APPEND_ERROR AMPERSAND

%union	{
		char   *string_val;
	}

%{
extern "C" 
{
	int yylex();
	void yyerror (char const *s);
}
#define yylex yylex
#include <stdio.h>
#include "command.h"
%}

%%

goal:	
	commands
	;

commands: 
	command
	| commands command 
	;

command: 
		piped_command
		| simple_command
        ;


piped_command:
	PIPE simple_command
	;


simple_command:	
	command_and_args iomodifier_opt NEWLINE {
		printf("   Yacc: Execute command\n");
		Command::_currentCommand.execute();
	}
	| command_and_args iomodifier_opt
	| NEWLINE 
	| error NEWLINE { yyerrok; }
	;


command_and_args:
	command_word arg_list {
		Command::_currentCommand.
			insertSimpleCommand( Command::_currentSimpleCommand );
	}
	;

arg_list:
	arg_list argument
	| /* can be empty */
	;

argument:
	WORD {
               printf("   Yacc: insert argument \"%s\"\n", $1);

	       Command::_currentSimpleCommand->insertArgument( $1 );\
	}
	;

command_word:
	WORD {
               printf("   Yacc: insert command \"%s\"\n", $1);
	       
	       Command::_currentSimpleCommand = new SimpleCommand();
	       Command::_currentSimpleCommand->insertArgument( $1 );
	}
	;

iomodifier_opt:
	GREAT WORD {
		printf("   Yacc: insert output \"%s\"\n", $2);
		Command::_currentCommand._outFile = $2;
	}
	| APPEND WORD {
		printf("   Yacc: Append output \"%s\"\n", $2);
		Command::_currentCommand._outFile = $2;
		Command::_currentCommand._append = 1;
	}
	| SMALL WORD {
		printf("   Yacc: Read input \"%s\"\n", $2);
		Command::_currentCommand._inputFile = $2;
	}
	| ERROR WORD {
		printf("   Yacc: insert error \"%s\"\n", $2);
		Command::_currentCommand._errFile = $2;
	}
	| APPEND_ERROR WORD {
		printf("   Yacc: Append error \"%s\"\n", $2);
		Command::_currentCommand._errFile = $2;
		Command::_currentCommand._append = 1;
	}
	| GREAT WORD SMALL WORD {
		printf("   Yacc: insert output \"%s\"\n", $2);
		printf("   Yacc: Read input \"%s\"\n", $4);
		Command::_currentCommand._outFile = $2;
		Command::_currentCommand._inputFile = $4;
	}
	| SMALL WORD GREAT WORD {
		printf("   Yacc: insert output \"%s\"\n", $4);
		printf("   Yacc: Read input \"%s\"\n", $2);
		Command::_currentCommand._outFile = $4;
		Command::_currentCommand._inputFile = $2;
	}
	| AMPERSAND {
		printf("   Yacc: Background Process");
		Command::_currentCommand._background = 1;
	}
	|
	 /* can be empty */ 
	;

%%

void
yyerror(const char * s)
{
	fprintf(stderr,"%s", s);
}

#if 0
main()
{
	yyparse();
}
#endif
