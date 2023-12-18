import sys
import json
import itertools

perimeter, vertices = int(sys.argv[1]), json.loads(sys.argv[2].replace("(", "[").replace(")", "]"))

def area(perimeter, vertices):
    m1 =  tuple(map(lambda v: v[0], vertices)) + (vertices[0][0],) 
    m2 =  tuple(map(lambda v: v[1], vertices)) + (vertices[0][1],) 

    s1 = sum(map(lambda m: m[0] * m[1], zip(m1, itertools.islice(m2, 1, None))))
    s2 = sum(map(lambda m: m[0] * m[1], zip(itertools.islice(m1, 1, None), m2)))

    return int((abs(s1 - s2) + perimeter) / 2 + 1)

print(area(perimeter, vertices), end="")
