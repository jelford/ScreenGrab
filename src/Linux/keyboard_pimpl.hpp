#ifndef keyboard_pimpl_HPP
#define keyboard_pimpl_HPP

#include <map>
#include <X11/Xlib.h>
#include <boost/function.hpp>
#include <string>

class KeyboardGrabberPimpl {
    private:
        int get_keycode_from_string(std::string key_string) const;       
        bool handleKeystroke(int keycode); 
        Display* display;
        Window rootWindow;
        std::map<int, boost::function<bool ()> > handlers;
    
    public:
        KeyboardGrabberPimpl();
        ~KeyboardGrabberPimpl();

        void addToHandlers(boost::function<bool ()> &handler, std::string key, bool ctrl, bool alt, bool shift);
 
        void mainloop();
};
#endif
