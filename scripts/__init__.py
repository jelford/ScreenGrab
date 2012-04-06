def fail(message):
        print('!'*36 + ' FAIL ' + '!'*36)
        print(message)
        print('!'*36 + ' FAIL ' + '!'*36)
        raise FailedException(message)

class FailedException(Exception):
    pass

