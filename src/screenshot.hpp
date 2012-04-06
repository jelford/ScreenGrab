#ifndef screengrabber_HPP
#define screengrabber_HPP

#include <vector>
#include <memory>

class ScreenGrabber_Pimpl;

class ScreenGrabber {
    private:
        ScreenGrabber_Pimpl* _pimpl;
        ScreenGrabber(ScreenGrabber const &);
        ScreenGrabber& operator=(ScreenGrabber const &);
	public:
        std::unique_ptr< std::vector<unsigned char> > grab_screen() const; 
        ScreenGrabber();
        virtual ~ScreenGrabber();
                
};
#endif
