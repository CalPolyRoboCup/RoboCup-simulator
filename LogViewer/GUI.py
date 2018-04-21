from Actor import *
from Slider import *


class GUI(Actor):
    def __init__(self, viewer):
        super().__init__(viewer)
        self.elements = [Slider(viewer)]

    def update(self, packet, delta):
        for e in self.elements:
            e.update(packet, delta)

    def draw(self, geometry):
        for e in self.elements:
            e.draw(geometry)
