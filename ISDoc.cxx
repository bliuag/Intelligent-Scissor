
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


char* getImageName()