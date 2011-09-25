AC_INIT([screen-grab], [0.1], [James Elford <james.elford08@imperial.ac.uk>])
AM_INIT_AUTOMAKE
AC_PROG_CXX
AC_PROG_INSTALL
PKG_CHECK_MODULES([cairo_DEPS], [cairo])
if ! test -v output_dir; then
    output_dir=$HOME/.screengrab/output
fi
AC_ARG_VAR([output_dir], [Set the output directory for screen grabs])
AC_ARG_WITH([boost-libs], 
            [Boost libs path (defaults to -lboost_system -lboost_filesystem)], 
            [BOOST_LIBS="$withval"],
            [BOOST_LIBS="-lboost_system -lboost_filesystem"])
AC_SUBST([BOOST_LIBS])

platform=`uname`
AC_SUBST([platform])

AC_CONFIG_FILES([Makefile src/Makefile src/config.h src/keyboard.hpp])
AC_CONFIG_HEADERS([global_config.h])
AC_OUTPUT

