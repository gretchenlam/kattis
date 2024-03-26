import math

def dot(a, b):
    return a[0] * b[0] + a[1] * b[1]

def norm(v):
    return (v[0]**2 + v[1]**2)**0.5

def find_smallest_angle(vectors):
    min_angle = 1000000
    min_index = -1  # need to keep track of index of the smallest angle
    for i in range(len(vectors)):
        v1 = vectors[i]
        v2 = vectors[(i + 1) % len(vectors)] 
        cos_theta = dot(v1, v2) / (norm(v1) * norm(v2))
        angle = math.pi - math.acos(cos_theta)
        if angle < min_angle:
            min_angle = angle
            min_index = (i + 1) % len(vectors)  # vertex to cut is after v1
    return min_index, min_angle

def cut_vertex(coords, index):
    return coords[:index] + coords[index+1:]

def vectorize(coords):
    vectors = []
    n = len(coords) 
    for i in range(n):
        x1, y1 = coords[i]
        x2, y2 = coords[(i + 1) % n]
        dx, dy = x2 - x1, y2 - y1
        vectors.append((dx, dy))
    return vectors    

while True:
    coords = []
    arr = [int(i) for i in input().split()]
    if arr[0] == 0:
        break
    for i in range(1, len(arr), 2): #not using arr[0]
        x, y = arr[i], arr[i+1]
        coords.append((x, y))

    while len(coords) > 3:
        vectors = vectorize(coords)
        index_to_cut, smallest_angle_before_cut = find_smallest_angle(vectors)
        new_coords = cut_vertex(coords, index_to_cut)
        new_vectors = vectorize(new_coords)
        _, smallest_angle_after_cut = find_smallest_angle(new_vectors)

        if smallest_angle_after_cut < smallest_angle_before_cut:
            break  # cutting gives even smaller angle, don't cut
        else:
            coords = new_coords # all good to cut

    print(len(coords), end=' ')
    for x, y in coords:
        print(f'{x} {y}', end=' ')
    print()