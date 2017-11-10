import random

class QueenBoard():
  def __init__(self, queens):
    self.queens_ = queens
    self.score_ = None
    self.conflicts_ = {}
    self.size_ = len(self.queens_)

    self.left_diagonal = {}
    self.right_diagonal = {}
    self.row_diagonal = {}

    self.conflict_diagondals_()

  def conflict_diagondals_(self):
    for c,r in enumerate(self.queens_):
      if r is not None:
        self.left_diagonal[c+r] = self.left_diagonal.get(c+r, 0) + 1
        self.right_diagonal[c-r] = self.right_diagonal.get(c-r, 0) + 1
        self.row_diagonal[r] = self.row_diagonal.get(r, 0) + 1


  def is_queen_on(self, row, col):
    return self.queens_[col] == row


  def move_queen_on(self, queen, position):
    # remove old queen
    if self.queens_[queen] is not None:
      c, r = queen, self.queens_[queen]
      self.left_diagonal[c+r] = self.left_diagonal[c+r] - 1
      self.right_diagonal[c-r] = self.right_diagonal[c-r] - 1
      self.row_diagonal[r] = self.row_diagonal[r] - 1

    # insert new queen
    c, r = queen, position
    self.queens_[queen] = position

    self.left_diagonal[c+r] = self.left_diagonal.get(c+r, 0) + 1
    self.right_diagonal[c-r] = self.right_diagonal.get(c-r, 0) + 1
    self.row_diagonal[r] = self.row_diagonal.get(r, 0) + 1

    return self


  def conflicts(self, row, col):
    # row_col = "%d_%d" % (row, col)
    # if row_col in self.conflicts_:
    #   return self.conflicts_[row_col]

    count = 0

    # conflicts on row
    count += self.row_diagonal.get(row, 0)

    # conflicts on col are zero
    # count += 0

    # conflicts on diagonals
    count += self.left_diagonal.get(col + row, 0)
    count += self.right_diagonal.get(col - row, 0)

    if self.is_queen_on(row, col):
      count -= 3

    # self.conflicts_[row_col] = count
    return count

  def score(self):
    # if self.score_ is None:
    conflicts = map(
      lambda c_r: self.conflicts(c_r[1], c_r[0]),
      enumerate(self.queens_)
    )
    self.score_ = sum(conflicts)

    return self.score_

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


def move_queen_on(board, queen, position):
  next_board = list(board.queens_)
  next_board[queen] = position

  return QueenBoard(next_board)


def max_queen_on_min_state(board):
  m_queen = max_queen(board)
  m_queen_min_state = min_state(board, m_queen)

  # return move_queen_on(board, m_queen, m_queen_min_state)
  return board.move_queen_on(m_queen, m_queen_min_state)


def rand_queen_on_rand_state(board):
  rand_queen = random.choice(range(0, board.size()))
  rand_state = random.choice(range(0, board.size()))

  # return move_queen_on(board, rand_queen, rand_state)
  return board.move_queen_on(rand_queen, rand_state)


def min_conflicts(start):
  current = start
  last_score = current.score()
  # ite = 0
  while last_score > 0:
    # ite +=1
    # print(last_score)
    current = max_queen_on_min_state(current)

    next_score = current.score()
    if last_score <= next_score:
      current = rand_queen_on_rand_state(current)
      next_score = current.score()

    last_score = next_score

  # print(ite, current.score())
  return current


def init_board(size):
  board = QueenBoard([None for i in range(size)])
  position_to_try = list(range(board.size()))
  # avg_try = 0
  chunk = int(board.size() * 0.1)
  for queen in range(board.size()):
    if queen % chunk == 0:
      random.shuffle(position_to_try)

    # n_try = 0
    state = position_to_try[0]
    for r in position_to_try[queen % chunk:]:
      # n_try += 1
      if board.conflicts(r, queen) < board.conflicts(state, queen):
        state = r

      if board.conflicts(state, queen) == 0:
        break

    # avg_try += n_try
    # print(queen, 'state', state, board.conflicts(state, queen), n_try, avg_try / (queen + 1))
    # board = move_queen_on(board, queen, state)
    board.move_queen_on(queen, state)

  return board


if __name__ == '__main__':
    size = int(input())

    # start_board = QueenBoard([1,2,0,3])
    # print(start_board.score())
    start_board = init_board(size)
    # print('ready')
    # # print(str(start_board))

    solution = min_conflicts(start_board)

    print(str(solution))
    # print(solution.queens_)
