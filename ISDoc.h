#ifndef ISDoc_H
#define ISDoc_H

#include "bitmap.h"
#define INITIAL 0
#define ACTIVE 1
#define EXPANDED 2
#define WORK_MODE 0
#define DEBUG_MODE 1

class ISUI;

struct Color{
	unsigned char c1,c2,c3;
};

struct Point
{
	int row;
	int col;
};

struct Node
 {
 	unsigned char c1,c2,c3;
 	double linkCost[8];
 	double DR[8];
 	double DG[8];
 	double DB[8];
 	double D[8];
 	int state;
 	double totalCost;
 	Node* preNode;
 	int row;
 	int col;
 	bool drawed;
 };


class ISDoc{

public: 
	ISDoc();
	void setUI(ISUI*);
	char* getImageName();

	int loadImage(const char* picName);
	int saveImage(char* picName);
	int width,height;
	unsigned char*	bitmap;
	int zw,zh;
	double z;
	unsigned char*  curmap;
	void zoom(char inq);
	void pixelNode();

	void calcCostTree(int,int);
	Point* seed;
	Point* last;
	bool mode;
	void drawContour(int,int);
private:
	void initializeMatrix();
	void refreshCurmap();
	void calcLinkCost();
	void initStates();
	

	char imageName[256];
	ISUI* myUI;
	Node** nodeMatrix;
	Color** debugMatrix;
	Color** drawMatrix;


};


#endif