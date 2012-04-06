#include "screengrabber_pimpl.hpp"

#include <X11/Xlib.h>
#include <cairo/cairo-xlib.h>
#include "cairo_helper.hpp"

using namespace std;
using namespace screengrab;

ScreenGrabber_Pimpl::~ScreenGrabber_Pimpl()
{
    XFree(display);
}

ScreenGrabber_Pimpl::ScreenGrabber_Pimpl()
    : display(XOpenDisplay(NULL)), rootWindow(DefaultRootWindow(display))
{

}

unique_ptr<vector<unsigned char>> ScreenGrabber_Pimpl::grab_screen()
{
    Window rootWindow = DefaultRootWindow(display);
    int x, y;
    unsigned int width, height, border_width, depth;
    Window theRootOfTheRoot;
    XGetGeometry(display, rootWindow, &theRootOfTheRoot,
                    &x, &y, &width, &height, 
                    &border_width, 
                    &depth);
    
    cairo_surface_t* screen_surface = cairo_xlib_surface_create(
            display,
            rootWindow,
            DefaultVisual(display, 0),
            width,
            height);
    unique_ptr<vector<unsigned char>> out = cairo_helpers::cairo_to_mem_png(screen_surface);
    cairo_surface_destroy(screen_surface);
    return out;
}
