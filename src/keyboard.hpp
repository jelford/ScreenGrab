#ifndef keyboard_HPP
#define keyboard_HPP

#include <string>
#include <memory>

#include "keyboard_pimpl.hpp"

class KeyboardGrabber {
    private:
        std::unique_ptr<KeyboardGrabberPimpl> _pimpl;
    public:
        KeyboardGrabber() : _pimpl(std::unique_ptr<KeyboardGrabberPimpl>(new KeyboardGrabberPimpl())) { }
        virtual ~KeyboardGrabber() { }
        void addToHandlers(std::unique_ptr< std::function<bool ()> > &handler, std::string key, bool ctrl, bool alt, bool shift)
        {
            this->_pimpl->addToHandlers(handler, key, ctrl, alt, shift);
        }
        void mainloop()
        {
            this->_pimpl->mainloop();
        }
};

#endif
