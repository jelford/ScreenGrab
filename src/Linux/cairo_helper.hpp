#ifndef cairo_helper_HPP
#define cairo_helper_HPP

#include <vector>
#include <cairo/cairo.h>
#include <memory>

namespace cairo_helpers {

    cairo_status_t write_png_stream_to_byte_array(void *in_closure, const unsigned char* data, unsigned int length) {
        std::vector<unsigned char>* closure = static_cast<std::vector<unsigned char>*>(in_closure);
        closure->insert(closure->end(), data, data + length);
        return CAIRO_STATUS_SUCCESS;
    }

    std::unique_ptr< std::vector<unsigned char> > cairo_to_mem_png(cairo_surface_t* surface) {
        std::vector<unsigned char>* out_vector = new std::vector<unsigned char>();
        cairo_surface_write_to_png_stream(surface, write_png_stream_to_byte_array, out_vector);
        std::unique_ptr< std::vector<unsigned char> > out(out_vector);
        return out;
    }
}

#endif
