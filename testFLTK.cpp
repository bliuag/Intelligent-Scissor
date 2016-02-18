#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Check_Button.H>

int main(int argc, char **argv) {
    Fl_Window *window = new Fl_Window(600, 360);

    window->end();
    window->show(argc, argv);

    return Fl::run();
}