#ifndef PICVIEW_H
#define PICVIEW_H

#include <FL/Fl.H>

#include <FL/Fl_Gl_Window.H>
#include <FL/gl.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>

#include <stdlib.h>

class ISDoc;

class PicView : public Fl_Gl_Window
{
public:
	PicView(int x,int y,int width,int height,const char* message);

	void draw();
	void refresh();

	ISDoc *myDoc;
	void stopContour();
	int handle(int event);
	bool contour;
private:
	int width;
	int height;
	
};

#endif