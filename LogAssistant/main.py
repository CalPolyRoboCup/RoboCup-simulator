import socket
import sys
import struct
import gzip
import time

LOG_HEADER_SIZE = 12
LOG_HEADER_STR = b'SSL_LOG_FILE'


def start() -> None:
    address = ("224.5.23.2", 10020)
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    client_socket.connect(address)

    """
    Loads the log file given via the command line arguments, and starts the log viewer
    """
    if len(sys.argv) < 2:
        return

    with gzip.open(sys.argv[1], 'rb') as file:
        data = read(file)

    send(data, client_socket)


def read(file):
    if file.read(LOG_HEADER_SIZE) != LOG_HEADER_STR:
        raise RuntimeError("Invalid file type")

    vn, = struct.unpack('>I', file.read(4))

    if vn != 1:
        raise RuntimeError("Invalid version number")

    data = list()

    while True:
        ts = file.read(8)

        if not ts:
            break

        ns, = struct.unpack('>Q', ts)

        mt, = struct.unpack('>I', file.read(4))

        ms, = struct.unpack('>I', file.read(4))

        packet_data = file.read(ms)

        data.append((ns / 1000000000, packet_data))

    return data


def send(data, client_socket):
    sender_start = time.time() - data[50000][0]

    for packet in data[50000:]:
        while time.time() - sender_start < packet[0]:
            pass

        client_socket.sendall(packet[1])


if __name__ == '__main__':
    start()
