#include "PicView.h"
#include "ISDoc.h"

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

	if(myDoc->bitmap)
	{
		int drawWidth, drawHeight;
		GLvoid* bitstart;

		width=w();
		height=h();

		Point scrollpos;//=GetScrollPosition();
		scrollpos.x=scrollpos.y=0;

		drawWidth	= min(width, myDoc->width);
		drawHeight	= min(height,myDoc->height);

		int startrow = myDoc->height - (scrollpos.y+drawHeight);
		if(startrow<0)
			startrow=0;
		bitstart = myDoc->bitmap+3*((myDoc->width*startrow)+scrollpos.x);

		glRasterPos2i( 0, height - drawHeight );
		glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );
		glPixelStorei( GL_UNPACK_ROW_LENGTH, myDoc->width );
		glDrawBuffer( GL_BACK );
		glDrawPixels( drawWidth, drawHeight, GL_RGB, GL_UNSIGNED_BYTE, bitstart );//*/
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