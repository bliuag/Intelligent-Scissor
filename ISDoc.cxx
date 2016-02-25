
#include <FL/fl_ask.H>
#include "ISDoc.h"
#include "ISUI.h"
#include <cstring>
#include <iostream>
using namespace std;int test;
ISDoc::ISDoc(){
	curmap=bitmap = NULL;
	imageName[0] = '\0';
	z=1;
	width=height=0;
	matrix=NULL;
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
	}cout<<"breakpoint2"<<endl;
	bitmap = data;
	zw=width = w;
	zh=height = h;
	z=1;
	//initializeMatrix();
	//refreshcurmap();
	curmap=bitmap;
	myUI->pic->refresh();
	cout<<"breakpoint3"<<endl;
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

	refreshcurmap();
}

void ISDoc::initializeMatrix()
{
	if(matrix!=NULL)
	{
		for(int i=0;i<height;i++)
			delete matrix[i];
		delete matrix;
	}
	matrix=new Node*[height];
	for(int i=0;i<height;i++)
		matrix[i]=new Node[width];
	for(int i=0;i<height;i++)
		for(int j=0;j<width;j++)
		{
			matrix[i][j].c1=bitmap[(i*width+j)*3];
			matrix[i][j].c2=bitmap[(i*width+j)*3+1];
			matrix[i][j].c3=bitmap[(i*width+j)*3+2];
			matrix[i][j].state=0;
			matrix[i][j].totalCost=-1;
			matrix[i][j].preNode=NULL;
			matrix[i][j].row=i;
			matrix[i][j].column=j;
		}
}

void ISDoc::refreshcurmap()
{
	if(curmap!=NULL)
		delete curmap;
	curmap=new unsigned char[zw*zh*3];

	for(int i=0;i<zh;i++)
		for(int j=0;j<zw;j++)
		{
			curmap[(i*zw+j)*3]=matrix[int(i/z)][int(j/z)].c1;
			curmap[(i*zw+j)*3+1]=matrix[int(i/z)][int(j/z)].c2;
			curmap[(i*zw+j)*3+2]=matrix[int(i/z)][int(j/z)].c3;
		}
	cout << "curmap" << endl;
	for(int i=0;i<zh*zw;i++)
			if (curmap[i]!=bitmap[i])
				cout << "Wrong!!" << endl;
	
	myUI->pic->refresh();
}
