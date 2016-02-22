
#include <FL/fl_ask.H>
#include "ISDoc.h"
#include "ISUI.h"

ISDoc::ISDoc(){
	bitmap = NULL;
	imageName[0] = '\0';


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
	width = w;
	height = h;


	return 1;
}

int ISDoc::saveImage(char* picName){
	writeBMP(picName, width, height, bitmap);
	return 1;
}