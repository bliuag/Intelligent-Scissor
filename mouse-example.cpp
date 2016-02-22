#include <stdio.h>
#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Scroll.H>
#include <FL/Fl_Box.H>
//
// Demonstrate getting mouse click coords on a scrollable box
// erco 08/14/2005
//
class ScrollBox : public Fl_Box {
    Fl_Scroll *scroll;
public:
    int handle(int e) {
        if ( e == FL_PUSH ) {
            fprintf(stderr, "event_x,event_y: %d,%d, Hit on box: %d,%d\n",
                Fl::event_x(),
                Fl::event_y(),
                Fl::event_x() - scroll->x() + scroll->hscrollbar.value(),
                Fl::event_y() - scroll->y() + scroll->scrollbar.value());
        }
        return(Fl_Box::handle(e));
    }
    void SetScroll(Fl_Scroll *val) {
        scroll = val;
    }
    ScrollBox(int x,int y,int w,int h,const char*l=0) : Fl_Box(x,y,w,h,l) {
        color(FL_BLUE);
        box(FL_FLAT_BOX);
    }
};
int main() {
    Fl_Double_Window win(400, 400);
    Fl_Scroll scroll(0,0,400,400);
    ScrollBox box(0,0,1000,1000);       // box is bigger than scroll
    box.SetScroll(&scroll);
    scroll.end();
    win.resizable(win);
    win.show();
    return(Fl::run());
} 