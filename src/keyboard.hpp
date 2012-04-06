#ifndef keyboard_HPP
#define keyboard_HPP

#include <string>
#include <memory>

class KeyboardGrabberPimpl;

class KeyboardGrabber {
    private:
        std::unique_ptr<KeyboardGrabberPimpl> _pimpl;
    public:
        KeyboardGrabber();
        virtual ~KeyboardGrabber();
        void addToHandlers(std::unique_ptr< std::function<bool ()> > handler, std::string key, bool ctrl, bool alt, bool shift);
        void mainloop();
};

#endif
