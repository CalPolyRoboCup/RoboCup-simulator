from Actor import *


class ScreenActor(Actor):
    """
    Used to represent Actors visualized on the screen
    """
    def __init__(self, viewer, radius: int, x=0, y=0):
        """
        Creates a new ScreenActor instance
        :param viewer: The Viewer to be rendered to
        :param radius: The radius of the actor
        :param x: The x position of the actor
        :param y: The y position of the actor
        """
        super().__init__(viewer)
        self.radius = radius
        self.x = x
        self.y = y

    @abstractmethod
    def update(self, packet, delta):
        pass

    @abstractmethod
    def draw(self, geometry):
        pass

    def _get_radius(self) -> int:
        return self._radius

    def _set_radius(self, radius: int):
        if radius <= 0:
            raise ValueError('Radius must be nonzero')

        self._radius = radius

    def _get_x(self) -> int:
        return self._x

    def _set_x(self, x: int):
        self._x = x

    def _get_y(self) -> int:
        return self._y

    def _set_y(self, y: int):
        self._y = y

    radius = property(_get_radius, _set_radius)
    x = property(_get_x, _set_x)
    y = property(_get_y, _set_y)
