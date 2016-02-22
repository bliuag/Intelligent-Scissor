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

private:
	char imageName[256];
	ISUI* myUI;
};


#endif