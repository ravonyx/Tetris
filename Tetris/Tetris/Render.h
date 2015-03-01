#ifndef RENDER_H
#define RENDER_H

#include <string>

void DisplayText(const std::string& text, unsigned char x, unsigned char y, unsigned char size, unsigned char fR, unsigned char fG, unsigned char fB, unsigned char bR, unsigned char bG, unsigned char bB);
void DrawBackground();
void ClearScreen();

#endif
