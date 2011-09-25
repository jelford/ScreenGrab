bin_PROGRAMS = screengrab
AM_CPPFLAGS=$(cairo_DEPS_CFLAGS)
screengrab_LDFLAGS = -lX11 -lboost_filesystem -lboost_system
screengrab_LDADD = $(cairo_DEPS_LIBS)
screengrab_SOURCES = main.cpp 
