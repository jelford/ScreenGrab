import platform as plat_tools
platform = plat_tools.uname()[0]

from .headertools import HeaderChecker

linux_libs = ['X11', 'cairo']
platform_libs = {'Linux' : linux_libs,}

libs = platform_libs[platform]

linux_headers = ['cairo/cairo-xlib.h', 'X11/Xlib.h']
platform_headers = {'Linux' : linux_headers,}

headers = platform_headers[platform]

def check_headers(conf):
    hCheck = HeaderChecker(conf)
    hCheck(headers, message='Not all platform-specific headers were found; you will need to make sure you have all the dependencies for your platform.')
