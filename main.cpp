#include <iostream>
#include <cairo/cairo.h>
#include <sys/stat.h>
#include <string>
#include <string.h>
#include <sstream>
#include <time.h>
#include "keyboard.hpp"
#include "screenshot.hpp"

std::string output_dir = "output";

void check_output_directory() {
	// Don't actually care if this fails, so long as we can write there...
	int n = mkdir(output_dir.c_str(), 0777);
}

std::string get_output_filename() {
	time_t epoch_time;
	epoch_time = time(NULL);
	std::stringstream output;
	output <<  output_dir;
	output << "/screengrab_";
	output << epoch_time;
	output << ".png";
	return output.str();
}

class ScreenGrabHandler {
	public:
		ScreenGrabHandler(ScreenGrabber& sg) : sg(sg) {} ;

		bool operator()(void) {
			cairo_surface_t* screen_image = sg.grab_screen();
			cairo_surface_write_to_png(screen_image, get_output_filename().c_str());
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
	check_output_directory();
	KeyboardGrabber keyboard;
	ScreenGrabber screenGrabber;
	ScreenGrabHandler screenHandler(screenGrabber);
	keyboard.addToHandlers(screenHandler,
				"Print",
				true, false, false, false);
	QuitHandler quit;
	keyboard.addToHandlers(quit,
				"q",
				true, false, false, false);
	keyboard.mainloop();
	return 0;
}
