#pragma once
#include <stdio.h>

#define LOG_INFO(...)       fprintf(stdout,"[INFO] "__VA_ARGS__)
#define LOG_WARNING(...)    fprintf(stderr,"[WARNING] "__VA_ARGS__)
#define LOG_ERROR(...)      fprintf(stderr,"[ERROR] "__VA_ARGS__)