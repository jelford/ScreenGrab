#ifndef keyboard_HPP
#define keyboard_HPP

#include <boost/function.hpp>
#include <string>

#include "keyboard_pimpl.hpp"

class KeyboardGrabber {
    private:
        KeyboardGrabberPimpl* _pimpl;
    public:
        KeyboardGrabber();
        virtual ~KeyboardGrabber();
        void addToHandlers(boost::function<bool ()> &handler, std::string key, bool ctrl, bool alt, bool shift);
        void mainloop();
};

#endif
