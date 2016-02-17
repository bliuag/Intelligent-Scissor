#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Check_Button.H>

int main(int argc, char **argv) {
    Fl_Window *window = new Fl_Window(600, 360);
    Fl_Box *box = new Fl_Box(0, 0, 100, 100, "Hello, World!");
    box->box(FL_DOWN_BOX);
    box->labelsize(10);
    box->labelfont(FL_BOLD+FL_ITALIC);
    box->labeltype(FL_SHADOW_LABEL);

    Fl_Box *box1 = new Fl_Box(300, 0, 100, 100, "Hello, World!");
    box1->box(FL_UP_BOX);
    box1->labelsize(10);
    box1->labelfont(FL_BOLD+FL_ITALIC);
    box1->labeltype(FL_SHADOW_LABEL);

    Fl_Check_Button *button = new Fl_Check_Button(300,150,100,100,"test");

    window->end();
    window->show(argc, argv);

    return Fl::run();
}