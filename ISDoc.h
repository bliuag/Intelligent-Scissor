#ifndef ISDoc_H
#define ISDoc_H

#include "bitmap.h"

class ISUI;

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
	unsigned char*  zmap;
	void zoom(char inq);
private:
	char imageName[256];
	ISUI* myUI;
};


#endif