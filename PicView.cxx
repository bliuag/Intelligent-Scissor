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
	contour=0;
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

int PicView::handle(int event){
	switch(event){
	case FL_PUSH:
		//cout<<"x: "<<Fl::event_y()<<" y: "<<Fl::event_x()<<"\n";
		if (Fl::event_y()<=1 || Fl::event_y()/myDoc->z >= myDoc->height-2 || Fl::event_x()<=1 || Fl::event_x()/myDoc->z >= myDoc->width-2) break;
		if (myDoc->mode!=WORK_MODE) break;
		if (myDoc->scissorStatus && contour!=2){
			if (myDoc->haveBrushed && myDoc->nodeMatrix[myDoc->height - int((Fl::event_y())/myDoc->z) -1][int(Fl::event_x()/myDoc->z)].brushed==false) break;
			if (contour==0){
				myDoc->setStartSeed(myDoc->height - (Fl::event_y())/myDoc->z -1,Fl::event_x()/myDoc->z);
			}
			myDoc->setSeed(myDoc->height - (Fl::event_y())/myDoc->z -1,Fl::event_x()/myDoc->z);
			contour=1;
		}
		flush();
		break;
	case FL_MOVE:
		if (Fl::event_y()<=1 || Fl::event_y()/myDoc->z >= myDoc->height-2 || Fl::event_x()<=1 || Fl::event_x()/myDoc->z >= myDoc->width-2) break;
		if (myDoc->haveBrushed && myDoc->nodeMatrix[myDoc->height - int((Fl::event_y())/myDoc->z) -1][int(Fl::event_x()/myDoc->z)].brushed==false) break;
		if(/*compContour==false && */myDoc->scissorStatus && contour==1 && myDoc->mode==WORK_MODE){
			myDoc->drawContour(myDoc->height - (Fl::event_y())/myDoc->z -1,Fl::event_x()/myDoc->z);
		}
		break;
	case FL_DRAG:
		if (Fl::event_y()<=1 || Fl::event_y()/myDoc->z >= myDoc->height-2 || Fl::event_x()<=1 || Fl::event_x()/myDoc->z >= myDoc->width-2) break;
		if (myDoc->brushStatus && myDoc->mode==WORK_MODE){
			myDoc->drawBrush(myDoc->height - (Fl::event_y())/myDoc->z -1,Fl::event_x()/myDoc->z);
		}

	case FL_ENTER:
		return true;
	default:
		return 0;
		break;

	}
	return true;
}


