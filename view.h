#ifndef VIEW_H
#define VIEW_H

enum Viewmode {
	FPS,
	TPS,
};

extern Viewmode view;

void view_change() {
	if (view == TPS) {
		view = FPS;
		return;
	}
	else if (view == FPS) {
		view = TPS;
		return;
	}
}
#endif