#include "includes/minishell.h"

int main(void)
{
    char *prompt;

    while (42)
    {
        prompt = readline("minishell>");
    }
}