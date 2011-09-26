#include <iostream>
#include <map>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <assert.h>

#include <boost/function.hpp>

#include "keyboard.hpp"

int KeyboardGrabber::get_keycode_from_string(std::string key_string) const{
    const char* key = key_string.c_str();
    assert(XStringToKeysym(key) != NoSymbol);
    int keycode = XKeysymToKeycode(display, XStringToKeysym(key));
    assert(keycode);
    return keycode;
}

KeyboardGrabber::KeyboardGrabber() {
    // Establish connection to the XServer
    display = XOpenDisplay(NULL);
    assert(display);

    // Get the root window (One Window To Rule Them All
    // (so long as they reside on a given display)
    rootWindow = DefaultRootWindow(display);
}

KeyboardGrabber::~KeyboardGrabber() {
    for(std::map<int, boost::function<bool () >* >::iterator it = handlers.begin(); it != handlers.end(); ++it) {
            delete it->second;
    }
}

void KeyboardGrabber::addToHandlers(boost::function<bool ()>* handler, std::string key, bool ctrl, bool alt, bool shift) {
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

bool KeyboardGrabber::handleKeystroke(int keycode) {
    return (handlers[keycode]->operator())();
}

void KeyboardGrabber::mainloop() {
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
