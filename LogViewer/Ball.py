import pygame
from ScreenActor import *


class Ball(ScreenActor):
    DETECTION_TIMEOUT_MS = 750

    def __init__(self, viewer, x=0, y=0):
        """
        Creates a new Ball instance
        :param viewer: The viewer to be rendered to
        :param x: The Ball's X position
        :param y: The Ball's Y position
        """
        super().__init__(viewer, 22, x, y)
        self.time_since_update = 0

    def update(self, packet, delta):
        pass

    def draw(self, geometry):
        """
        Renders the Ball to the Viewer
        :param geometry: (unused)
        """
        pygame.draw.circle(self.viewer.screen, (255, 127, 0), self.viewer.screen_point(self.x, self.y),
                           self.viewer.screen_scalar(self.radius), 0)
