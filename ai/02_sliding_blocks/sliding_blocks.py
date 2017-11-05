from collections import defaultdict
import itertools, math
from heapq import *

# LIB

class PQueue():
    def __init__(self):
        self.data_ = []
        self.index_ = {}
        self.counter_ = itertools.count()

    def push(self, value, priority=0):
        'Add new element or update priority.'
        if value in self.index_:
            self.remove(value)

        count = next(self.counter_)
        entry = [priority, count, value]
        self.index_[value] = entry
        heappush(self.data_, entry)

        return self

    def remove(self, value):
        'Mark an existing element as removed.'
        entry = self.index_.pop(value)
        entry[-1] = '<removed-element>'

    def pop(self):
        'Remove and return the lowest priority element.'
        while self.data_:
            priority, count, value = heappop(self.data_)
            if value != '<removed-element>':
                del self.index_[value]
                return value

        raise KeyError('pop from an empty priority queue')

    def __contains__(self, value):
        return value in self.index_

    def __len__(self):
        return len(self.index_)


def reconstruct_path(parent_tree, current):
    path = [current]
    while current in parent_tree:
        current = parent_tree[current]
        path.append(current)

    path.reverse()
    return path


def a_star(start, goal, neighbors_of, heuristic_cost):
    visited = set()
    discovered = PQueue()
    parent = dict()

    g_score = defaultdict(lambda: float("inf"))
    g_score[start] = 0

    f_score = defaultdict(lambda: float("inf"))
    f_score[start] = heuristic_cost(start, goal)

    discovered.push(start, f_score[start])

    while len(discovered) > 0:
        current = discovered.pop()

        if current == goal:
            return reconstruct_path(parent, current)

        visited.add(current)

        for neighbor in neighbors_of(current):
            if neighbor in visited:
                continue

            # The distance from start to a neighbor
            tmp_gScore = g_score[current] + 1 # dist(current, neighbor)
            if tmp_gScore >= g_score[neighbor]:
                continue

            parent[neighbor] = current
            g_score[neighbor] = tmp_gScore
            f_score[neighbor] = g_score[neighbor] + heuristic_cost(neighbor, goal)

            discovered.push(neighbor, f_score[neighbor])

    return None

# Solution

class Grid():
    def __init__(self, grid):
        self.grid_ = tuple(grid)
        self.size_ = int(math.sqrt(len(self.grid_)))
        self.empty_index_ = self.grid_.index(0)
        self.hash_ = hash(self.grid_)

    def index_1d(self, x, y):
        return self.size_ * x + y

    def index_2d(self, i):
        return (i // self.size_, i % self.size_)

    def swap_(self, x, y):
        nextGrid = list(self.grid_) # copy current grid
        index = self.index_1d(x, y)

        nextGrid[index] = 0
        nextGrid[self.empty_index_] = self.grid_[index]
        return Grid(nextGrid)

    def up(self):
        x, y = self.index_2d(self.empty_index_)
        x += 1
        if x >= self.size_:
            return self

        return self.swap_(x, y)

    def down(self):
        x, y = self.index_2d(self.empty_index_)
        x -= 1
        if x < 0:
            return self

        return self.swap_(x, y)

    def left(self):
        x, y = self.index_2d(self.empty_index_)
        y += 1
        if y >= self.size_:
            return self

        return self.swap_(x, y)

    def right(self):
        x, y = self.index_2d(self.empty_index_)
        y -= 1
        if y < 0:
            return self

        return self.swap_(x, y)

    def __hash__(self):
        return self.hash_

    def __str__(self):
        return str(self.grid_)

    def __eq__(self, other):
        return hash(self) == hash(other)
        # return self.grid_ == other.grid_


def manhattan_dist(state, goal):
    dist = 0
    for i, block in enumerate(state.grid_):
        x1, y1 = state.index_2d(i)
        x2, y2 = goal.index_2d(goal.grid_.index(block))

        dist += abs(x1 - x2) + abs(y1 - y2) # Manhattan distance

    return dist


def neighbors(state):
    return set([state.up(), state.down(), state.left(), state.right()]) - set([state])


def path_to_instructions(path):
    instructions = []
    for a, b in zip(path, path[1:]):
        states = { a.up(): 'up', a.down(): 'down', a.left(): 'left', a.right(): 'right' }
        instructions.append(states[b])

    return instructions

# Inputs

# 8
# 3 8 4
# 5 2 1
# 7 0 6

# 8
# 2 0 7
# 5 3 6
# 1 4 8

# 15
# 1 9 4 3
# 6 0 15 14
# 11 12 7 5
# 2 13 8 10
if __name__ == '__main__':
    size = input()
    size = int(math.sqrt(int(size) + 1))

    start = ''
    for row in range(size):
        start += input().strip()
        start += ' '

    start = list(map(int, start.strip().replace(r'\s+', ' ').split()))
    start_grid = Grid(start)

    goal = list(range(1, size**2)) + [0]
    goal_grid = Grid(goal)

    path = a_star(start_grid, goal_grid, neighbors, manhattan_dist)
    if path:
        instructions = path_to_instructions(path)
        print(len(instructions))

        for i, inst in enumerate(instructions):
            print(inst)
    else:
        print("404: Solution not found!")
