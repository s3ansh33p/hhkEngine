/**
 * @file 3d.hpp
 * @author SnailMath
 * @brief 3d library (a bit old and will be refactored)
 * @version 1.0
 * @date 2021-12-14
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

extern uint8_t arctan[];
