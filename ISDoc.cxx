
#include <FL/fl_ask.H>
#include "ISDoc.h"
#include "ISUI.h"
#include <cstring>
#include <iostream>
using namespace std;
ISDoc::ISDoc(){
	zmap=bitmap = NULL;
	imageName[0] = '\0';
	z=1;
	width=height=0;

}

void ISDoc::setUI(ISUI* ui){
	myUI = ui;
}


char* ISDoc::getImageName(){
	return imageName;
}

int ISDoc::loadImage(const char* picName){
	unsigned char* data;
	int	w, h;

	if ( (data=readBMP(picName, w, h))==NULL ) 
	{
		fl_alert("Can't load bitmap file");
		return 0;
	}
	bitmap = data;
	zw=width = w;
	zh=height = h;
	int l=width*height*3;
	zmap=new unsigned char[l];
	for(int i=0;i<l;i++)
		zmap[i]=bitmap[i];
	z=1;
	//myUI->mainWindow->resize(myUI->mainWindow->x(),myUI->mainWindow->y(),width,height+20);

	//myUI->pic->resizeView(width,height);

	myUI->pic->refresh();
	return 1;

}

int ISDoc::saveImage(char* picName){
	writeBMP(picName, width, height, bitmap);
	return 1;
}

void ISDoc::zoom(char inq)
{
	if(inq=='+')
		z*=2;
	else if(inq=='-')
		z*=0.5;
	zw=z*width;
	zh=z*height;
	int l=zw*zh*3;
	unsigned char *temp=new unsigned char[l];
	for(int i=0;i<zh;i++)
		for(int j=0;j<zw;j++)
		{
			temp[(i*zw+j)*3]=bitmap[(int(i/z)*width+int(j/z))*3];
			temp[(i*zw+j)*3+1]=bitmap[(int(i/z)*width+int(j/z))*3+1];
			temp[(i*zw+j)*3+2]=bitmap[(int(i/z)*width+int(j/z))*3+2];
		}

	delete zmap;
	zmap=temp;
	myUI->pic->refresh();
}
