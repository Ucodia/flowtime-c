#include "flowtime.h"
#include <stdio.h>
#include <unistd.h>

int main()
{
    while (1)
    {
        time_t t;
        struct tm date;
        time(&t);
        date = *localtime(&t);

        Time result = fromDate(date);

        printf("\r%02d:%02d:%02d", result.hour, result.minute, result.second);
        fflush(stdout);

        sleep(1);
    }
    return 0;
}
