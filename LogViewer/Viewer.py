import pygame
import math

from typing import *
from LogData import *
from messages_robocup_ssl_detection_pb2 import *

# TODO: Fix the scaling now that you've got the packet versioning issue fixed.


class Robot:
    DETECTION_TIMEOUT_MS = 500

    def __init__(self):
        """
        Creates a new Robot instance
        """
        self.position = (0.0, 0.0)
        self.orientation = 0.0
        self.time_since_update = 0


class Ball:
    DETECTION_TIMEOUT_MS = 750

    def __init__(self, x: float, y: float):
        """
        Creates a new Ball instance
        :param x: The Ball's x position
        :param y: The Ball's y position
        """
        self.x = x
        self.y = y
        self.time_since_update = 0


class Viewer:
    START_OFFSET_SECONDS = 300  # For testing

    def __init__(self, log_data: LogData, title: str, size: (int, int), background: (int, int, int)):
        """
        Creates a new Viewer instance
        :param log_data: The protobuf log data to view
        :param title: The title of the Viewer's window
        :param size: The window size of the Viewer
        :param background: The background color of the Viewer
        """
        self.log_data = log_data
        self.title = title
        self.size = size
        self.background = background
        self.yellow_bots = {}
        self.blue_bots = {}
        self.balls = []

        # Initialize pygame for rendering
        pygame.init()

        self.current_time_ns = log_data.packets[0].time_ns + self.START_OFFSET_SECONDS * 1000000000
        self.last_time = pygame.time.get_ticks()
        self.packet_id = 0

        # Set the title of the window
        pygame.display.set_caption(self.title)

        # Load the surfaces (images)
        self.screen = pygame.display.set_mode(self.size)
        self.field = pygame.image.load("images/Field.png")
        self.yellow_bot = pygame.image.load("images/YellowBot.png")
        self.blue_bot = pygame.image.load("images/BlueBot.png")

    def run(self) -> None:
        """
        Starts the run loop for the viewer
        """
        while True:
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    sys.exit()

            self.update()
            self.render()

    def update(self) -> None:
        """
        Updates each ball and robot
        """
        ticks = pygame.time.get_ticks()
        time_delta_ms = ticks - self.last_time
        self.current_time_ns += time_delta_ms * 1000000
        self.last_time = ticks

        def update_balls(detection_balls: List[SSL_DetectionBall], viewer_balls: List[Ball]) -> None:
            """
            Updates the positions of the viewer balls from the detection balls provided
            :param detection_balls: The detection balls from which to update the viewer balls
            :param viewer_balls: The viewer balls to update
            """

            # Remove any balls that aren't being detected anymore
            for b in viewer_balls:
                b.time_since_update += time_delta_ms

            viewer_balls[:] = [b for b in viewer_balls if b.time_since_update < Ball.DETECTION_TIMEOUT_MS]
            remaining_balls = viewer_balls[:]

            # Update the positions of the remaining balls
            for db in detection_balls:
                ball = None
                smallest_distance = math.inf

                # Find the closest viewer ball to the current detection ball, if it exists
                for vb in remaining_balls:
                    distance = math.sqrt(math.pow(vb.x - db.x, 2) + math.pow(vb.y - db.y, 2))
                    if distance < smallest_distance:
                        ball = vb
                        smallest_distance = distance

                # If there aren't any viewer balls found, add a new one, otherwise update the closest ball
                if ball is None:
                    viewer_balls.append(Ball(db.x, db.y))
                else:
                    remaining_balls.remove(ball)
                    ball.x = db.x
                    ball.y = db.y
                    ball.time_since_update = 0

        def update_bots(detection_bots: List[SSL_DetectionRobot], viewer_bots: Dict[int, Robot]) -> None:
            """
            Updates the positions of the viewer robots from the detection robots provided
            :param detection_bots: The detection bots from which to update the viewer bots
            :param viewer_bots: THe viewer bots to update
            """

            # Add the delta time to each robot's time since the last update
            for r in viewer_bots.values():
                r.time_since_update += time_delta_ms

            # Update each robot's position
            for r in detection_bots:
                # Get a robot from the viewer bots or create a new one if it does not exist
                if r.robot_id in viewer_bots.keys():
                    robot = viewer_bots[r.robot_id]
                else:
                    robot = viewer_bots[r.robot_id] = Robot()

                # Update the robot's position and orientation, and reset its time since the last update
                robot.position = self.to_screen(r.x, r.y)
                robot.orientation = math.degrees(-r.orientation)
                robot.time_since_update = 0

        # Read all the packets leading up to the current time
        while True:
            current_packet = self.log_data.packets[self.packet_id]
            wrapper_packet = current_packet.wrapper_packet

            # If the packet contains ball and robot positions, update each position
            if wrapper_packet is not None:
                update_balls(current_packet.wrapper_packet.detection.balls, self.balls)
                update_bots(current_packet.wrapper_packet.detection.robots_yellow, self.yellow_bots)
                update_bots(current_packet.wrapper_packet.detection.robots_blue, self.blue_bots)

                # If we've gone through all packets leading up to this point in time, finish updating
                if current_packet.time_ns >= self.current_time_ns:
                    break

            self.packet_id += 1

    def render(self) -> None:
        """
        Render all the balls and robots
        """
        self.screen.fill(self.background)
        self.screen.blit(self.field, self.field.get_rect())  # TODO: Render without an image like this

        # Render each ball
        for b in self.balls:
            pygame.draw.circle(self.screen, (255, 127, 0), self.to_screen(b.x, b.y), 4, 4)

        def render_bots(bot_image: pygame.Surface, viewer_bots: ValuesView[Robot]):
            """
            Render each bot provided with the provided image
            :param bot_image: The bot image to render
            :param viewer_bots: The bots to render
            """
            for r in viewer_bots:
                # If this robot hasn't been updated in a while, skip it
                if r.time_since_update > Robot.DETECTION_TIMEOUT_MS:
                    continue

                # Render the robot
                rect = bot_image.get_rect().move(r.position)
                rect = rect.move((-rect.width / 2, -rect.height / 2))
                self.screen.blit(pygame.transform.rotate(bot_image, r.orientation), rect)

        # Render the yellow and blue robots
        render_bots(self.yellow_bot, self.yellow_bots.values())
        render_bots(self.blue_bot, self.blue_bots.values())

        # Present the new image to the window
        pygame.display.flip()

    def to_screen(self, x: float, y: float) -> (int, int):
        """
        Converts x and y field coordinates to screen coordinates
        :param x: The x field coordinate
        :param y: The y field coordinate
        :return: A tuple containing the updated x and y positions
        """
        #  return int(x / self.log_data.field_length * self.size[0]), int(y / self.log_data.field_width * self.size[1])
        return int(x * 0.1 + self.size[0] * 0.5), int(y * 0.1 + self.size[1] * 0.5)
