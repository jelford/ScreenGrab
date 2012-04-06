#ifndef SCREENGRABBER_PIMPL_HPP
#define SCREENGRABBER_PIMPL_HPP

#include <memory>
#include <vector>

#include <X11/Xlib.h>

namespace screengrab
{
    class ScreenGrabber_Pimpl
    {
        private:
            Display* display;
            Window rootWindow;
            ScreenGrabber_Pimpl(ScreenGrabber_Pimpl const &);
            ScreenGrabber_Pimpl& operator=(ScreenGrabber_Pimpl const &);

        public:
            ScreenGrabber_Pimpl();
            virtual ~ScreenGrabber_Pimpl();
            std::unique_ptr<std::vector<unsigned char>> grab_screen();
    };
}

#endif
