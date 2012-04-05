
class FailedException(Exception):
    pass

class HeaderChecker(object):
    def __init__(self, config):
        self.conf = config

    def fail(message):
        print(message)
        raise FailedException(message)

    def __call__(self, header_list, message=None):
        for header in header_list:
            if not self.conf.CheckCXXHeader(header):
                fail('!! Could not find header <{header}> !! \n {message} \n Aborting build.'.format(message=message or ''))
        
