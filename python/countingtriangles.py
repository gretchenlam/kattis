def cross_product(p1, p2, p3):
    return ((p2[0] - p1[0]) * (p3[1] - p1[1])) - ((p3[0] - p1[0]) * (p2[1] - p1[1]))

def lines_intersect(s1_p1, s1_p2, s2_p1, s2_p2):
    first_line_endpoint1 = cross_product(s2_p1, s2_p2, s1_p1)
    first_line_endpoint2 = cross_product(s2_p1, s2_p2, s1_p2)
    second_line_endpoint1 = cross_product(s1_p1, s1_p2, s2_p1)
    second_line_endpoint2 = cross_product(s1_p1, s1_p2, s2_p2)

    # if first line endpoints are on opposite sides of second line, vice versa
    if ((first_line_endpoint1 > 0 and first_line_endpoint2 < 0) or (first_line_endpoint1 < 0 and first_line_endpoint2 > 0)) and ((second_line_endpoint1 > 0 and second_line_endpoint2 < 0) or (second_line_endpoint1 < 0 and second_line_endpoint2 > 0)):
        return True
    elif first_line_endpoint1 == 0 and on_segment(s2_p1, s2_p2, s1_p1):
        return True
    elif first_line_endpoint2 == 0 and on_segment(s2_p1, s2_p2, s1_p2):
        return True
    elif second_line_endpoint1 == 0 and on_segment(s1_p1, s1_p2, s2_p1):
        return True
    elif second_line_endpoint2 == 0 and on_segment(s1_p1, s1_p2, s2_p2):
        return True
    return False

def on_segment(p1, p2, q):
    return (min(p1[0], p2[0]) <= q[0] <= max(p1[0], p2[0]) and min(p1[1], p2[1]) <= q[1] <= max(p1[1], p2[1]))


def count_triangles(lines):
    triangle_count = 0
    for i in range(len(lines)):
        for j in range(i + 1, len(lines)):
            for k in range(j + 1, len(lines)):
                if (lines_intersect(lines[i][0], lines[i][1], lines[j][0], lines[j][1]) and lines_intersect(lines[i][0], lines[i][1], lines[k][0], lines[k][1]) and lines_intersect(lines[j][0], lines[j][1], lines[k][0], lines[k][1])):
                    triangle_count += 1
    return triangle_count

while True:
    n = int(input())
    if n == 0:
        exit()

    lines = []
    for _ in range(n):
        x1, y1, x2, y2 = map(float, input().split())
        lines.append(((x1, y1), (x2, y2)))

    triangles = count_triangles(lines)
    print(triangles)