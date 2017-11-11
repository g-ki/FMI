import random

class QueenBoard():
  def __init__(self, queens):
    self.queens_ = queens
    self.size_ = len(self.queens_)

    self.left_diagonal = {}
    self.right_diagonal = {}
    self.row = {}

    self.init_conflicts_()


  def put_queen_on_(self, row, col):
    self.queens_[col] = row

    self.left_diagonal[col+row] = self.left_diagonal.get(col+row, 0) + 1
    self.right_diagonal[col-row] = self.right_diagonal.get(col-row, 0) + 1
    self.row[row] = self.row.get(row, 0) + 1


  def remove_queen_on_(self, row, col):
    self.left_diagonal[col+row] = self.left_diagonal[col+row] - 1
    self.right_diagonal[col-row] = self.right_diagonal[col-row] - 1
    self.row[row] = self.row[row] - 1

    self.queens_[col] = None


  def init_conflicts_(self):
    for c,r in enumerate(self.queens_):
      if r is not None:
        self.put_queen_on_(r, c)


  def is_queen_on(self, row, col):
    return self.queens_[col] == row


  def move_queen_on(self, queen, position):
    # remove old queen
    if self.queens_[queen] is not None:
      self.remove_queen_on_(self.queens_[queen], queen)

    # put new queen
    self.put_queen_on_(position, queen)

    return self


  def conflicts(self, row, col):
    count = 0
    # conflicts on row
    count += self.row.get(row, 0)

    # conflicts on diagonals
    count += self.left_diagonal.get(col + row, 0)
    count += self.right_diagonal.get(col - row, 0)

    if self.is_queen_on(row, col):
      count -= 3

    return count


  def score(self):
    conflicts = map(
      lambda c_r: self.conflicts(c_r[1], c_r[0]),
      enumerate(self.queens_)
    )

    return sum(conflicts)


  def size(self):
    return self.size_


  def __str__(self):
    board = ""
    for r in range(self.size_):
      row = ""
      for c in range(self.size_):
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
  queen_states = [board.conflicts(r, queen) for r in range(board.size())]
  state = rand_element(queen_states, min(queen_states))

  return state


def max_queen_on_min_state(board):
  m_queen = max_queen(board)
  m_queen_min_state = min_state(board, m_queen)

  return board.move_queen_on(m_queen, m_queen_min_state)


def rand_queen_on_rand_state(board):
  rand_queen = random.choice(range(0, board.size()))
  rand_state = random.choice(range(0, board.size()))

  return board.move_queen_on(rand_queen, rand_state)


def min_conflicts(start):
  current = start
  last_score = current.score()
  while last_score > 0:
    current = max_queen_on_min_state(current)

    next_score = current.score()
    # escape minimum
    # if last_score <= next_score:
    #   current = rand_queen_on_rand_state(current)
    #   next_score = current.score()

    last_score = next_score
  return current


def init_board(size):
  board = QueenBoard([None for i in range(size)])

  position_to_try = list(range(board.size()))
  chunk = int(board.size() * 0.1) + 1

  for queen in range(board.size()):
    if queen % chunk == 0:
      random.shuffle(position_to_try)

    state = position_to_try[0]
    for r in position_to_try[queen % chunk:]:
      if board.conflicts(r, queen) < board.conflicts(state, queen):
        state = r

      if board.conflicts(state, queen) == 0:
        break

    board.move_queen_on(queen, state)

  return board


if __name__ == '__main__':
    size = int(input())
    start_board = init_board(size)

    solution = min_conflicts(start_board)
    print(solution)

