#include <map>
#include <string>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <assert.h>
#include <memory>

#include "keyboard_pimpl.hpp"

using namespace std;
using namespace screengrab;

KeyCode KeyboardGrabberPimpl::get_keycode_from_string(string key_string) const{
    const char* key = key_string.c_str();
    assert(XStringToKeysym(key) != NoSymbol);
    KeyCode keycode = XKeysymToKeycode(display, XStringToKeysym(key));
    assert(keycode);
    return keycode;
}

bool KeyboardGrabberPimpl::handleKeystroke(int keycode) {
    return (*handlers[keycode])();
}



KeyboardGrabberPimpl::KeyboardGrabberPimpl() {
    // Establish connection to the XServer
    display = XOpenDisplay(NULL);
    assert(display);

    // Get the root window (One Window To Rule Them All
    // (so long as they reside on a given display)
    rootWindow = DefaultRootWindow(display);
}

KeyboardGrabberPimpl::~KeyboardGrabberPimpl()
{
    XFree(display);
}

void KeyboardGrabberPimpl::addToHandlers(unique_ptr< function<bool ()> > handler, string key, bool ctrl, bool alt, bool shift) {
    auto modifierMask = (ctrl ? ControlMask : 0) | (shift ? ShiftMask : 0) | (alt ? Mod1Mask : 0);
    auto keycode = get_keycode_from_string(key);

    // Set up the hook
    XGrabKey(display,
            keycode,
            modifierMask,
            rootWindow,	
            true,			// Pass on events to owner window
            GrabModeAsync, 	 	// Non-blocking
            GrabModeAsync);  	// on both keyboard and pointer


    /* X would like us to be explicit about whether numlock, capslock, or
     * scroll-lock are enabled. This looks like a hack -- there really ought
     * to be a way to specify that we don't care. I haven't found one
     * (patches welcome)
     */
    auto NumLock = Mod2Mask;
    auto ScrollLock = Mod5Mask;

    // CapsLock
    XGrabKey(display, keycode, modifierMask | LockMask, rootWindow, true, GrabModeAsync, GrabModeAsync);
    // NumLock
    XGrabKey(display, keycode, modifierMask | NumLock, rootWindow, true, GrabModeAsync, GrabModeAsync);
    // Scroll Lock
    XGrabKey(display, keycode, modifierMask | ScrollLock, rootWindow, true, GrabModeAsync, GrabModeAsync);
    // Combinations
    XGrabKey(display, keycode, modifierMask | LockMask | NumLock, rootWindow, true, GrabModeAsync, GrabModeAsync);
    XGrabKey(display, keycode, modifierMask | LockMask | ScrollLock, rootWindow, true, GrabModeAsync, GrabModeAsync);
    XGrabKey(display, keycode, modifierMask | NumLock | ScrollLock, rootWindow, true, GrabModeAsync, GrabModeAsync);
    XGrabKey(display, keycode, modifierMask | LockMask | NumLock | ScrollLock, rootWindow, true, GrabModeAsync, GrabModeAsync);

    handlers[keycode] = move(handler);
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
