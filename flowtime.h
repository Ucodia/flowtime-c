#include <time.h>

typedef struct Lcg
{
    long long z;
    long long modulus;
    long long multiplier;
    long long increment;
} Lcg;

typedef struct Time
{
    int hour;
    int minute;
    int second;
} Time;

double nextLcgValue(Lcg *lcg);
Lcg createLcg(long long seed, long long modulus, long long multiplier, long long increment);
void getSeedsFromDate(struct tm date, long long *minuteSeed, long long *hourSeed);
void getSequenceFromLcg(Lcg lcg, int length, int *sequence);
Time fromDate(struct tm date);
