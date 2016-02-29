
#include <FL/fl_ask.H>
#include "ISDoc.h"
#include "ISUI.h"
#include <cstring>
#include <iostream>
#include <cmath>
using namespace std;
ISDoc::ISDoc(){
	curmap=bitmap = NULL;
	imageName[0] = '\0';
	z=1.0;
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
	z=1.0;
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
	refreshCurmap();
}

void ISDoc::initializeMatrix(){

	nodeMatrix = new Node*[height];
	for (int i=0;i<height;i++)
		nodeMatrix[i] = new Node[width];

	for (int i=0;i<height;i++)
		for (int j=0;j<width;j++){
			nodeMatrix[i][j].c1=bitmap[(i*width+j)*3];
			nodeMatrix[i][j].c2=bitmap[(i*width+j)*3+1];
			nodeMatrix[i][j].c3=bitmap[(i*width+j)*3+2];
			nodeMatrix[i][j].row=i;
			nodeMatrix[i][j].col=j;
			nodeMatrix[i][j].state=0;
			nodeMatrix[i][j].preNode=NULL;
			nodeMatrix[i][j].totalCost=-1;
		}
}

void ISDoc::refreshCurmap()
{
	curmap=new unsigned char[zw*zh*3];
	for(int i=0;i<zh;i++)
		for(int j=0;j<zw;j++)
		{
			curmap[(i*zw+j)*3]=nodeMatrix[int(i/z)][int(j/z)].c1;
			curmap[(i*zw+j)*3+1]=nodeMatrix[int(i/z)][int(j/z)].c2;
			curmap[(i*zw+j)*3+2]=nodeMatrix[int(i/z)][int(j/z)].c3;
		}
	myUI->pic->refresh();
}

void ISDoc::calcLinkCost(){
	// Not calcute the out round of the pixels. To be handled later.
	double maxD=0;
	for (int i=1;i<width-1;i++)
		for (int j=1;j<height-1;j++)
			for (int d=0;d<8;d++){
				double DR,DG,DB;
				if (d%2==0){ //vertical or horizontal lines
					DR= abs( (nodeMatrix[i+dir[(d+1)%8][0]][j+dir[(d+1)%8][1]].c1 +
							  nodeMatrix[i+dir[(d+2)%8][0]][j+dir[(d+2)%8][1]].c1)/2.0 -
							 (nodeMatrix[i+dir[(d+7)%8][0]][j+dir[(d+7)%8][1]].c1 +
							  nodeMatrix[i+dir[(d+6)%8][0]][j+dir[(d+6)%8][1]].c1)/2.0 ) /2.0;
					DG= abs( (nodeMatrix[i+dir[(d+1)%8][0]][j+dir[(d+1)%8][1]].c2 +
							  nodeMatrix[i+dir[(d+2)%8][0]][j+dir[(d+2)%8][1]].c2)/2.0 -
							 (nodeMatrix[i+dir[(d+7)%8][0]][j+dir[(d+7)%8][1]].c2 +
							  nodeMatrix[i+dir[(d+6)%8][0]][j+dir[(d+6)%8][1]].c2)/2.0 ) /2.0;
					DB= abs( (nodeMatrix[i+dir[(d+1)%8][0]][j+dir[(d+1)%8][1]].c3 +
							  nodeMatrix[i+dir[(d+2)%8][0]][j+dir[(d+2)%8][1]].c3)/2.0 -
							 (nodeMatrix[i+dir[(d+7)%8][0]][j+dir[(d+7)%8][1]].c3 +
							  nodeMatrix[i+dir[(d+6)%8][0]][j+dir[(d+6)%8][1]].c3)/2.0 ) /2.0;
					nodeMatrix[i][j].D[d] = sqrt((DR*DR+DG*DG+DB*DB)/3);

					maxD = max(maxD, nodeMatrix[i][j].D[d]);
				}else{ // diagonal lines
					DR= abs( nodeMatrix[i+dir[(d+1)%8][0]][j+dir[(d+1)%8][1]].c1 - 
						 	 nodeMatrix[i+dir[(d+7)%8][0]][j+dir[(d+7)%8][1]].c1)/sqrt(2);
					DG= abs( nodeMatrix[i+dir[(d+1)%8][0]][j+dir[(d+1)%8][1]].c2 - 
						 	 nodeMatrix[i+dir[(d+7)%8][0]][j+dir[(d+7)%8][1]].c2)/sqrt(2);
					DB= abs( nodeMatrix[i+dir[(d+1)%8][0]][j+dir[(d+1)%8][1]].c3 - 
						 	 nodeMatrix[i+dir[(d+7)%8][0]][j+dir[(d+7)%8][1]].c3)/sqrt(2);
					nodeMatrix[i][j].D[d] = sqrt((DR*DR+DG*DG+DB*DB)/3);

					maxD = max(maxD, nodeMatrix[i][j].D[d]);
				}
			}

	for (int i=1;i<width-1;i++)
		for (int j=1;j<height-1;j++)
			for (int d=0;d<8;d++){
				nodeMatrix[i][j].linkCost[d] = (maxD - nodeMatrix[i][j].D[d]);
				if (d%2==0)
					nodeMatrix[i][j].linkCost[d] *= 1;
				else
					nodeMatrix[i][j].linkCost[d] *= sqrt(2);
			}
}

void ISDoc::minCostPath(Node* seed){
	

}

