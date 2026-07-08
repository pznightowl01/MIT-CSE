#Write a Python class named Circle constructed by a radius and two methods
#which will compute the area and the perimeter of a circle.

import math

class Circle:
    def __init__(self, r):
        self.r = r

    def area(self):
        return math.pi * self.r * self.r

    def perimeter(self):
        return 2 * math.pi * self.r


c = Circle(10)
print("circle radius:", c.r)
print("area:", c.area())
print("perimeter:", c.perimeter())
