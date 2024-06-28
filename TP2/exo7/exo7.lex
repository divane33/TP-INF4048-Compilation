%{
#include <stdio.h>
#include <stdlib.h>
%}

digit       [0-9]+
addop       \+
mulop       \*

%%
{digit}     { printf("<int:%s>", yytext); }
{addop}     { printf("<operateur:+>"); }
{mulop}     { printf("<operateur:*>"); }
.|\n        { /* Ignorer les autres caractères */ }
%%

int main(int argc, char *argv[]) {
    if (argc > 1) {
        FILE *file = fopen(argv[1], "r");
        if (!file) {
            perror("Error opening file");
            return 1;
        }
        yyin = file;
    }
    yylex();
    return 0;
}