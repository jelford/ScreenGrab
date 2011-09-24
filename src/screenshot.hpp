#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <cairo/cairo-xlib.h>
#include <iostream>
#include <fstream>

#include <stdlib.h>

class ScreenGrabber {
	public:
		cairo_surface_t* grab_screen() {
			std::cout << "Taking a screen shot now!" << std::endl;
			Display* display = XOpenDisplay(0);
			Window rootWindow = DefaultRootWindow(display);
			int x, y;
			unsigned int width, height, border_width, border_height, depth;
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
			return screen_surface;			
		}

};

