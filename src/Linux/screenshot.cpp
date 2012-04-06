#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <cairo/cairo-xlib.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "screenshot.hpp"
#include "cairo_helper.hpp"

using namespace std;

shared_ptr< vector<unsigned char> > ScreenGrabber::grab_screen() const
{
    Display* display = XOpenDisplay(NULL);
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
    auto out = cairo_helpers::cairo_to_mem_png(screen_surface);
    cairo_surface_destroy(screen_surface);
    return out;
}

