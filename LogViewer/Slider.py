import pygame

from UIRect import *


class Slider(Actor):
    SLIDER_PADDING_H = 32
    SLIDER_PADDING_V = 32
    SLIDER_THICKNESS = 8
    OUTLINE_PADDING = 2
    THUMB_WIDTH = 12
    THUMB_HEIGHT = 24

    def __init__(self, viewer):
        super().__init__(viewer)
        self.slider_bar = UIRect(viewer, self.SLIDER_PADDING_H, self.SLIDER_PADDING_V,
                                 self.viewer.window_width - self.SLIDER_PADDING_H * 2,
                                 self.SLIDER_THICKNESS, self.OUTLINE_PADDING, (127, 127, 255))
        self.thumb = UIRect(viewer, self.SLIDER_PADDING_H,
                            self.SLIDER_PADDING_V - self.THUMB_HEIGHT // 2 + self.SLIDER_THICKNESS // 2,
                            self.THUMB_WIDTH, self.THUMB_HEIGHT, self.OUTLINE_PADDING, (191, 191, 255))
        self.elements = [self.slider_bar, self.thumb]
        self.sliding = False

    def update(self, packet, delta):
        pass

    def draw(self, geometry):
        if self.sliding:
            if pygame.mouse.get_pressed()[0]:
                self.thumb.x = min(max(pygame.mouse.get_pos()[0] - self.THUMB_WIDTH // 2, self.SLIDER_PADDING_H),
                                   self.viewer.window_width - self.SLIDER_PADDING_H)
            else:
                self.sliding = False
                self.viewer.set_packet(int((self.thumb.x - self.SLIDER_PADDING_H) /
                                           (self.viewer.window_width - self.SLIDER_PADDING_H * 2) *
                                           self.viewer.log_data.num_packets))
        elif (self.thumb.mouse_hover() or self.slider_bar.mouse_hover()) and pygame.mouse.get_pressed()[0]:
            self.sliding = True
        else:
            self.thumb.x = self.SLIDER_PADDING_H + int(self.viewer.packet_id / self.viewer.log_data.num_packets *
                                                       (self.viewer.window_width - self.SLIDER_PADDING_H * 2))
        for e in self.elements:
            e.draw(geometry)
