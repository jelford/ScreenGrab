#include <iostream>
#include <cairo/cairo.h>
#include "keyboard.hpp"
#include "screenshot.hpp"

class ScreenGrabHandler {
	public:
		ScreenGrabHandler(ScreenGrabber& sg) : sg(sg) {} ;

		bool operator()(void) {
			cairo_surface_t* screen_image = sg.grab_screen();
			cairo_surface_write_to_png(screen_image, "out.png");
			cairo_surface_destroy(screen_image);
			return true;
		}
	private:
		ScreenGrabber sg;
};

class QuitHandler {
	public:
		bool operator()(void) {
			return false;
		}
};

int main(int argc, char ** argv) {
	
	KeyboardGrabber keyboard;
	ScreenGrabber screenGrabber;
	ScreenGrabHandler screenHandler(screenGrabber);
	keyboard.addToHandlers(&screenHandler,
				"Print",
				true, false, false, false);
	QuitHandler quit;
	keyboard.addToHandlers(&quit,
				"q",
				true, false, false, false);
	keyboard.mainloop();
	return 0;
}
