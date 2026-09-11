#ifndef EDORA_EXCEPTIONS_H
#define EDORA_EXCEPTIONS_H

void exceptions_init();
extern "C" void exception_dispatch(unsigned int vector);

#endif
