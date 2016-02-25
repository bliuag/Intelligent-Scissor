#include "PicView.h"
#include "ISDoc.h"
#include <iostream>
using namespace std;
#ifndef WIN32
#define min(a, b)	( ( (a)<(b) ) ? (a) : (b) )
#endif

PicView::PicView(int x,int y,int width,int height,const char* message): 
				Fl_Gl_Window(x,y,width,height,message)
{
	this->width=width;
	this->height=height;

}

void PicView::draw()
{

	cout << "ww" << endl;
	if(!valid())
	{
		glClearColor(0.7f, 0.7f, 0.7f, 1.0);

		// We're only using 2-D, so turn off depth 
		glDisable( GL_DEPTH_TEST );

		// Tell openGL to read from the front buffer when capturing
		// out paint strokes 
		glReadBuffer( GL_FRONT );
		ortho();

	}

	glClear( GL_COLOR_BUFFER_BIT );

	if(myDoc->curmap)
	{

		int drawWidth, drawHeight;
		GLvoid* bitstart;

		width=w();
		height=h();

		Point scrollpos;//=GetScrollPosition();
		scrollpos.x=scrollpos.y=0;

		drawWidth	= min(width, myDoc->zw);
		drawHeight	= min(height,myDoc->zh);

		int startrow = myDoc->zh - (scrollpos.y+drawHeight);
		if(startrow<0)
			startrow=0;
		bitstart = myDoc->curmap+3*((myDoc->zw*startrow)+scrollpos.x);
		
		glRasterPos2i( 0, height - drawHeight );
		glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );
		glPixelStorei( GL_UNPACK_ROW_LENGTH, myDoc->zw );
		glDrawBuffer( GL_BACK );
		glDrawPixels( drawWidth, drawHeight, GL_RGB, GL_UNSIGNED_BYTE, bitstart );//*/
		//glScalef(4,4,4);
		
		}

	glFlush();
}

void PicView::refresh()
{

	redraw();

}


void PicView::resizeView(int width,int height)
{
	resize(x(),y(),width,height);
}