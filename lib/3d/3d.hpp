/**
 * @file 3d.hpp
 * @author SnailMath
 * @brief 3d library
 * @version 1.1
 * @date 2021-12-16
 */

extern int camx;
extern int camy;
extern int camz;
extern int cama;
extern int camb;

int  to3dx(int x, int y, int z);
int intern_atan(int dx, int dy);
int  to3dy(int x, int y, int z);
void cube(int x, int y, int z, int w, uint16_t color);
void line(int x1, int y1, int z1, int x2, int y2, int z2, uint16_t color);
void triangle(int x1, int y1, int z1, int x2, int y2, int z2, int x3, int y3, int z3, uint16_t c1, uint16_t c2);

extern uint8_t arctan[];
