#ifndef cairo_helper_HPP
#define cairo_helper_HPP

#include <vector>
#include <cairo/cairo.h>
#include <boost/shared_ptr.hpp>

namespace cairo_helpers {

    cairo_status_t write_png_stream_to_byte_array(void *in_closure, const unsigned char* data, unsigned int length) {
        boost::shared_ptr< std::vector<unsigned char> >* closure = (boost::shared_ptr< std::vector<unsigned char> > *) in_closure;
        closure->get()->insert(closure->get()->end(), data, data + length);
        return CAIRO_STATUS_SUCCESS;
    }

    boost::shared_ptr< std::vector<unsigned char> > cairo_to_mem_png(cairo_surface_t* surface) {
        boost::shared_ptr< std::vector<unsigned char> >  out_vector(new std::vector<unsigned char>());
        cairo_surface_write_to_png_stream(surface, write_png_stream_to_byte_array, &out_vector);
        return out_vector;
    }
}

#endif
