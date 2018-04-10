import math
from Actor import *
from Ball import *


class BallContainer(Actor):
    """
    Used to track, manage, update, and render Ball instances
    """
    def __init__(self, viewer):
        """
        Creates a new BallContainer instance
        :param viewer: The Viewer to be rendered to
        """
        super().__init__(viewer)
        self.balls = []

    def update(self, packet, delta):
        """
        Updates each ball
        :param packet: The most up-to-date SSLPacket
        :param delta: The time since the last update
        """
        # Remove any balls that aren't being detected anymore
        for b in self.balls:
            b.time_since_update += delta

        self.balls[:] = [b for b in self.balls if b.time_since_update < Ball.DETECTION_TIMEOUT_MS]
        remaining_balls = self.balls[:]

        # Update the positions of the remaining balls
        for db in packet.detection.balls:
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
                self.balls.append(Ball(self.viewer, db.x, db.y))
            else:
                remaining_balls.remove(ball)
                ball.x = db.x
                ball.y = db.y
                ball.time_since_update = 0

    def draw(self, geometry):
        """
        Renders each ball
        :param geometry: (unused)
        """
        for b in self.balls:
            b.draw(geometry)
