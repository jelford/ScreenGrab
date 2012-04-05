#ifndef keyboard_HPP
#define keyboard_HPP

#include <boost/function.hpp>
#include <string>

#include "keyboard_pimpl.hpp"

class KeyboardGrabber {
    private:
        KeyboardGrabberPimpl* _pimpl;
    public:
        KeyboardGrabber() : _pimpl(new KeyboardGrabberPimpl()) { }
        virtual ~KeyboardGrabber() { delete(this->_pimpl); }
        void addToHandlers(boost::function<bool ()> &handler, std::string key, bool ctrl, bool alt, bool shift)
        {
            this->_pimpl->addToHandlers(handler, key, ctrl, alt, shift);
        }
        void mainloop()
        {
            this->_pimpl->mainloop();
        }
};

#endif
