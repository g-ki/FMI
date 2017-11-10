import random

class QueenBoard():
  def __init__(self, queens):
    self.queens_ = queens
    self.score_ = None
    self.conflicts_ = {}


  def is_queen_on(self, row, col):
    return self.queens_[col] == row

  def conflicts(self, row, col):
    row_col = "%d_%d" % (row, col)
    if row_col in self.conflicts_:
      return self.conflicts_[row_col]

    count = 0

    # conflicts on row
    count += self.queens_.count(row)
    if self.is_queen_on(row, col):
      count -= 1

    # conflicts on col are zero
    # count += 0

    # conflicts on diagonals
    size = len(self.queens_)
    d1 = list(zip(range(row + 1, size), range(col + 1, size)))
    d1 += list(zip(range(row - 1, -1, -1), range(col - 1, -1, -1)))

    d2 = list(zip(range(row + 1, size), range(col - 1, -1, -1)))
    d2 += list(zip(range(row - 1, -1, -1), range(col + 1, size)))

    d1_conflicts = list(map(lambda xy: self.is_queen_on(*xy), d1))
    d2_conflicts = list(map(lambda xy: self.is_queen_on(*xy), d2))

    count += d1_conflicts.count(True) + d2_conflicts.count(True)

    self.conflicts_[row_col] = count
    return count

  def score(self):
    if self.score_ is None:
      conflicts = [self.conflicts(r, c) for c, r in enumerate(self.queens_)]
      self.score_ = sum(conflicts)

    return self.score_


  def __str__(self):
    board = ""
    for r in range(len(self.queens_)):
      row = ""
      for c in range(len(self.queens_)):
        if self.is_queen_on(r, c):
          row += "*"
        else:
          row += "_"
      board += row + "\n"

    return board

def rand_element(arr, value):
  return random.choice([i for i,val in enumerate(arr) if val == value])

def max_queen(board):
  conflicts = [board.conflicts(r, c) for c, r in enumerate(board.queens_)]
  queen = rand_element(conflicts, max(conflicts))

  return queen


def min_state(board, queen):
  queen_states = [board.conflicts(r, queen) for r in range(len(board.queens_))]
  state = rand_element(queen_states, min(queen_states))

  return state


def move_queen_on(board, queen, position):
  next_board = list(board.queens_)
  next_board[queen] = position

  return QueenBoard(next_board)


def max_queen_on_min_state(board):
  m_queen = max_queen(board)
  m_queen_min_state = min_state(board, m_queen)

  return move_queen_on(board, m_queen, m_queen_min_state)


def rand_queen_on_rand_state(board):
  rand_queen = random.choice(range(0, len(board.queens_)))
  rand_state = random.choice(range(0, len(board.queens_)))

  return move_queen_on(board, rand_queen, rand_state)

def min_conflicts(start):
  current = start
  last_score = current.score()
  ite = 0
  while last_score > 0:
    ite +=1
    current = max_queen_on_min_state(current)

    print(current.score())
    if last_score <= current.score():
      current = rand_queen_on_rand_state(current)

    last_score = current.score()

  print(ite, current.score())
  return current


def init_board(size):
  # board = list(range(0, size))
  board = [random.choice(range(size)) for i in range(size)]
  return QueenBoard(board)


if __name__ == '__main__':
    # size = int(input())

    # start_board = QueenBoard([1,2,0,3,4,5,6,7])
    start_board = init_board(1000)
    print(str(start_board))

    solution = min_conflicts(start_board)

    print(str(solution))
    print(solution.queens_)
