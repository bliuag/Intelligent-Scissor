#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Menu_Item.H>

int main(int argc, char **argv) {
    Fl::scheme("gtk+");
    Fl_Window *window = new Fl_Window(600, 360);
    Fl_Menu_Bar *m=new Fl_Menu_Bar(0,0,600,20);
    Fl_Menu_Item menuItems[]=
    {
        {"File",0,0,0,FL_SUBMENU|FL_MENU_DIVIDER},
        {"Open",FL_CTRL+'o',0,0,0},
        {"Save Contour",FL_CTRL+'c',0,0,0},
        {"Save Mask",FL_CTRL+'m',0,0,0},
        {0},
        {"Function",0,0,0,FL_MENU_DIVIDER|FL_SUBMENU},
        {"Brush",FL_CTRL+'b',0,0,0},
        {"Scissor",FL_CTRL+'r',0,0,0},
        {0},
        {"About",0,0,0,FL_SUBMENU},
        {"Instructions",FL_CTRL+'i',0,0,FL_MENU_DIVIDER},
        {"Project",FL_CTRL+'p',0,0,0},
        {0},
        {0}
    };
    m->copy(menuItems);
    window->end();
    window->show(argc, argv);

    return Fl::run();
}