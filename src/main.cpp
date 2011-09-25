#include <iostream>
#include <cstdlib> //getenv
#include <cairo/cairo.h>
#include <boost/shared_ptr.hpp>
#include <sys/stat.h>
#include <string>
#include <vector>
#include <sstream>
#include <ostream>
#include <iterator>
#include <time.h>
#include "keyboard.hpp"
#include "screenshot.hpp"
#include "config.h"

namespace screengrab {
    using namespace std;
    
    typedef boost::shared_ptr< std::vector<unsigned char> > bitvector;

    // Where will we store files?
    string output_dir;

    void check_output_directory() {
            // Don't actually care if this fails, so long as we can write there...
            char* home_dir = getenv("HOME");
            output_dir = home_dir;
            output_dir += "/.screengrab";
            mkdir(output_dir.c_str(), 0777);
            output_dir += "/output";
            mkdir(output_dir.c_str(), 0777);
    }

    string get_output_filename() {
            time_t epoch_time;
            epoch_time = time(NULL);
            stringstream output;
            output <<  output_dir;
            output << "/screengrab_";
            output << epoch_time;
            output << ".png";
            return output.str();
    }

    struct ScreenGrabHandler {
            public:
                    ScreenGrabHandler(ScreenGrabber& sg) : sg(sg) {} ;

                    bool operator()(void) {
                            // Get a bitvector representing a png of the screen
                            bitvector png = sg.grab_screen();

                            // Dump the bigvector to a file
                            ofstream outfile(get_output_filename().c_str(), ios::out | ios::binary);
                            ostream_iterator<unsigned char> file_iterator(outfile, NULL);
                            copy(png->begin(), png->end(), file_iterator);
                            return true;
                    }
            private:
                    ScreenGrabber sg;
    };

    struct QuitHandler {
            public:
                    bool operator()(void) {
                            return false;
                    }
    };

}

using namespace screengrab;

int main(int argc, char ** argv) {
        check_output_directory();
        KeyboardGrabber keyboard;
        ScreenGrabber screenGrabber;
        ScreenGrabHandler screenHandle(screenGrabber);
        keyboard.addToHandlers(screenHandle,
                                "Print",
                                true, false, false);
        QuitHandler quit;
        keyboard.addToHandlers(quit,
                                "q",
                                true, true, false);
        keyboard.mainloop();
        return 0;
}
