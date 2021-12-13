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
int CamZPos = 5;

void DrawTri3D(int x, int y, int z, int x2, int y2, int z2, int x3, int y3, int z3)
{

	Debug_Printf(1,17,true,0,"DrawTri3D(%d, %d, %d, %d, %d, %d, %d, %d, %d)", x, y, z, x2, y2, z2, x3, y3, z3);
	// prevent Infinity
	if (CamZPos + z == 0) {z++;}
	if (CamZPos + z2 == 0) {z2++;}
	if (CamZPos + z3 == 0) {z3++;}
	Debug_Printf(1,18,true,0,"DrawTri3D(%d, %d, %d, %d, %d, %d, %d, %d, %d) New", x, y, z, x2, y2, z2, x3, y3, z3);
	Debug_Printf(1,19,true,0,"Fov: %d, CamX: %d, CamY: %d, CamZ: %d", FoV, CamXPos, CamYPos, CamZPos);

	Debug_Printf(1,5,true,0,"L1x: %d", FoV * (x + CamXPos) / (CamZPos + z));
	Debug_Printf(1,6,true,0,"L1y: %d", FoV * (y + CamYPos) / (z + CamZPos));
	Debug_Printf(1,7,true,0,"L1x2: %d", FoV * (x2 + CamXPos) / (CamZPos + z2));
	Debug_Printf(1,8,true,0,"L1y2: %d", FoV * (y2 + CamYPos) / (z2 + CamZPos));
	Debug_Printf(1,9,true,0,"L2x: %d", FoV * (x2 + CamXPos) / (CamZPos + z2));
	Debug_Printf(1,10,true,0,"L2y: %d", FoV * (y2 + CamYPos) / (z2 + CamZPos));
	Debug_Printf(1,11,true,0,"L2x2: %d", FoV * (x3 + CamXPos) / (CamZPos + z3));
	Debug_Printf(1,12,true,0,"L2y2: %d", FoV * (y3 + CamYPos) / (z3 + CamZPos));
	Debug_Printf(1,13,true,0,"L3x: %d", FoV * (x3 + CamXPos) / (CamZPos + z3));
	Debug_Printf(1,14,true,0,"L3y: %d", FoV * (y3 + CamYPos) / (z3 + CamZPos));
	Debug_Printf(1,15,true,0,"L3x2: %d", FoV * (x + CamXPos) / (CamZPos + z));
	Debug_Printf(1,16,true,0,"L3y2: %d", FoV * (y + CamYPos) / (z + CamZPos));

	line(FoV * (x + CamXPos) / (CamZPos + z), FoV * (y + CamYPos) / (z + CamZPos), FoV * (x2 + CamXPos) / (CamZPos + z2), FoV * (y2 + CamYPos) / (z2 + CamZPos), color(0, 0, 255));
	line(FoV * (x2 + CamXPos) / (CamZPos + z2), FoV * (y2 + CamYPos) / (z2 + CamZPos), FoV * (x3 + CamXPos) / (CamZPos + z3), FoV * (y3 + CamYPos) / (z3 + CamZPos), color(0, 0, 255));
	line(FoV * (x3 + CamXPos) / (CamZPos + z3), FoV * (y3 + CamYPos) / (z3 + CamZPos), FoV * (x + CamXPos) / (CamZPos + z), FoV * (y + CamYPos) / (z + CamZPos), color(0, 0, 255));
}
