#ifndef ISDoc_H
#define ISDoc_H

#include "bitmap.h"

class ISUI;

struct Node
{
	unsigned char c1,c2,c3;
	double linkCost[8];
	int state;
	double totalCost;
	Node* preNode;
	int row;
	int column;
	
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
	void blur();
	void initializeMatrix();
	void refreshcurmap();
	struct Node** matrix;
private:
	char imageName[256];
	ISUI* myUI;
	
	int radius;
};


#endif