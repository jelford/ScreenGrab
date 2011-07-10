#License:

Any intellectual property right associated with the authorship of
the included code are released under the GPLv3.

#Dependencies:

This code is designed to run on an X-Windows system. Nearly every
modern gnu/linux distribution runs with an X-Server and the Cairo
graphics library (which is also a dependency). To compile this
code, you will need to install headers for each of those libraries:

    Fedora:
    sudo yum install cairo-devel
    sudo yum groupinstall "X Development Tools"

Similar commands are available for Debian/Ubuntu users

#Make:

`g++ -o ScreenGrab -lX11 `pkg-config --cflags --libs cairo` main.cpp`

#Run:

 * `./nohup ScreenGrab` to run ScreenGrab
 * `ctrl+prtscn` to Capture a screen shot and save to out.png
 * `ctrl+q` to kill the program

# Future work:

This program is totally unfinished. Improvements will abound.
