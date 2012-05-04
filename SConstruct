import platform
import os
target_platform = platform.uname()[0]
print(target_platform)

from scripts import platform_specific, headertools, libtools


env = Environment()
env.Append(CCFLAGS = ['--std=c++0x'])

cross_platform_libs = ['boost_system-mt', 'boost_filesystem-mt', 'boost_thread-mt']
cross_platform_headers = ['boost/filesystem.hpp', 'boost/thread.hpp', 'thread', 'memory']

if not env.GetOption('clean'):
    conf = Configure(env)

    # Check we will be able to build anything
    if not conf.CheckCXX():
        fail('!! Your compiler and/or environment is not correctly configured !!')

    hCheck = headertools.HeaderChecker(conf)

    hCheck(cross_platform_headers,
        message='ScreenGrab requires boost development headers and c++0x (c++11) to build')
    
    lCheck = libtools.LibChecker(conf)
    
    lCheck(cross_platform_libs, 'ScreenGrab requires BOOST shared libraries to link properly')

    platform_specific.check_headers(conf)
    platform_specific.check_libs(conf)

    env = conf.Finish()
    # Finish checks

    output_dir = ARGUMENTS.get('output-dir', os.path.join(os.environ['HOME'], '.screengrab', 'output'))
    if output_dir not in ARGUMENTS and 'interactive' in ARGUMENTS:
        output_dir = raw_input('Please specify screen-grab output directory: ')
        
    env.Append(CPPDEFINES = {'OUTPUT_DIR': '\\"{output_dir}\\"'.format(output_dir=output_dir)})
    env.Append(CXXFLAGS = ['-O3'])

sources = [x.format(platform=target_platform) for x in ['main.cpp', 'keyboard.cpp', 'filewriter.cpp', '{platform}/keyboard_pimpl.cpp', 'screenshot.cpp', '{platform}/screengrabber_pimpl.cpp']]


platform_libs = platform_specific.libs

SConscript('src/SConscript.py',
    variant_dir='build',
    duplicate=1, 
    exports=['env', 'sources', 'cross_platform_libs', 'platform_libs', 'target_platform'])
