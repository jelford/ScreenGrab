#include "keyboard.hpp"
#include "keyboard_pimpl.hpp"

KeyboardGrabber::KeyboardGrabber() {
    _pimpl = new KeyboardGrabberPimpl();
}

KeyboardGrabber::~KeyboardGrabber() {
    delete _pimpl;
}

void KeyboardGrabber::addToHandlers(boost::function< bool() > &handler, std::string key, bool ctrl, bool alt, bool shift) {
    _pimpl->addToHandlers(handler, key, ctrl, alt, shift);
}

void KeyboardGrabber::mainloop() {
    _pimpl->mainloop();
}
