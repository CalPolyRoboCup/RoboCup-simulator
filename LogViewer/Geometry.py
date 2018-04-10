from collections import namedtuple

GeometryBase = namedtuple('Geometry',
                          ['line_width',
                           'field_length',
                           'field_width',
                           'boundary_width',
                           'goal_width',
                           'goal_depth',
                           'goal_wall_width',
                           'center_circle_radius',
                           'defense_radius'])


class Geometry(GeometryBase):
    """
    Used for storing field geometry
    """
    def scale(self, factor):
        """
        Scales each property by the given factor
        :param factor: The factor by which to scale the fields of this Geometry instance
        :return:
        """
        return Geometry._make([max(0, int(v * factor)) for v in self])


# Allow creation of a Geometry instance without parameters
Geometry.__new__.__defaults__ = (10, 9000, 6000, 300, 1000, 300, 10, 500, 1000)  # (0,) * len(Geometry._fields)
