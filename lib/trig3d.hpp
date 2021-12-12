/**
 * @file trig3d.hpp
 * @author DasHeiligeDönerhuhn
 * @brief 3D Triangle
 * @version 1.0
 * @date 2021-12-13
 */

int FoV = 20;
int CamXPos = 0;
int CamYPos = 0;
int CamZPos = 100;

void DrawTri3D(int x, int y, int z, int x2, int y2, int z2, int x3, int y3, int z3)
{
	line(FoV * (x + CamXPos) / (CamZPos + z), FoV * (y + CamYPos) / (z + CamZPos), FoV * (x2 + CamXPos) / (CamZPos + z2), FoV * (y2 + CamYPos) / (z2 + CamZPos), color(0, 0, 255));
	line(FoV * (x2 + CamXPos) / (CamZPos + z2), FoV * (y2 + CamYPos) / (z2 + CamZPos), FoV * (x3 + CamXPos) / (CamZPos + z3), FoV * (y3 + CamYPos) / (z3 + CamZPos), color(0, 0, 255));
	line(FoV * (x3 + CamXPos) / (CamZPos + z3), FoV * (y3 + CamYPos) / (z3 + CamZPos), FoV * (x + CamXPos) / (CamZPos + z), FoV * (y + CamYPos) / (z + CamZPos), color(0, 0, 255));
}
