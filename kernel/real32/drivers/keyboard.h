#ifndef EDORA_KEYBOARD_H
#define EDORA_KEYBOARD_H

void keyboard_init();

char keyboard_getchar();

bool keyboard_has_input();
void keyboard_irq_handler();

#endif