#include <boost/function.hpp>
#include <boost/shared_ptr.hpp>
#include <map>

#include <X11/Xlib.h>

class KeyboardGrabber {
	private:
            int get_keycode_from_string(std::string key_string) const;
            Display* display;
            Window rootWindow;
            std::map<int, boost::function<bool ()> > handlers;

	public:
            KeyboardGrabber();
            virtual ~KeyboardGrabber();
            void addToHandlers(boost::function<bool ()> &handler, std::string key, bool ctrl, bool alt, bool shift);
            bool handleKeystroke(int keycode); 
            void mainloop();
};
