import pygame
from ScreenActor import *
import math


class UIRect(ScreenActor):
    def __init__(self, viewer, x, y, width, height, padding, color):
        super().__init__(viewer, int(math.sqrt(width ** 2 + height ** 2)) // 2, x, y)
        self.padding = padding
        self.color = color
        self.outline = pygame.Rect(x, y, width, height)

    def update(self, packet, delta):
        pass

    def draw(self, geometry):
        self.outline.x, self.outline.y = self.x, self.y
        pygame.draw.rect(self.viewer.screen, (0, 0, 0), self.outline, 0)
        pygame.draw.rect(self.viewer.screen, self.color, self.outline.inflate(-self.padding, -self.padding), 0)

    def mouse_hover(self):
        mx, my = pygame.mouse.get_pos()
        return mx >= self.x and my >= self.y and mx < self.x + self.outline.width and my < self.y + self.outline.height
