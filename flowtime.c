#include "flowtime.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

double nextLcgValue(Lcg *lcg)
{
    lcg->z = (lcg->multiplier * lcg->z + lcg->increment) % lcg->modulus;
    return (double)lcg->z / lcg->modulus;
}

Lcg createLcg(long long seed, long long modulus, long long multiplier, long long increment)
{
    Lcg lcg = {seed, modulus, multiplier, increment};
    return lcg;
}

void getSeedsFromDate(struct tm date, long long *minuteSeed, long long *hourSeed)
{
    char buffer[20];
    sprintf(buffer, "%04d%02d%02d%02d", date.tm_year + 1900, date.tm_mon + 1, date.tm_mday, date.tm_hour);
    *minuteSeed = atoll(buffer);

    sprintf(buffer, "%04d%02d%02d", date.tm_year + 1900, date.tm_mon + 1, date.tm_mday);
    *hourSeed = atoll(buffer);
}

void getSequenceFromLcg(Lcg lcg, int length, int *sequence)
{
    double *values = (double *)malloc(length * sizeof(double));
    for (int i = 0; i < length; i++)
    {
        values[i] = nextLcgValue(&lcg);
    }

    for (int i = 0; i < length; i++)
    {
        int count = 0;
        for (int j = 0; j < length; j++)
        {
            if (values[j] < values[i] || (values[j] == values[i] && j < i))
            {
                count++;
            }
        }
        sequence[i] = count;
    }

    free(values);
}

Time fromDate(struct tm date)
{
    long long minuteSeed, hourSeed;
    getSeedsFromDate(date, &minuteSeed, &hourSeed);

    Lcg minuteLcg = createLcg(minuteSeed, 2147483647, 48271, 0);
    Lcg hourLcg = createLcg(hourSeed, 4294967296, 1664525, 1013904223);

    int minuteSequence[60];
    int hourSequence[24];

    getSequenceFromLcg(minuteLcg, 60, minuteSequence);
    getSequenceFromLcg(hourLcg, 24, hourSequence);

    Time result = {hourSequence[date.tm_hour], minuteSequence[date.tm_min], date.tm_sec};
    return result;
}
