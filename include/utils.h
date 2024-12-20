#ifndef UTILS_H
#define UTILS_H

#include <time.h>

void initializeSystem();
time_t parseDate(const char *dateStr);
char* formatDate(time_t timestamp);
int validateIntInput(int min, int max);
double validateDoubleInput(double min, double max);
void validateStringInput(char *output, int maxLength, const char *prompt);
int validateDateInput(char *output);

#endif // UTILS_H

