import socket
import struct
import gzip
import time
import tkinter
from tkinter import filedialog

LOG_HEADER_SIZE = 12
LOG_HEADER_STR = b'SSL_LOG_FILE'
SLIDER_RESOLUTION = 512


def start() -> None:
    playing = False
    packet_id = 0
    play_start = 0
    data = list()
    data_size = 0

    client_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

    root = tkinter.Tk()
    slider = tkinter.Scale(root, from_=0, to=SLIDER_RESOLUTION, orient=tkinter.HORIZONTAL, length=SLIDER_RESOLUTION,
                           width=24, sliderlength=24, showvalue=0)
    address_entry = tkinter.Entry(root, width=14)
    address_entry.insert(0, "224.5.23.2")
    port_entry = tkinter.Entry(root, width=6)
    port_entry.insert(0, "10020")

    def play(mode):
        nonlocal playing
        nonlocal packet_id
        nonlocal play_start

        if mode is not None:
            playing = mode

            if playing:
                play_start = time.time() - data[0][0]
                packet_id = 0
        if playing:
            if data:
                nonlocal data_size

                if data_size == 0:
                    data_size = len(data)

                if time.time() - play_start >= data[packet_id][0]:
                    client_socket.sendall(data[packet_id][1])
                    slider.set(int(packet_id / data_size * SLIDER_RESOLUTION))
                    packet_id += 1

                root.after(1, lambda: play(None))
            else:
                playing = False

    root.title("LogAssistant - No Log Opened")
    root.resizable(0, 0)

    tkinter.Button(root, text="Open Log File", height=3, command=lambda: open_file(root, data)).pack(side="left")
    slider.pack()
    tkinter.Button(root, text="Play", command=lambda: play(True)).pack(side="left")
    tkinter.Button(root, text="Pause", command=lambda: play(False)).pack(side="left")
    tkinter.Button(root, text="Connect", command=lambda: connect(client_socket, address_entry, port_entry))\
        .pack(side="right")
    port_entry.pack(side="right")
    tkinter.Label(root, text="Port:").pack(side="right")
    address_entry.pack(side="right")
    tkinter.Label(root, text="IP Address:").pack(side="right")

    root.mainloop()


def connect(client_socket, address_entry, port_entry):
    try:
        port = int(port_entry.get())
    except ValueError:
        return

    client_socket.connect((address_entry.get(), port))


def open_file(root, data):
    filename = filedialog.askopenfilename(filetypes=(("Log Files", "*.log.gz"), ("All Files", "*.*")))

    if not filename:
        return

    root.title("LogAssistant - Loading...")
    root.update()

    with gzip.open(filename, 'rb') as file:
        read(file, data)

    root.title("LogAssistant - " + filename)


def read(file, data):
    data.clear()

    if file.read(LOG_HEADER_SIZE) != LOG_HEADER_STR:
        raise RuntimeError("Invalid file type")

    vn, = struct.unpack('>I', file.read(4))

    if vn != 1:
        raise RuntimeError("Invalid version number")

    while True:
        ts = file.read(8)

        if not ts:
            break

        ns, = struct.unpack('>Q', ts)

        mt, = struct.unpack('>I', file.read(4))

        ms, = struct.unpack('>I', file.read(4))

        packet_data = file.read(ms)

        data.append((ns / 1000000000, packet_data))


if __name__ == '__main__':
    start()
