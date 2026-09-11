#include "system.h"

static unsigned int features = 0;

void system_init()
{
    unsigned int eax = 0;
    unsigned int ebx = 0;
    unsigned int ecx = 0;
    unsigned int edx = 0;

    asm volatile("cpuid"
                 : "=a"(eax), "=b"(ebx), "=c"(ecx), "=d"(edx)
                 : "a"(1));

    features = edx;
}

void system_cpu_vendor(char* vendor)
{
    unsigned int eax = 0;
    unsigned int ebx = 0;
    unsigned int ecx = 0;
    unsigned int edx = 0;

    asm volatile("cpuid"
                 : "=a"(eax), "=b"(ebx), "=c"(ecx), "=d"(edx)
                 : "a"(0));

    vendor[0] = static_cast<char>(ebx);
    vendor[1] = static_cast<char>(ebx >> 8);
    vendor[2] = static_cast<char>(ebx >> 16);
    vendor[3] = static_cast<char>(ebx >> 24);
    vendor[4] = static_cast<char>(edx);
    vendor[5] = static_cast<char>(edx >> 8);
    vendor[6] = static_cast<char>(edx >> 16);
    vendor[7] = static_cast<char>(edx >> 24);
    vendor[8] = static_cast<char>(ecx);
    vendor[9] = static_cast<char>(ecx >> 8);
    vendor[10] = static_cast<char>(ecx >> 16);
    vendor[11] = static_cast<char>(ecx >> 24);
    vendor[12] = 0;
}

unsigned int system_cpu_features()
{
    return features;
}
