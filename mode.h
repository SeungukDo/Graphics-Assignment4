#ifndef MODE_H
#define MODE_H

enum Gamemode {
	NORMAL,
	ALLPASS,
	ALLFAIL,
};

enum LineRendering {
	SHOWING,
	HIDING
};

enum Shading {
	GOURAUD,
	PHONG
};

enum Diffuse {
	D_ENABLE,
	D_DISABLE
};

enum NormalMap {
	N_ENABLE,
	N_DISABLE
};

extern Gamemode mode;
extern LineRendering line_rendering;
extern Shading shading;
extern Diffuse diffuse;
extern NormalMap normal_map;
#endif