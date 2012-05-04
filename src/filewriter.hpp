#ifndef FILEWRITER_HPP
#define FILEWRITER_HPP

#include <string>

#include <memory>               // std::unique_ptr
#include <vector>               // std::vector<unsigned char> (png data)

// Copying data into a filestream
#include <sstream>
#include <fstream>
#include <ostream>
#include <iterator>

#include <time.h>               // file timestamps
#include <mutex>                // std::lock_guard, std::mutex (naming conflicts)

namespace screengrab
{
    class FileWriter
    {
        private:
            std::shared_ptr<std::mutex> name_finder_lock;
            mutable int _count;

            int count() const 
            {
                // _count++ isn't atomic
                std::lock_guard<std::mutex> lock(*name_finder_lock);
                return _count++;
            }

            std::string next_output_filename() const
            {
                std::stringstream destination;
                // TODO: Should replace OUTPUT_DIR this with a config file!
                destination <<  OUTPUT_DIR;

                destination << "/screengrab_";

                // timestamp
                time_t epoch_time;
                epoch_time = time(NULL);
                destination << epoch_time;
                
                // avoid name conflicts whent he timestamp is the same
                destination << count();

                destination << ".png";
                return destination.str();    
            }

            FileWriter(FileWriter const & other);



        public:
            void dump(std::unique_ptr<std::vector<unsigned char>> png) const
            {
                assert(png);
                std::ofstream outfile(next_output_filename().c_str(), 
                                        std::ios::out | std::ios::binary);
                std::ostream_iterator<unsigned char> file_iterator(outfile, NULL);
                copy(png->begin(), png->end(), file_iterator);

            }

            FileWriter() : _count(0), name_finder_lock(new std::mutex()) { };

            FileWriter(FileWriter && other) : _count(other._count), name_finder_lock(other.name_finder_lock) { }

    };
}
#endif
