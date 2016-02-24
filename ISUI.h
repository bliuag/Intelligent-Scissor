#ifndef ISUI_H
#define ISUI_H


#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Menu_Item.H>
//#include <FL/fl_ask.h>
#include <FL/Fl_File_Chooser.H>
//#include <fstream>
//#include <FL/Fl_Shared_Image.H>
//#include <FL/Fl_BMP_Image.H>
//#include <FL/Fl_Box.H>
#include <FL/Fl_Double_Window.H>
#include "PicView.h"
#include <FL/Fl_Scroll.H>

class ISDoc;


class ISUI{

public:
	ISUI();

	void show();

	void setDocument(ISDoc*);
	ISDoc* getDocument();

	Fl_Double_Window* mainWindow;
	Fl_Menu_Bar* menuBar;
	PicView* pic;
	static Fl_Menu_Item menuitems[];

private:
	static ISUI* whoami(Fl_Menu_* o);

	static void cb_open(Fl_Menu_ *w, void *);
	static void cb_save_contour(Fl_Menu_ *w, void *);
	static void cb_save_mask(Fl_Widget *w, void *);
	static void cb_quit(Fl_Widget *w, void *);

	static void cb_brush(Fl_Widget *w, void *);
	static void cb_scissor(Fl_Widget *w, void *);
	static void cb_3x3(Fl_Widget *w, void *);
	static void cb_4x4(Fl_Widget *w, void *);
	static void cb_5x5(Fl_Widget *w, void *);

	static void cb_zoom_in(Fl_Widget *w, void *);
	static void cb_zoom_out(Fl_Widget *w, void *);

	ISDoc* myDoc;

};

#endif