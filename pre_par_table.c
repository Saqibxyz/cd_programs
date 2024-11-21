#include <stdio.h>
#include <string.h>
#define MAX 100
// Operator precedence relations
char precTable[4][4] = {
    {'>', '>', '<', '>'}, // +: > +, > *, < id, >
    {'>', '>', '<', '>'}, // *: > +, > *, < id, >
    {'<', '<', '=', '<'}, // id: < +, < *, = id, >
    {'<', '<', '<', '='}  // $: < +, < *, < id, = $
};
int isOperator(char c)
{
    return (c == '+' || c == '*' || c == '(' || c == ')' || c == '$');
}
int precedenceIndex(char c)
{
    switch (c)
    {
    case '+':
        return 0;
    case '*':
        return 1;
    case 'i':
        return 2; // assuming 'i' represents 'id'
    case '$':
        return 3;
    default:
        return -1;
    }
}
char getPrecedence(char stackTop, char input)
{
    return precTable[precedenceIndex(stackTop)][precedenceIndex(input)];
}
int validateString(char *input)
{
    char stack[MAX];
    int top = -1;
    int i = 0;
    stack[++top] = '$';
    while (input[i] != '\0')
    {
        if (input[i] == 'i' && input[i + 1] == 'd')
        {
            stack[++top] = 'i'; // Simplify 'id' to 'i'
            i += 2;             // Move past 'id'
        }
        else
        {
            switch (getPrecedence(stack[top], input[i]))
            {
            case '<':
                stack[++top] = input[i++];
                break;
            case '=':
                top--;
                i++;
                break;
            case '>':
                if (top == 0)
                    return 0; // Error: Invalid string
                top--;
                break;
            default:
                return 0; // Error: Invalid string
            }
        }
    }
    while (stack[top] != '$')
    {
        if (getPrecedence(stack[top - 1], stack[top]) == '>')
        {
            top--;
        }
        else
        {
            return 0; // Error: Invalid string
        }
    }
    return 1;
}
int main()
{
    char input[] = "id+id*id$";
    if (validateString(input))
    {
        printf("The string is valid.\n");
    }
    else
    {
        printf("The string is invalid.\n");
    }
    return 0;
}