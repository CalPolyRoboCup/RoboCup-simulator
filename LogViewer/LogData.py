import gzip
import messages_robocup_ssl_wrapper_legacy_pb2

from struct import *
from Geometry import *


class LogData:
    LOG_HEADER_SIZE = 12
    LOG_HEADER_STR = b'SSL_LOG_FILE'

    def __init__(self):
        """
        Creates a new LogData instance
        """
        self.packets = []
        self.num_packets = 0

    def parse(self, file: gzip.GzipFile) -> None:
        """
        Generates packets from the given gzipped log file
        :param file: The gzip file to parse
        """
        if file.read(self.LOG_HEADER_SIZE) != self.LOG_HEADER_STR:
            raise RuntimeError("Invalid file type")

        vn, = unpack('>I', file.read(4))

        if vn != 1:
            raise RuntimeError("Invalid version number: " + str(vn))

        geometry = Geometry()

        while True:
            # Read the time stamp of the packet
            ts = file.read(8)

            # If the time stamp is empty, we're done parsing the file, so exit the loop
            if not ts:
                break

            # Convert the time stamp tp an integer
            ns, = unpack('>Q', ts)

            # Parse the message type as an integer
            mt, = unpack('>I', file.read(4))

            # Parse the message string
            ms, = unpack('>I', file.read(4))
            mc = file.read(ms)

            if mt != 2:
                continue

            # Construct a new SSLPacket
            ssl_packet = SSLPacket(ns, mt, geometry)

            # Generate the SSLPacket's wrapper packet based on the message type
            if not ssl_packet.gen_wrapper_packet(mc):
                continue

            geometry = ssl_packet.geometry

            self.packets.append(ssl_packet)
            self.num_packets += 1


class SSLPacket:
    def __init__(self, time_ns: int, message_type: int, geometry: Geometry):
        """
        Creates a new SSLPacket instance
        :param time_ns: The time stamp in nanoseconds of the packet
        :param message_type:
        """
        self.time_ns = time_ns
        self.message_type = message_type
        self.wrapper_packet = None
        self.geometry = geometry

    def gen_wrapper_packet(self, message: str) -> bool:
        """
        Generates a wrapper packet from the given message
        :param message: The message as a string
        """
        if self.message_type == 2:
            self.wrapper_packet = messages_robocup_ssl_wrapper_legacy_pb2.SSL_WrapperPacket()
        elif self.message_type == 3:
            # TODO: Implement refbox messages
            return False
        else:
            return False

        self.wrapper_packet.ParseFromString(message)

        # Generate geometry data
        if self.wrapper_packet.geometry is not None:
            self.geometry = Geometry._make([
                getattr(self.wrapper_packet.geometry.field, v) or getattr(self.geometry, v) for
                v in list(self.wrapper_packet.geometry.field.DESCRIPTOR.fields_by_name) if
                v in self.geometry._fields])

        return True
