#include <iostream>
#include <memory>
#include <cairo/cairo.h>
#include <thread>
#include <boost/filesystem.hpp>
#include <boost/thread.hpp>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <ostream>
#include <iterator>
#include <time.h>
#include "keyboard.hpp"
#include "screenshot.hpp"


using namespace std;

namespace screengrab {
    
    typedef unique_ptr< vector<unsigned char> > bitvector;

    string get_output_filename() {
            // TODO: Should replace all this with a config file!
            static int counter = 0; // Avoid name clashes
            time_t epoch_time;
            epoch_time = time(NULL);
            stringstream output;
            output <<  OUTPUT_DIR;
            output << "/screengrab_";
            output << epoch_time;
            output << counter++;
            output << ".png";
            return output.str();
    }

    class ScreenGrabHandler {
            private:
                    shared_ptr<ScreenGrabber> sg;
            public:
                    ScreenGrabHandler(shared_ptr<ScreenGrabber> sg) : sg(sg)  { }
                    
                    bool operator()(void) const {
                            // Do this work in a thread, in case it's hard.
                            boost::thread([&sg]() {
                                // Get a bitvector representing a png of the screen
                                bitvector png = sg->grab_screen();

                                // Dump the bigvector to a file
                                //ofstream outfile(get_output_filename().c_str(), ios::out | ios::binary);
                                //ostream_iterator<unsigned char> file_iterator(outfile, NULL);
                                //assert(png);
                                //copy(png->begin(), png->end(), file_iterator);
                            });

                            return true;
                    }
    };

    class QuitHandler {
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
        shared_ptr<ScreenGrabber> screenGrabber(new ScreenGrabber());
        unique_ptr< function< bool () > > screenHandleFunction(new function< bool () >(ScreenGrabHandler(screenGrabber)));
        keyboard.addToHandlers(move(screenHandleFunction),
                                "Print",
                                true, false, false);
        unique_ptr< function< bool() > > quitHandleFunction(new function< bool () >(QuitHandler()));
        keyboard.addToHandlers(move(quitHandleFunction),
                                "q",
                                true, true, false); 
        keyboard.mainloop();
        return 0;
}
