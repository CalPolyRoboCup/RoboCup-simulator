from Viewer import *


def start() -> None:
    """
    Loads the log file given via the command line arguments, and starts the log viewer
    """
    if len(sys.argv) < 2:
        return

    with gzip.open(sys.argv[1], 'rb') as file:
        ld = LogData()
        ld.parse(file)

    viewer = Viewer(ld, "RoboCup SSL Log Viewer", (1040, 740), (0, 0, 0))
    viewer.run()


if __name__ == '__main__':
    start()
