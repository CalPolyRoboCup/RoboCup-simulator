from LogData import *
from GeometryRenderer import *
from RobotContainer import *
from BallContainer import *
from GUI import *
from SSLClient import *


class Viewer:
    START_OFFSET_SECONDS = 0  # 4500  # For testing
    SCALE_RATE = 1.05
    MIN_SCALE = 0.01
    MAX_SCALE = 1.0

    def __init__(self, title: str, width: int, height: int, background: (int, int, int)):
        """
        Creates a new Viewer instance
        :param log_data: The protobuf log data to view
        :param title: The title of the Viewer's window
        :param size: The window size of the Viewer
        :param background: The background color of the Viewer
        """
        # self.log_data = log_data
        self.client = SSLClient()
        self.title = title
        self.window_width = width
        self.window_height = height
        self.scale = 0.1
        self.background = background
        self._geometry = None
        self.actors = [GeometryRenderer(self), BallContainer(self), RobotContainer(self), GUI(self)]

        # Initialize pygame for rendering
        pygame.init()

        # self.current_time_ns = log_data.packets[0].time_ns + self.START_OFFSET_SECONDS * 1000000000
        # self.last_time = pygame.time.get_ticks()
        # self.packet_id = 0

        # Set the title of the window
        pygame.display.set_caption(self.title)

        # Load the surfaces (images)
        self.screen = pygame.display.set_mode((self.window_width, self.window_height))

        self.client.connect()

    def run(self) -> None:
        """
        Starts the run loop for the viewer
        """
        while True:
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    sys.exit()
                # elif event.type == pygame.MOUSEBUTTONDOWN:
                #     if event.button == 4:
                #         self.scale *= self.SCALE_RATE
                #     elif event.button == 5:
                #         self.scale /= self.SCALE_RATE
                #
                #     self.scale = min(self.MAX_SCALE, max(self.MIN_SCALE, self.scale))

            self.update()
            self.render()

    def update(self) -> None:
        """
        Updates each ball and robot
        """

        # TODO: Change this loop to read from a local network socket instead of the cached file data.

        current_packet = self.client.receive()

        if current_packet is None:
            return

        # while True:
        wrapper_packet = current_packet.wrapper_packet

        # If the packet contains ball and robot positions, update each position
        if wrapper_packet is None:
            return

        for actor in self.actors:
            actor.update(wrapper_packet, 0)

        # If we've gone through all packets leading up to this point in time, finish updating
        self._geometry = current_packet.geometry

        # ticks = pygame.time.get_ticks()
        # time_delta_ms = ticks - self.last_time
        # self.current_time_ns += time_delta_ms * 1000000
        # self.last_time = ticks

        # if self.packet_id >= self.log_data.num_packets:
        #     return

        # Read all the packets leading up to the current time
        # while True:
        #     current_packet = self.log_data.packets[self.packet_id]
        #     wrapper_packet = current_packet.wrapper_packet
        #
        #     # If the packet contains ball and robot positions, update each position
        #     if wrapper_packet is not None:
        #         for actor in self.actors:
        #             actor.update(wrapper_packet, time_delta_ms)
        #
        #         # If we've gone through all packets leading up to this point in time, finish updating
        #         if current_packet.time_ns >= self.current_time_ns:
        #             self._geometry = current_packet.geometry
        #             break
        #
        #     self.packet_id += 1

    def render(self) -> None:
        """
        Render all the balls and robots
        """
        self.screen.fill(self.background)

        if self._geometry is not None:
            for actor in self.actors:
                actor.draw(self._geometry.scale(self.scale))

        # Present the new image to the window
        pygame.display.flip()

    def screen_point(self, x: float, y: float) -> (int, int):
        """
        Converts x and y field coordinates to screen coordinates
        :param x: The x field coordinate
        :param y: The y field coordinate
        :return: A tuple containing the updated x and y positions
        """
        return int(x * self.scale + self.window_width * 0.5), int(y * self.scale + self.window_height * 0.5)

    def screen_scalar(self, value: float) -> int:
        """
        Scales the value field to correspond with screen units
        :param value: The value to scale
        :return: The scaled value
        """
        return int(value * self.scale)

    def set_packet(self, id):
        pass
        # TODO: No longer needed. Delete when you can.
        # self.packet_id = id
        #
        # if self.packet_id < self.log_data.num_packets:
        #     self.current_time_ns = self.log_data.packets[self.packet_id].time_ns
