#ifndef ISUI_H
#define ISUI_H


#include "ISUI.h"

class ISUI;

class ISDoc{

public: 
	ISDoc();
	void setUI(ISUI*);
	char* getImageName();


	int width,height;
	unsigned char*	bitmap;

private:
	char imageName[256];
	ISUI* myUI;
};


#endif