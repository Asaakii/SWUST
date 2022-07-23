#ifndef lint
static char yysccsid[] = "@(#)yaccpar	1.8 (Berkeley) 01/02/91\n\
 Modified 5/15/91 by J. Roskind to support graphic debugging modes";
#endif
#define YYBYACC 1
#define YYPREFIX "yy"
#line 2 "yac1.txt"
#include <stdio.h>
#include <ctype.h>

#line 12 "y_tab.c"
#define DIGIT 257
#define YYERRCODE 256
short yylhs[] = {                                        -1,
    0,    1,    1,    2,    2,    3,    3,
};
short yylen[] = {                                         2,
    1,    3,    1,    3,    1,    3,    1,
};
short yydefred[] = {                                      0,
    7,    0,    0,    0,    0,    5,    0,    0,    0,    6,
    0,    4,
};
short yydgoto[] = {                                       3,
    4,    5,    6,
};
short yysindex[] = {                                    -40,
    0,  -40,    0,  -39,  -36,    0,  -38,  -40,  -40,    0,
  -36,    0,
};
short yyrindex[] = {                                      0,
    0,    0,    0,    7,    1,    0,    0,    0,    0,    0,
    2,    0,
};
short yygindex[] = {                                      0,
    6,    3,    4,
};
#define YYTABLESIZE 217
short yytable[] = {                                       2,
    3,    2,   10,    8,    8,    9,    1,    7,    0,    0,
   11,    0,   12,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    3,    2,    3,    2,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    1,
};
short yycheck[] = {                                      40,
    0,    0,   41,   43,   43,   42,    0,    2,   -1,   -1,
    8,   -1,    9,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   41,   41,   43,   43,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  257,
};
#define YYFINAL 3
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 257
#if YYDEBUG
char *yyname[] = {
"end-of-file",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,"'('","')'","'*'","'+'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"DIGIT",
};
char *yyrule[] = {
"$accept : line",
"line : expr",
"expr : expr '+' term",
"expr : term",
"term : term '*' factor",
"term : factor",
"factor : '(' expr ')'",
"factor : DIGIT",
};
#endif
#ifndef YYSTYPE
typedef int YYSTYPE;
#endif
#define yyclearin (yychar=(-1))
#define yyerrok (yyerrflag=0)
#ifdef YYSTACKSIZE
#ifndef YYMAXDEPTH
#define YYMAXDEPTH YYSTACKSIZE
#endif
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 600
#define YYMAXDEPTH 600
#endif
#endif
int yydebug;
int yynerrs;
int yyerrflag;
int yychar;
short *yyssp;
YYSTYPE *yyvsp;
YYSTYPE yyval;
YYSTYPE yylval;
short yyss[YYSTACKSIZE];
YYSTYPE yyvs[YYSTACKSIZE];
#define yystacksize YYSTACKSIZE
#line 22 "yac1.txt"
main()
{
printf("·ÖÎö½á¹û%d\n", yyparse());
}
int yylex(void){
int c;
while ((c=getchar())==' ');
if (isdigit(c)){
     ungetc(c,stdin);
     scanf("%d",&yylval);
     return(DIGIT);
     }

if (c=='\n') return 0;
return c;
}
void yyerror(char *s)
{fprintf(stderr,"%s\n",s);
}
#line 162 "y_tab.c"
#define YYABORT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR goto yyerrlab
#if YYDEBUG
#ifndef YYDEBUG_LEXER_TEXT /* pointer to the text isolated by the lexer*/
#define YYDEBUG_LEXER_TEXT "YYDEBUG_LEXER_TEXT not defined"
#endif
#ifndef YYDEBUG_INDENT_STRING
#define YYDEBUG_INDENT_STRING  "|       "
#endif
#ifndef YYDEBUG_REDUCE_STRING
#define YYDEBUG_REDUCE_STRING  "+-------"
#endif
#ifndef YYDEBUG_INDENT
YYDEBUG_INDENT(yyindent)
int yyindent;
{
    while(yyindent-- > 0)
        printf("%s", YYDEBUG_INDENT_STRING);
}
#endif /* YYDEBUG_INDENT */
#ifndef YYDEBUG_REDUCE
YYDEBUG_REDUCE(yynew_state, yyrule_num, yyrule_string, yynew_indent, 
yyrhs_count)
int yynew_state;
int yyrule_num;
char * yyrule_string;
int yynew_indent;
int yyrhs_count;
{
    if (1 < yyrhs_count)
    {  /* draw the graphics for the reduction */
        YYDEBUG_INDENT(yynew_indent);
        while(1 < yyrhs_count--)
            printf("%s", YYDEBUG_REDUCE_STRING);
        putchar('+'); /* left rotated L would look nice */
        putchar('\n');
        YYDEBUG_INDENT(yynew_indent);
        putchar('|'); /* down arrow would look nice */
        putchar('\n');
    }
    YYDEBUG_INDENT(yynew_indent);
    /* Only print the resulting token name */
    while (*yyrule_string && ' ' != *yyrule_string)
        putchar(*yyrule_string++);
    putchar('\n');
}
#endif /* YYDEBUG_REDUCE */
#ifndef YYDEBUG_SHIFT_LEXEME
YYDEBUG_SHIFT_LEXEME(yyold_state, yynew_state, yytoken_string, yynew_indent)
int yyold_state;
int yynew_state;
char * yytoken_string;
int yynew_indent;
{
    YYDEBUG_INDENT(yynew_indent);
    printf("%s <-- `%s'\n", yytoken_string, YYDEBUG_LEXER_TEXT);
}
#endif /*  YYDEBUG_SHIFT_LEXEME */
#ifndef YYDEBUG_LOOK_AHEAD
YYDEBUG_LOOK_AHEAD(yynew_state, yytoken_num, yytoken_string, yyindent)
int yynew_state;
int yytoken_num;
char * yytoken_string;
int yyindent;
{
    YYDEBUG_INDENT(yyindent);
    printf("          .... look ahead at %s   `%s'\n",
           yytoken_string,
           (0 == yytoken_num)? "\0": YYDEBUG_LEXER_TEXT);
}
#endif /* YYDEBUG_LOOK_AHEAD */
#ifndef YYDEBUG_DISCARD_STATE
YYDEBUG_DISCARD_STATE(yynew_state, yyindent)
int yynew_state;
int yyindent;
{
    if (0 < yyindent)
    {  /* draw the graphics for the reduction */
        YYDEBUG_INDENT(yyindent-1);
        printf("%s", YYDEBUG_REDUCE_STRING);
        putchar('+'); /* left rotated L would look nice */
        printf("  discarding state\n");
        YYDEBUG_INDENT(yyindent-1);
        putchar('|'); /* down arrow would look nice */
        putchar('\n');
    }
    else
    {
        if (0 == yyindent)
            printf("discarding state\n");
        else
            printf("no more states to discard: parser will abort\n");
    }
}
#endif /* YYDEBUG_DISCARD_STATE */
#ifndef YYDEBUG_DISCARD_TOKEN
YYDEBUG_DISCARD_TOKEN(yynew_state, yytoken_num, yytoken_string, yyindent)
int yynew_state;
int yytoken_num;
char * yytoken_string;
int yyindent;
{
    YYDEBUG_INDENT(yyindent);
    printf("discarding token %s\n", yytoken_string);
}
#endif /* YYDEBUG_DISCARD_TOKEN */
#ifndef YYDEBUG_SHIFT_ERROR_LEXEME
YYDEBUG_SHIFT_ERROR_LEXEME(yyold_state, yynew_state, yyindent)
int yyold_state;
int yynew_state;
int yyindent;
{
    YYDEBUG_INDENT(yyindent);
    printf("error\n");
}
#endif /* YYDEBUG_SHIFT_ERROR_LEXEME */
#endif /* YYDEBUG */
int
yyparse()
{
    register int yym, yyn, yystate;
#if YYDEBUG
    register char *yys;
    extern char *getenv();

    if (yys = getenv("YYDEBUG"))
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
#endif

    yynerrs = 0;
    yyerrflag = 0;
    yychar = (-1);

    yyssp = yyss;
    yyvsp = yyvs;
    *yyssp = yystate = 0;

yyloop:
    if (yyn = yydefred[yystate]) goto yyreduce;
    if (yychar < 0)
    {
        if ((yychar = yylex()) < 0) yychar = 0;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            if (5 > yydebug)
                printf("yydebug: state %d, reading %d (%s)\n", yystate,
                        yychar, yys);
            else
                YYDEBUG_LOOK_AHEAD(yystate, yychar, yys, yyssp-yyss);
        }
#endif
    }
    if ((yyn = yysindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
#if YYDEBUG
        if (yydebug)
            if (5 > yydebug)
                printf("yydebug: state %d, shifting to state %d\n",
                        yystate, yytable[yyn]);
            else
                YYDEBUG_SHIFT_LEXEME(yystate, yytable[yyn], yys, yyssp-yyss);
#endif
        if (yyssp >= yyss + yystacksize - 1)
        {
            goto yyoverflow;
        }
        *++yyssp = yystate = yytable[yyn];
        *++yyvsp = yylval;
        yychar = (-1);
        if (yyerrflag > 0)  --yyerrflag;
        goto yyloop;
    }
    if ((yyn = yyrindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
        yyn = yytable[yyn];
        goto yyreduce;
    }
    if (yyerrflag) goto yyinrecovery;
#ifdef lint
    goto yynewerror;
#endif
yynewerror:
    yyerror("syntax error");
#ifdef lint
    goto yyerrlab;
#endif
yyerrlab:
    ++yynerrs;
yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            if ((yyn = yysindex[*yyssp]) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    if (5 > yydebug)
                        printf("yydebug: state %d, error recovery shifting\
 to state %d\n", *yyssp, yytable[yyn]);
                    else
                        YYDEBUG_SHIFT_ERROR_LEXEME(*yyssp, yytable[yyn], yyssp-yyss);
#endif
                if (yyssp >= yyss + yystacksize - 1)
                {
                    goto yyoverflow;
                }
                *++yyssp = yystate = yytable[yyn];
                *++yyvsp = yylval;
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    if (5 > yydebug)
                        printf("yydebug: error recovery discarding state %d\n",
                            *yyssp);
                    else
                        YYDEBUG_DISCARD_STATE(*yyssp, yyssp-yyss-1);
#endif
                if (yyssp <= yyss) goto yyabort;
                --yyssp;
                --yyvsp;
            }
        }
    }
    else
    {
        if (yychar == 0) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            if (5 > yydebug)
                printf("yydebug: state %d, error recovery discards token %d (%s)\n",
                    yystate, yychar, yys);
            else 
                YYDEBUG_DISCARD_TOKEN(yystate, yychar, yys, yyssp-yyss);
        }
#endif
        yychar = (-1);
        goto yyloop;
    }
yyreduce:
    yym = yylen[yyn];
    yyval = yyvsp[1-yym];
#if YYDEBUG
    if (yydebug)
        if (5 > yydebug)
            printf("yydebug: state %d, reducing by rule %d (%s)\n",
                    yystate, yyn, yyrule[yyn]);
        else
            YYDEBUG_REDUCE(yystate, yyn, yyrule[yyn], yyssp-yyss-yym, yym);
#endif
    switch (yyn)
    {
case 1:
#line 10 "yac1.txt"
{printf("%d\n",yyvsp[0]);}
break;
case 2:
#line 12 "yac1.txt"
{yyval=yyvsp[-2]+yyvsp[0];}
break;
case 3:
#line 13 "yac1.txt"
{yyval=yyvsp[0];}
break;
case 4:
#line 15 "yac1.txt"
{yyval=yyvsp[-2]*yyvsp[0];}
break;
case 5:
#line 16 "yac1.txt"
{yyval=yyvsp[0];}
break;
case 6:
#line 18 "yac1.txt"
{yyval=yyvsp[-1];}
break;
case 7:
#line 19 "yac1.txt"
{yyval=yyvsp[0];}
break;
#line 463 "y_tab.c"
    }
    yyssp -= yym;
    yystate = *yyssp;
    yyvsp -= yym;
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug && 5 > yydebug)
            printf("yydebug: after reduction, shifting from state 0 to\
 state %d\n", YYFINAL);
#endif
        yystate = YYFINAL;
        *++yyssp = YYFINAL;
        *++yyvsp = yyval;
        if (yychar < 0)
        {
            if ((yychar = yylex()) < 0) yychar = 0;
#if YYDEBUG
            if (yydebug)
            {
                yys = 0;
                if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
                if (!yys) yys = "illegal-symbol";
                if (5 > yydebug)
                    printf("yydebug: state %d, reading %d (%s)\n",
                        YYFINAL, yychar, yys);
                else
                    YYDEBUG_LOOK_AHEAD(YYFINAL, yychar, yys, yyssp-yyss);
            }
#endif
        }
        if (yychar == 0) goto yyaccept;
        goto yyloop;
    }
    if ((yyn = yygindex[yym]) && (yyn += yystate) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yystate)
        yystate = yytable[yyn];
    else
        yystate = yydgoto[yym];
#if YYDEBUG
    if (yydebug && 5 > yydebug)
        printf("yydebug: after reduction, shifting from state %d \
to state %d\n", *yyssp, yystate);
#endif
    if (yyssp >= yyss + yystacksize - 1)
    {
        goto yyoverflow;
    }
    *++yyssp = yystate;
    *++yyvsp = yyval;
    goto yyloop;
yyoverflow:
    yyerror("yacc stack overflow");
yyabort:
    return (1);
yyaccept:
    return (0);
}
