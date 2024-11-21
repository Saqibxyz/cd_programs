// Program 9: Write a program to implement recursive
// descent parsing.
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
char input[100];
int i = 0; // Initialize index to 0
bool E();
bool EP();
bool T();
bool TP();
bool F();
int main()
{
    printf("\nRecursive descent parsing for the following grammar\n");
    printf("\nE->TE'\nE'->+TE'/@\nT->FT'\nT'->*FT'/@\nF->(E)/ID\n");
    printf("\nEnter the string to be checked: ");
    // Use fgets instead of gets for safer input
    fgets(input, sizeof(input), stdin);
    // Remove newline character from input if present
    input[strcspn(input, "\n")] = 0;
    if (E())
    {
        if (input[i] == '\0')
        {
            printf("\nString is accepted\n");
        }
        else
        {
            printf("\nString is not accepted\n");
        }
    }
    else
    {
        printf("\nString not accepted\n");
    }
    return 0;
}
bool E()
{
    if (T())
    {
        if (EP())
            return true;
        else
            return false;
    }
    else
    {
        return false;
    }
}
bool EP()
{
    if (input[i] == '+')
    {
        i++;
        if (T())
        {
            if (EP())
                return true;
            else
                return false;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return true; // ε production
    }
}
bool T()
{
    if (F())
    {
        if (TP())
            return true;
        else
            return false;
    }
    else
    {
        return false;
    }
}
bool TP()
{
    if (input[i] == '*')
    {
        i++;
        if (F())
        {
            if (TP())
                return true;
            else
                return false;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return true; // ε production
    }
}
bool F()
{
    if (input[i] == '(')
    {
        i++;
        if (E())
        {
            if (input[i] == ')')
            {
                i++;
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }
    else if ((input[i] >= 'a' && input[i] <= 'z') || (input[i] >= 'A' &&
                                                      input[i] <= 'Z'))
    {
        i++;
        return true;
    }
    else
    {
        return false;
    }
}