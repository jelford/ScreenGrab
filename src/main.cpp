#include <iostream>
#include <string>

#include <memory>               // shared_ptr, unique_ptr
#include <thread>               // std::thread

// Image data
#include <vector>

// File output
#include <boost/filesystem.hpp> // boost::filesystem::create_directories

// Application libraries
#include "keyboard.hpp"
#include "screenshot.hpp"
#include "filewriter.hpp"

using namespace std;

namespace screengrab {
    
    typedef unique_ptr< vector<unsigned char> > bitvector;
    
    class ScreenGrabHandler
    {
            private:
                    shared_ptr<ScreenGrabber> sg;
                    shared_ptr<screengrab::FileWriter> file_writer;
            public:
                    ScreenGrabHandler(shared_ptr<ScreenGrabber> sg) : sg(sg), file_writer(new FileWriter())  { }
                    
                    virtual bool operator()(void) const 
                    {
                            // Do this work in a thread, in case it's hard.
                            thread([&sg, &file_writer]() {
                                // Get a bitvector representing a png of the screen
                                bitvector png = sg->grab_screen();
                                
                                file_writer->dump(move(png));
                            }).detach();

                            return true;
                    }

                    /* 
                     * We can't use std::move when we pass this into a std::function (TODO: Why?), so have a copy
                     * constructor but don't keep making new versions of the fields
                     */
                    ScreenGrabHandler(ScreenGrabHandler const & other) : sg(other.sg), file_writer(other.file_writer) { }
    };

    class QuitHandler 
    {
            public:
                    virtual bool operator()(void) const 
                    {
                            return false;
                    }
    };

}

using namespace screengrab;

int main(int argc, char ** argv) {
        // TODO OUTPUT_DIR should come from a config file
        boost::filesystem::create_directories(OUTPUT_DIR);

        KeyboardGrabber keyboard;

        /* 
         * Connections to the X server are expensive; don't want to keep
         * making new ones, use exactly one grabber for the program
         */
        shared_ptr<ScreenGrabber> screenGrabber(new ScreenGrabber());

        unique_ptr<function<bool()>> screenHandleFunction(new function<bool()>(ScreenGrabHandler(screenGrabber)));

        keyboard.addToHandlers(move(screenHandleFunction),
                                "Print",
                                true, false, false);


        unique_ptr<function<bool()>> quitHandleFunction(new function<bool()>(QuitHandler()));
        keyboard.addToHandlers(move(quitHandleFunction),
                                "q",
                                true, true, false);
        keyboard.mainloop();
        return 0;
}
