%option noyywrap

%{
#include <stdio.h>
int token_count = 0;  // Declare token_count in the C code section
%}

%%

[a-zA-Z0-9]+  { printf("Token: %s\n", yytext); token_count++; }
[=;*+-]      { printf("Token: %s\n", yytext); token_count++; }
\n            { /* ignore newlines */ }
.             { /* ignore other characters */ }

%%

int main() {
    yylex();  // Process all tokens
    printf("Number of tokens: %d\n", token_count);  // Print the total count
    return 0;
}
