from abc import *


class Actor(ABC):
    """
    An abstract base class for everything updated by the viewer
    """
    def __init__(self, viewer):
        self._viewer = viewer

    @abstractmethod
    def update(self, packet, delta):
        """
        Called when the Actor is updated
        :param packet: The most up-to-date packet
        :param delta: The time since the last update
        """
        pass

    @abstractmethod
    def draw(self, geometry):
        """
        Draws the Actor to the Viewer
        :param geometry: The most up-to-date field geometry
        """
        pass

    def _get_viewer(self):
        return self._viewer

    viewer = property(_get_viewer)
