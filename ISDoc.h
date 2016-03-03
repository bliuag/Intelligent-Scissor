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

struct Point{
	int row;
	int col;
};

struct Node{
 	unsigned char c1,c2,c3;
 	double linkCost[8];
 	double DR[8];
 	double DG[8];
 	double DB[8];
 	double D[8];
 	int state;
 	double totalCost;
 	Node* preNode;
 	int preNodeDir;
 	int row;
 	int col;
 	int drawed;
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
	void backToWorkMode();
	void drawContour(int,int);

	void pixelNode();
	void costGraph();
	void pathTree(int,int,int);
	void minPath(int,int);

	int calcCostTree(int,int,int);
	Point* seed;
	Point* last;
	bool mode;
	
	void undo();
	void stopContour();
	void setSeed(int,int);
	void closeContour();
private:
	void initializeMatrix();
	void refreshCurmap();
	void calcLinkCost();
	void initStates();
	char imageName[256];
	ISUI* myUI;
	Node** nodeMatrix;
	Color** debugMatrix;
	double maxD;
	int curlayer;
	
};


#endif