
#ifndef EDORA_VGA_H
#define EDORA_VGA_H

// ========================================
// EDORA OS VGA Terminal 3.1
// VGA Text Mode: 80x25
// Hardware Cursor
// ========================================

void vga_init();
void vga_clear();

void vga_putc(char c);
void vga_print(const char* text);

void vga_set_color(unsigned char foreground,
                   unsigned char background);

void vga_reset_color();

void vga_set_cursor(int x, int y);
void vga_get_cursor(int* x, int* y);

void vga_write_at(int x, int y, char c);

void vga_draw_box(int x1, int y1,
                  int x2, int y2);

void vga_draw_header(const char* title);
void vga_draw_footer(const char* text);

void vga_terminal_start();
void vga_terminal_prompt();

#endif
