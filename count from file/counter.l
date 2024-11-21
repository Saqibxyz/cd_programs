%{
#include <stdio.h>
#include <stdlib.h>

int keyword_count = 0;
int identifier_count = 0;
int special_character_count = 0;
%}

%% 
const | 
final | 
break | 
else | 
while | 
continue |
for | 
if | 
do | 
switch               { 
    printf("%s is a keyword\n", yytext); 
    keyword_count++; 
}
[ \t\n]+            ; // Ignore whitespace
[a-zA-Z_][a-zA-Z0-9_]* { 
    printf("%s is an identifier\n", yytext); 
    identifier_count++; 
}
"{"                  { 
    printf("%s is a special character\n", yytext); 
    special_character_count++; 
}
"}"                  { 
    printf("%s is a special character\n", yytext); 
    special_character_count++; 
}
"("                  { 
    printf("%s is a special character\n", yytext); 
    special_character_count++; 
}
")"                  { 
    printf("%s is a special character\n", yytext); 
    special_character_count++; 
}
"["                  { 
    printf("%s is a special character\n", yytext); 
    special_character_count++; 
}
"]"                  { 
    printf("%s is a special character\n", yytext); 
    special_character_count++; 
}
";"                  { 
    printf("%s is a special character\n", yytext); 
    special_character_count++; 
}
","                  { 
    printf("%s is a special character\n", yytext); 
    special_character_count++; 
}
"="                  { 
    printf("%s is a special character\n", yytext); 
    special_character_count++; 
}
"=="                 { 
    printf("%s is a special character\n", yytext); 
    special_character_count++; 
}
"!="                 { 
    printf("%s is a special character\n", yytext); 
    special_character_count++; 
}
"+"                  { 
    printf("%s is a special character\n", yytext); 
    special_character_count++; 
}
"-"                  { 
    printf("%s is a special character\n", yytext); 
    special_character_count++; 
}
"*"                  { 
    printf("%s is a special character\n", yytext); 
    special_character_count++; 
}
"/"                  { 
    printf("%s is a special character\n", yytext); 
    special_character_count++; 
}
"%"                  { 
    printf("%s is a special character\n", yytext); 
    special_character_count++; 
}
"."                  { 
    printf("%s is not an identifier\n", yytext); 
} 
.                    { 
    printf("%s is not an identifier\n", yytext); 
} // catch-all for any other character
%% 

int yywrap() {
    return 1; // Indicates that there are no more input files
}

int main() {
    FILE *file;
    file = fopen("sample.txt", "r"); // Open the file for reading
    if (!file) {
        perror("Failed to open file");
        return EXIT_FAILURE;
    }

    yyin = file; // Set the input stream for the lexer

    yylex(); // Start lexing

    fclose(file); // Close the file

    // Print the token counts
    printf("\nTotal keywords: %d\n", keyword_count);
    printf("Total identifiers: %d\n", identifier_count);
    printf("Total special characters: %d\n", special_character_count);

    return 0;
}
