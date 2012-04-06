from . import FailedException, fail

class LibChecker(object):
    def __init__(self, config):
        self.conf = config

    
    def __call__(self, lib_list, message=None):
        for lib in lib_list:
            if not self.conf.CheckLib(lib):
                fail('!! Could not find header <{lib}> !! \n{message}'.format(lib=lib, message=message or ''))
