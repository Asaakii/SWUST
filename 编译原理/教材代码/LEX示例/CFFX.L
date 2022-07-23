%{
#include <stdio.h>
#ifndef FALSE
#define FALSE 0
#endif
#ifndef TRUE
#define TRUE 1
#endif
%}

digit       [0-9]
number      {digit}+
letter      [a-zA-Z]
identifier  {letter}+
newline     [\n]
whitespace  [ \t]+
%%
"if"           {fprintf(yyout,"%s  %s\n",  yytext,yytext);}
"else"         {fprintf(yyout,"%s  %s\n",  yytext,yytext);}
"for"          {fprintf(yyout,"%s  %s\n",  yytext,yytext);}
"while"        {fprintf(yyout,"%s  %s\n",  yytext,yytext);}
"do"           {fprintf(yyout,"%s  %s\n",  yytext,yytext);}
"int"          {fprintf(yyout,"%s  %s\n",  yytext,yytext);}
"read"         {fprintf(yyout,"%s  %s\n",  yytext,yytext);}
"write"       {fprintf(yyout,"%s,  %s\n", yytext,yytext);}
"="   {fprintf(yyout,"%s  %s\n", yytext,yytext);}
"+"   {fprintf(yyout,"%s  %s\n",  yytext,yytext);}
"-"   {fprintf(yyout,"%s  %s\n",  yytext,yytext);}
"*"   {fprintf(yyout,"%s  %s\n",  yytext,yytext);}
"/"   {fprintf(yyout,"%s  %s\n",  yytext,yytext);}
"<"   {fprintf(yyout,"%s  %s\n",  yytext,yytext);}
">"   {fprintf(yyout,"%s  %s\n",  yytext,yytext);}
"("   {fprintf(yyout,"%s  %s\n",  yytext,yytext);}
")"   {fprintf(yyout,"%s  %s\n",  yytext,yytext);}
"["   {fprintf(yyout,"%s  %s\n",  yytext,yytext);}
"]"   {fprintf(yyout,"%s  %s\n",  yytext,yytext);}
"{"   {fprintf(yyout,"%s  %s\n",  yytext,yytext);}
"}"   {fprintf(yyout,"%s  %s\n",  yytext,yytext);}
";"   {fprintf(yyout,"%s  %s\n",  yytext,yytext);}
":"   {fprintf(yyout,"%s  %s\n",  yytext,yytext);}
"'"   {fprintf(yyout,"%s  %s\n",  yytext,yytext);}
"\""   {fprintf(yyout,"%s  %s\n",  yytext,yytext);}
","   {fprintf(yyout,"%s  %s\n",  yytext,yytext);}
"=="   {fprintf(yyout,"%s  %s\n",  yytext,yytext);}
">="   {fprintf(yyout,"%s  %s\n",  yytext,yytext);}
"<="   {fprintf(yyout,"%s  %s\n",  yytext,yytext);}
"!="   {fprintf(yyout,"%s  %s\n",  yytext,yytext);}
{number}        {fprintf(yyout,"%s  %s\n",  "NUM",yytext);}
{identifier}    {fprintf(yyout,"%s  %s\n",  "ID",yytext);}
{whitespace}    {/* skip whitespace */}
"/*" { char c ;
       int done = FALSE;
       do
       { while ((c=input())!='*');
         while ( (c=input()) == '*');
         if (c == '/') done = TRUE;
       } while (!done);
      }
.      {fprintf(yyout,"%s,  %s\n",  "ERROR",yytext);}

%%
main( argc, argv )
     int argc;
     char **argv;
         {
         ++argv, --argc;  /* skip over program name */
         if ( argc > 0 )
                 yyin = fopen( argv[0], "r" );//yyin存放LEXYY的输入源程序
         else
                 yyin = stdin;
         ++argv, --argc;  /* skip over input name */
         if ( argc > 0 )
                 yyout = fopen( argv[0], "w" );//yyout存放LEXYY的输出程序
         else
                 yyout = stdout;
     
         yylex();
         }

     
int yywrap()
{ 
	return 1;
}