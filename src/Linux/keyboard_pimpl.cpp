#include <iostream>
#include <map>
#include <string>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <assert.h>
#include <boost/function.hpp>

#include "keyboard_pimpl.hpp"

int KeyboardGrabberPimpl::get_keycode_from_string(std::string key_string) const{
    const char* key = key_string.c_str();
    assert(XStringToKeysym(key) != NoSymbol);
    int keycode = XKeysymToKeycode(display, XStringToKeysym(key));
    assert(keycode);
    return keycode;
}

bool KeyboardGrabberPimpl::handleKeystroke(int keycode) {
    return handlers[keycode]();
}

KeyboardGrabberPimpl::KeyboardGrabberPimpl() {
    // Establish connection to the XServer
    display = XOpenDisplay(NULL);
    assert(display);

    // Get the root window (One Window To Rule Them All
    // (so long as they reside on a given display)
    rootWindow = DefaultRootWindow(display);
}

KeyboardGrabberPimpl::~KeyboardGrabberPimpl(){}

void KeyboardGrabberPimpl::addToHandlers(boost::function<bool ()> &handler, std::string key, bool ctrl, bool alt, bool shift) {
    unsigned int modifierMask = (ctrl ? ControlMask : 0) | (shift ? ShiftMask : 0) | (alt ? Mod1Mask : 0);
    int keycode = get_keycode_from_string(key);

    // Set up the hook
    XGrabKey(display,
            keycode,
            modifierMask,
            rootWindow,	
            true,			// Pass on events to owner window
            GrabModeAsync, 	 	// Non-blocking
            GrabModeAsync);  	// on both keyboard and pointer
    // Then we do the same again, allowing for Numlock/Capslock (X distinguishes)
    XGrabKey(display, keycode, modifierMask | LockMask, rootWindow, true, GrabModeAsync, GrabModeAsync);
    handlers[keycode] = handler;
}

void KeyboardGrabberPimpl::mainloop() {
    // Let X know we'd like to actually receive our keyboard events please
    XSelectInput(display, rootWindow, KeyPressMask);

    // Enter the main loop listening for events!
    XEvent event;
    for(bool shouldContinue = true; shouldContinue;) {
            XNextEvent(display, &event);
            switch(event.type) {
                    case KeyPress:
                            shouldContinue = handleKeystroke(event.xkey.keycode);
                            break;
                    default:
                            break;
            }
    }

    return;
}
