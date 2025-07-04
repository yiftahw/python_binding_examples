import geometry2d

p1 = geometry2d.Pose(-10, -10)
p2 = geometry2d.Pose(10, 10)
line = geometry2d.Line(p1, p2)

# should yield something similar to y = 1 * x + 0
print(line.to_string())
