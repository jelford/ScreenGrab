#ifndef screengrabber_HPP
#define screengrabber_HPP

#include <vector>
#include <boost/shared_ptr.hpp>

class ScreenGrabber {
	public:
                boost::shared_ptr< std::vector<unsigned char> > grab_screen() const; 
};
#endif
