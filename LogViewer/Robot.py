import pygame
from ScreenActor import *


class Robot(ScreenActor):
    DETECTION_TIMEOUT_MS = 500

    def __init__(self, viewer, image):
        """
        Creates a new Robot instance
        :param viewer: The Viewer to be rendered to
        :param image: The image to render to the Viewer
        """
        super().__init__(viewer, 90)
        self.time_since_update = 0
        self.image = image
        self.orientation = 0

    def update(self, packet, delta):
        pass

    def draw(self, geometry):
        """
        Render the bot
        :param geometry: (unused)
        """
        if self.time_since_update > self.DETECTION_TIMEOUT_MS:
            return

        scaled_radius = max(1, self.viewer.screen_scalar(self.radius))

        # Render the robot
        surface = pygame.transform.scale(self.image, (scaled_radius * 2, scaled_radius * 2))
        rect = surface.get_rect().move((self.x, self.y))
        rect = rect.move((-rect.width / 2, -rect.height / 2))

        surface = pygame.transform.rotate(surface, self.orientation)
        self.viewer.screen.blit(surface, rect)
