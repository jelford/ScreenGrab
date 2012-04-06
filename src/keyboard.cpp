#include <memory>
#include <string>

#include "keyboard.hpp"
#include "keyboard_pimpl.hpp"

using namespace std;
using namespace screengrab;

KeyboardGrabber::KeyboardGrabber() 
    : _pimpl(new KeyboardGrabberPimpl())
{ }

void KeyboardGrabber::mainloop()
{
    _pimpl->mainloop();
}

KeyboardGrabber::~KeyboardGrabber()
{ }

void KeyboardGrabber::addToHandlers(unique_ptr< function<bool ()> > handler, string key, bool ctrl, bool alt, bool shift)
{
    _pimpl->addToHandlers(move(handler), key, ctrl, alt, shift);
}
