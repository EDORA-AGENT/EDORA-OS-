#ifndef EDORA_KERNEL_H
#define EDORA_KERNEL_H

void kernelInit();
void kernelShutdown();

void kernelPanic();

void rebootSystem();
void shutdownSystem();

#endif