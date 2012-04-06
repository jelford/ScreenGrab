#include "screenshot.hpp"

#include "screengrabber_pimpl.hpp"

using namespace std;
using namespace screengrab;

ScreenGrabber::ScreenGrabber() : _pimpl(new ScreenGrabber_Pimpl())
{
}

ScreenGrabber::~ScreenGrabber()
{
    delete(_pimpl);
}

unique_ptr< vector<unsigned char> > ScreenGrabber::grab_screen() const
{
    return _pimpl->grab_screen();
}

