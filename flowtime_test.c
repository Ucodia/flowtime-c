#include "flowtime.h"
#include <stdio.h>
#include <stdbool.h>

bool compareTimes(Time actual, Time expected)
{
    return actual.hour == expected.hour && actual.minute == expected.minute && actual.second == expected.second;
}

void test_fromDate()
{
    FILE *file = fopen("test_data.csv", "r");
    if (!file)
    {
        perror("Failed to open test_data.csv");
        return;
    }

    char dateStr[20];
    Time expected;
    int testCaseCount = 0;
    char line[100]; // Assuming a line won't exceed 100 characters

    while (fgets(line, sizeof(line), file))
    {
        if (sscanf(line, "%19s,%d:%d:%d", dateStr, &expected.hour, &expected.minute, &expected.second) == 4)
        {
            struct tm date;
            strptime(dateStr, "%Y-%m-%dT%H:%M:%S", &date);
            Time actual = fromDate(date);

            if (!compareTimes(actual, expected))
            {
                printf("❌ Test failed for date %s. Expected time: %d:%d:%d but got time: %d:%d:%d\n",
                       dateStr, expected.hour, expected.minute, expected.second, actual.hour, actual.minute, actual.second);
                fclose(file);
                return;
            }

            testCaseCount++;
        }
    }

    fclose(file);
    printf("✅ All %d tests passed\n", testCaseCount);
}

int main()
{
    test_fromDate();
    return 0;
}
