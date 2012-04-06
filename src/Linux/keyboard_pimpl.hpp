#ifndef keyboard_pimpl_HPP
#define keyboard_pimpl_HPP

#include <map>
#include <X11/Xlib.h>
#include <string>
#include <memory>

class KeyboardGrabberPimpl {
    private:
        KeyCode get_keycode_from_string(std::string key_string) const;       
        bool handleKeystroke(int keycode); 
        Window rootWindow;
        Display* display;
        std::map<int, std::unique_ptr<std::function<bool ()> > > handlers;
    
    public:
        KeyboardGrabberPimpl();
        virtual ~KeyboardGrabberPimpl();

        void addToHandlers(std::unique_ptr< std::function<bool ()> > handler, std::string key, bool ctrl, bool alt, bool shift);
 
        void mainloop();
};
#endif
