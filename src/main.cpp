#include <iostream>
#include <cairo/cairo.h>
#include <boost/shared_ptr.hpp>
#include <boost/filesystem.hpp>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <ostream>
#include <iterator>
#include <time.h>
#include <boost/function.hpp>
#include "keyboard.hpp"
#include "screenshot.hpp"

namespace screengrab {
    using namespace std;
    
    typedef boost::shared_ptr< std::vector<unsigned char> > bitvector;

    string get_output_filename() {
            time_t epoch_time;
            epoch_time = time(NULL);
            stringstream output;
            output <<  OUTPUT_DIR;
            output << "/screengrab_";
            output << epoch_time;
            output << ".png";
            return output.str();
    }

    struct ScreenGrabHandler {
            public:
                    ScreenGrabHandler(ScreenGrabber sg) : sg(sg) { }
                    
                    bool operator()(void) const {
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
                    bool operator()(void) const {
                            return false;
                    }
    };

}

using namespace screengrab;

int main(int argc, char ** argv) {
        boost::filesystem::create_directories(OUTPUT_DIR);
        KeyboardGrabber keyboard;
        ScreenGrabber screenGrabber;
        boost::function< bool () > screenHandleFunction = ScreenGrabHandler(screenGrabber);
        keyboard.addToHandlers(screenHandleFunction,
                                "Print",
                                true, false, false);
        boost::function< bool() > quitHandleFunction = QuitHandler();
        keyboard.addToHandlers(quitHandleFunction,
                                "q",
                                true, true, false);
        keyboard.mainloop();
        return 0;
}
