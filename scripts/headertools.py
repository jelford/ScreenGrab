from . import FailedException, fail

class HeaderChecker(object):
    def __init__(self, config):
        self.conf = config

    def __call__(self, header_list, message=None):
        for header in header_list:
            if not self.conf.CheckCXXHeader(header):
                fail('!! Could not find header <{header}> !! \n{message}'.format(header=header, message=message or ''))
        
