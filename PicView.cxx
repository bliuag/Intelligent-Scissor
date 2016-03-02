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
	contour=false;
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
		valid(1);

	}

	glClear( GL_COLOR_BUFFER_BIT );
	if(myDoc->curmap)
	{
		
		int drawWidth, drawHeight;
		GLvoid* bitstart;

		width=w();
		height=h();

		Point scrollpos;//=GetScrollPosition();
		scrollpos.col=scrollpos.row=0;

		drawWidth	= min(width, myDoc->zw);
		drawHeight	= min(height,myDoc->zh);

		int startrow = myDoc->zh - (scrollpos.row+drawHeight);
		if(startrow<0)
			startrow=0;
		bitstart = myDoc->curmap+3*((myDoc->zw*startrow)+scrollpos.col);

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
	flush();
}


void PicView::stopContour()
{
	contour=false;
	// if(myDoc->seed!=NULL)
	// {
	// 	delete myDoc->seed;
	// 	myDoc->seed=NULL;
	// }
	// if(myDoc->last!=NULL)
	// {
	// 	delete myDoc->last;
	// 	myDoc->last=NULL;
	// }
	myDoc->stopContour();
}

int PicView::handle(int event)
{
	switch(event){
	case FL_PUSH:
		//cout<<"x: "<<Fl::event_y()<<" y: "<<Fl::event_x()<<"\n";
		if (Fl::event_y()<=0 || Fl::event_y()>myDoc->zh || Fl::event_x()<=0 || Fl::event_x()>myDoc->zw) break;
		if (myDoc->mode!=WORK_MODE) break;
		myDoc->setSeed(myDoc->height - (Fl::event_y())/myDoc->z -1,Fl::event_x()/myDoc->z);
		contour=true;
		flush();
		break;
	case FL_MOVE:
		if (Fl::event_y()<=0 || Fl::event_y()>myDoc->zh || Fl::event_x()<=0 || Fl::event_x()>myDoc->zw) break;
		if(contour && myDoc->mode==WORK_MODE){
			//cout<<"x: "<<Fl::event_y()<<" y: "<<Fl::event_x()<<"\n";
			myDoc->drawContour(myDoc->height - (Fl::event_y())/myDoc->z -1,Fl::event_x()/myDoc->z);
		}
		break;
	case FL_ENTER:
		return true;
	default:
		return 0;
		break;

	}
	return true;
}


