#include <stdio.h>

#include "ISUI.h"
#include "ISDoc.h"

ISUI* myUI;
ISDoc* myDoc;



int main(){
	myUI = new ISUI();
	myDoc = new ISDoc();

	myUI->setDocument(myDoc);
	myDoc->setDocument(myUI);

	myUI->show();

	return Fl::run();
}