bin_PROGRAMS = screengrab
AM_CPPFLAGS=$(cairo_DEPS_CFLAGS)
screengrab_LDFLAGS = -lX11 $(BOOST_LIBS)
screengrab_LDADD = $(cairo_DEPS_LIBS)
screengrab_SOURCES = main.cpp $(platform)/screenshot.cpp $(platform)/keyboard.cpp
