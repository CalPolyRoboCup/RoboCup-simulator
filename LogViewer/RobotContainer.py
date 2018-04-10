import math

from Actor import *
from typing import *
from Robot import *
from messages_robocup_ssl_detection_pb2 import *


class RobotContainer(Actor):
    def __init__(self, viewer):
        """
        Creates a new RobotContainer instance
        :param viewer: The Viewer to be rendered to
        """
        super().__init__(viewer)
        self.robots_yellow = {}
        self.robots_blue = {}
        self.yellow_image = pygame.image.load("images/YellowBot.png")
        self.blue_image = pygame.image.load("images/BlueBot.png")

    def update(self, packet, delta):
        """
        Updates each yellow and blue robot
        :param packet: The packet data used to update the robots
        :param delta: The time since the last update
        """
        self.update_bots(packet.detection.robots_yellow, self.robots_yellow, self.yellow_image, delta)
        self.update_bots(packet.detection.robots_blue, self.robots_blue, self.blue_image, delta)

    def draw(self, geometry):
        """
        Draws each yellow and blue robot
        :param geometry: (unused)
        """
        for r in self.robots_yellow.values():
            r.draw(geometry)

        for r in self.robots_blue.values():
            r.draw(geometry)

    def update_bots(self, detection_bots: List[SSL_DetectionRobot],
                    viewer_bots: Dict[int, Robot], image, delta: int):
        """
        Updates each bot with the provided detection and viewer bots
        :param detection_bots: The SSL bot data
        :param viewer_bots: The bot instances
        :param image: The image associated with the updated bots
        :param delta: The time since the last update
        """
        # Add the delta time to each robot's time since the last update
        for r in viewer_bots.values():
            r.time_since_update += delta

        # Update each robot's position
        for r in detection_bots:
            # Get a robot from the viewer bots or create a new one if it does not exist
            if r.robot_id in viewer_bots.keys():
                robot = viewer_bots[r.robot_id]
            else:
                robot = viewer_bots[r.robot_id] = Robot(self.viewer, image)

            # Update the robot's position and orientation, and reset its time since the last update
            robot.x, robot.y = self.viewer.screen_point(r.x, r.y)
            robot.orientation = math.degrees(-r.orientation)
            robot.time_since_update = 0
