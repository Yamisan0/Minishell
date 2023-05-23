#include "includes/minishell.h"

int main(void)
{
    char *prompt;

    while (42)
    {
        prompt = get_next_line(0);
        printf("%s\n", prompt);
    }
}