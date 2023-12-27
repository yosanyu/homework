MAX_BYTES = 1024


# static class
class Argument:
    def __init__(self):
        pass

    @staticmethod
    def get_address(args):
        return tuple((args.host, args.p))

    @staticmethod
    def get_username(args):
        return args.u

    @staticmethod
    def get_max_bytes():
        return MAX_BYTES

