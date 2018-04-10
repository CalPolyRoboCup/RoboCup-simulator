from Actor import *
import pygame


class GeometryRenderer(Actor):
    """
    Used for rendering field geometry
    """
    LINE_COLOR = (255, 255, 255)

    def __init__(self, viewer):
        """
        Creates a new GeometryRenderer instance
        :param viewer: The Viewer to be rendered to
        """
        super().__init__(viewer)

    def update(self, packet, delta):
        pass

    def draw(self, geometry):
        """
        Draws the field based on the given geometry
        :param geometry: The geometry by which to render the field
        """
        if geometry is None:
            return

        thickness = max(1, geometry.line_width)

        field_rect = pygame.Rect((self.viewer.window_width - geometry.field_length) // 2,
                                 (self.viewer.window_height - geometry.field_width) // 2,
                                 geometry.field_length, geometry.field_width)
        boundary_rect = field_rect.inflate(geometry.boundary_width, geometry.boundary_width)
        goal_rect = pygame.Rect(field_rect.x - geometry.goal_depth,
                                self.viewer.window_height // 2 - geometry.goal_width // 2,
                                geometry.goal_depth, geometry.goal_width)

        pygame.draw.rect(self.viewer.screen, (0, 127, 0), boundary_rect, 0)
        pygame.draw.rect(self.viewer.screen, self.LINE_COLOR, field_rect, thickness)
        pygame.draw.rect(self.viewer.screen, self.LINE_COLOR, goal_rect, thickness)
        goal_rect.x = field_rect.x + field_rect.width
        pygame.draw.rect(self.viewer.screen, self.LINE_COLOR, goal_rect, thickness)
        pygame.draw.line(self.viewer.screen, self.LINE_COLOR,
                         (field_rect.x, self.viewer.window_height // 2),
                         (field_rect.x + field_rect.width, self.viewer.window_height // 2))
        pygame.draw.line(self.viewer.screen, self.LINE_COLOR,
                         (self.viewer.window_width // 2, field_rect.y),
                         (self.viewer.window_width // 2, field_rect.y + field_rect.height))
        pygame.draw.circle(self.viewer.screen, self.LINE_COLOR,
                           (self.viewer.window_width // 2, self.viewer.window_height // 2),
                           geometry.center_circle_radius, thickness)
