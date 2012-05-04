#ifndef FILEWRITER_HPP
#define FILEWRITER_HPP

#include <string>

#include <memory>               // std::unique_ptr
#include <vector>               // std::vector<unsigned char> (png data)

#include <time.h>               // file timestamps
#include <mutex>                // std::lock_guard, std::mutex (naming conflicts)

namespace screengrab
{
    class FileWriter
    {
        private:
            std::shared_ptr<std::mutex> name_finder_lock;
            mutable int _count;

            int count() const;
            
            std::string next_output_filename() const;
            
            FileWriter(FileWriter const & other);



        public:
            void dump(std::unique_ptr<std::vector<unsigned char>> png) const;

            FileWriter(); 

            FileWriter(FileWriter && other);

    };
}
#endif
