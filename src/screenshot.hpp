#ifndef screengrabber_HPP
#define screengrabber_HPP

#include <vector>
#include <memory>

class ScreenGrabber {
	public:
                std::shared_ptr< std::vector<unsigned char> > grab_screen() const; 
};
#endif
