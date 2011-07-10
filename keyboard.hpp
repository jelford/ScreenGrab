#include <iostream>
#include <map>
#include <functional>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <assert.h>

template <typename ReturnType>
struct Functor { 
	public:
		virtual ReturnType operator()(void)=0;
};

template <typename T, typename ReturnType>
struct Functor_impl : public Functor<ReturnType> {
	private:
		T* wrapped_object;
	public:
		ReturnType operator()(void) {
			return (wrapped_object->operator())();
		}

		T* get_wrapped() {
			return wrapped_object;
		}

		Functor_impl(T* object) : wrapped_object(object) { }
};

class KeyboardGrabber {
	private:
		int get_keycode_from_string(std::string key_string) {
			const char* key = key_string.c_str();
			assert(XStringToKeysym(key) != NoSymbol);
			int keycode = XKeysymToKeycode(display, XStringToKeysym(key));
			assert(keycode);
			return keycode;
		}

		Display* display;
		Window rootWindow;
		bool ctrl, meta, alt, shift;
		std::map<int, Functor<bool>* > handlers;

	public:

	KeyboardGrabber() {
		// Establish connection to the XServer
		display = XOpenDisplay(NULL);
		assert(display);

		// Get the root window (One Window To Rule Them All
		// (so long as they reside on a given display)
		rootWindow = DefaultRootWindow(display);
	}

	~KeyboardGrabber() {
		for(std::map<int, Functor<bool>*>::iterator it = handlers.begin(); it != handlers.end(); ++it) {
			delete it->second;
		}
	}

	template <typename T>
	void addToHandlers(T* handler, std::string key, bool ctrl, bool meta, bool alt, bool shift)
	{
		Functor<bool>* wrapped_handler = new Functor_impl<T, bool>(handler);

		unsigned int modifierMask = (ctrl ? ControlMask : 0) | (shift ? ShiftMask : 0);
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
		handlers[keycode] = wrapped_handler;
	}

	void mainloop() 
	{
		// Let X know we'd like to actually receive our keyboard events please
		XSelectInput(display, rootWindow, KeyPressMask);

		// Enter the main loop listening for events!
		XEvent event;
		for(bool shouldContinue = true; shouldContinue;) {
			XNextEvent(display, &event);
			switch(event.type) {
				case KeyPress:
					shouldContinue = (handlers[event.xkey.keycode]->operator())();
					break;
				default:
					break;
			}
		}

		return;
	}
};
