#include "filewriter.hpp"

// Copying data into a filestream
#include <sstream>
#include <fstream>
#include <ostream>
#include <iterator>

using namespace std;
using namespace screengrab;

int FileWriter::count() const
{
    // _count++ isn't atomic
    lock_guard<std::mutex> lock(*name_finder_lock);
    return _count++;
}

string FileWriter::next_output_filename() const
{
    stringstream destination;
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

void FileWriter::dump(std::unique_ptr<std::vector<unsigned char>> png) const
{
    std::ofstream outfile(next_output_filename().c_str(), 
                            std::ios::out | std::ios::binary);
    std::ostream_iterator<unsigned char> file_iterator(outfile, NULL);
    copy(png->begin(), png->end(), file_iterator);
}


FileWriter::FileWriter() : _count(0), name_finder_lock(new std::mutex())
{ }

