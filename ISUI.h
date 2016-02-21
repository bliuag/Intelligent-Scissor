#ifndef ISUI_H
#define ISUI_H


#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Menu_Item.H>
#include <FL/fl_ask.h>
#include <FL/Fl_File_Chooser.H>
#include <fstream>
#include <FL/Fl_Shared_Image.H>
#include <FL/Fl_BMP_Image.H>
#include <FL/Fl_Box.H>


class ISUI{

public:
	ISUI();




	void show();

	void setDocument(ISDoc*);
	ISDoc* getDocument();

	Fl_Window* mainWindow;
	Fl_Menu_Bar* menuBar;
	Fl_Menu_Item menuitems[];

private:
	
	void cb_open(Fl_Widget *w, void *);
	void cb_save_contour(Fl_Widget *w, void *);
	void cb_save_mask(Fl_Widget *w, void *);
	void cb_quit(Fl_Widget *w, void *);

	void cb_brush(Fl_Widget *w, void *);
	void cb_scissor(Fl_Widget *w, void *);
	void cb_3x3(Fl_Widget *w, void *);
	void cb_4x4(Fl_Widget *w, void *);
	void cb_5x5(Fl_Widget *w, void *);

	void cb_zoom_in(Fl_Widget *w, void *);
	void cb_zoom_out(Fl_Widget *w, void *);

	ISDoc* myDoc;

};

#endif