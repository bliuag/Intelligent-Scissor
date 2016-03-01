
#include <FL/fl_ask.H>
#include "ISDoc.h"
#include "ISUI.h"
#include <cstring>
#include <iostream>
using namespace std;
ISDoc::ISDoc(){
	curmap=bitmap = NULL;
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
	z=1;
	initializeMatrix();
	refreshCurmap();
	// int l=width*height*3;
	// curmap=new unsigned char[l];
	// for(int i=0;i<l;i++)
	// 	curmap[i]=bitmap[i];
	//curmap=bitmap;
	//myUI->mainWindow->resize(myUI->mainWindow->x(),myUI->mainWindow->y(),width,height+20);

	//myUI->pic->resizeView(width,height);

	//myUI->pic->refresh();
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
	cout<<"bp1\n";
	refreshCurmap();
}

void ISDoc::initializeMatrix(){


	matrix = new Node*[height];
	for (int i=0;i<height;i++)
		matrix[i] = new Node[width];

	for (int i=0;i<height;i++)
		for (int j=0;j<width;j++){
			matrix[i][j].c1=bitmap[(i*width+j)*3];
			matrix[i][j].c2=bitmap[(i*width+j)*3+1];
			matrix[i][j].c3=bitmap[(i*width+j)*3+2];
			matrix[i][j].row=i;
			matrix[i][j].col=j;
			matrix[i][j].state=0;
			matrix[i][j].preNode=NULL;
			matrix[i][j].totalCost=-1.0;
		}

}

void ISDoc::refreshCurmap()
{
	curmap=new unsigned char[zw*zh*3];
	for(int i=0;i<zh;i++)
		for(int j=0;j<zw;j++)
		{
			curmap[(i*zw+j)*3]=matrix[int(i/z)][int(j/z)].c1;
			curmap[(i*zw+j)*3+1]=matrix[int(i/z)][int(j/z)].c2;
			curmap[(i*zw+j)*3+2]=matrix[int(i/z)][int(j/z)].c3;
		}
	myUI->pic->refresh();
}


