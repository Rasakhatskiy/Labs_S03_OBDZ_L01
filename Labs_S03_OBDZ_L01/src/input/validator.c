#include "validator.h"

unsigned int readUInt32()
{
    char input[BUFSIZ];

    // omg what have i done
    while (1)
    {
        printf("> ");
        if (!fgets(input, sizeof input, stdin))
        {
            // read error on input - panic
            exit(-1);
        }
        else
        {
            /**
                * Make sure the user didn't enter a string longer than the buffer
                * was sized to hold by looking for a newline character.  If a newline
                * isn't present, we reject the input and read from the stream until
                * we see a newline or get an error.
                */
            if (!strchr(input, '\n'))
            {
                // input too long
                while (
                    fgets(input, sizeof input, stdin) &&
                    !strchr(input, '\n'));
                printf("Input is too long. Try again please.\n");
            }
            else
            {
                char* chk;
                unsigned int result = (int)strtol(input, &chk, 10);

                /**
                    * chk points to the first character not converted.  If
                    * it's whitespace or 0, then the input string was a valid
                    * integer
                    */
                if (isspace(*chk) ||
                    *chk == 0)
                {
                    return result;
                }
                else
                {
                    printf("It is not a valid integer input. Try again please.\n");
                }
            }
        }
    }
}

char* readString(int maxLength)
{
    char* input = malloc(maxLength);

    // omg what have i done
    while (1)
    {
        printf("> ");
        if (!fgets(input, maxLength, stdin))
        {
            // read error on input - panic
            exit(-1);
        }
        else
        {
            /**
                * Make sure the user didn't enter a string longer than the buffer
                * was sized to hold by looking for a newline character.  If a newline
                * isn't present, we reject the input and read from the stream until
                * we see a newline or get an error.
                */
            if (!strchr(input, '\n'))
            {
                // input too long
                while (
                    fgets(input, maxLength, stdin) &&
                    !strchr(input, '\n'));
                printf("Input is too long. Try again please.\n");
            }
            else
            {
                return input;
            }
        }
    }
}
