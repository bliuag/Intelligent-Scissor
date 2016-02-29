#include <stdio.h>

#include "ISUI.h"
#include "ISDoc.h"
#include <iostream>
using namespace std;
ISUI* myUI;
ISDoc* myDoc;
// For auxiliary purpose
	//diagonal:1,3,5,7
	int dir[8][2]={{1,0},{1,-1},{0,-1},{-1,-1},
				   {-1,0},{-1,1},{0,1},{1,1}};


int main(){

	myUI = new ISUI();
	myDoc = new ISDoc();

	myUI->setDocument(myDoc);
	myDoc->setUI(myUI);

	Fl::visual(FL_DOUBLE|FL_INDEX);

	myUI->show();

	return Fl::run();
}