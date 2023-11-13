
/*
 *
 * CS-413 Spring 98
 * shell.l: lexical analyzer for shell
 * You have to extend it.
 *
 */

%{

#include <string.h>
#include "y.tab.h"

%}

%%

\n 	{
		return NEWLINE;
	}

[ \t] 	{
		/* Discard spaces and tabs */
     	}	

">" 	{
		return GREAT;
	}

"|"		{
		return PIPE;
	}

">>"	{
		return APPEND;
	}
	
"<"		{
		return SMALL;
	}

">&"	{
		return ERROR;
	}

">>&"	{
		return APPEND_ERROR;
	}

"&"		{
		return AMPERSAND;
	}

.	{
		/* Invalid character in input */
		return NOTOKEN;
	}

[^\|\>\<\& \t\n][^\|\>\<\& \t\n]*  {
		/* Assume that file names have only alpha chars */
		yylval.string_val = strdup(yytext);
		return WORD;
	}


%%
//[^ \t\n][^ \t\n]*  
