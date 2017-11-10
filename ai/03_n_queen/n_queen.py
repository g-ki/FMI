import random

class QueenBoard():
  def __init__(self, queens):
    self.queens_ = tuple(queens)
    self.score_ = None


  def is_queen_on(self, row, col):
    return self.queens_[col] == row

  def conflicts(self, row, col):
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

    d1_conflicts = map(lambda xy: self.is_queen_on(*xy), d1)
    d2_conflicts = map(lambda xy: self.is_queen_on(*xy), d2)

    count += d1_conflicts.count(True) + d2_conflicts.count(True)


    return count

  def score(self):
    if self.score_ is None:
      conflicts = map(lambda q: self.conflicts(q[1], q[0]), enumerate(self.queens_))
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


def max_queen(board):
  conflicts = map(lambda q: (q[0], board.conflicts(q[1], q[0])), enumerate(board.queens_))
  return max(conflicts, key=lambda q: q[1])[0]

def move_queen_on(board, queen, position):
  next_board = list(board.queens_)
  next_board[queen] = position

  return QueenBoard(next_board)


# def better_random(state, max_iter):
#   current_score = state.score()
#   new_state = state
#   for i in range(max_iter):
#     rand_queen = random.choice(range(0, len(state.queens_)))
#     rand_state = random.choice(range(0, len(state.queens_)))

#     new_state = move_queen_on(state, rand_queen, rand_state)
#     new_score = new_state.score()
#     if new_score < current_score:
#       return new_state

#   return new_state

def min_conflicts(start):
  current = start
  last_score = current.score()
  ite = 0
  while last_score > 0:
    ite +=1
    m_queen = max_queen(current)

    m_queen_states = map(
      lambda r: (r, current.conflicts(r, m_queen)),
      range(len(current.queens_))
    )

    min_state = min(m_queen_states, key=lambda q: q[1])[0]

    current = move_queen_on(current, m_queen, min_state)

    if last_score <= current.score():
      rand_queen = random.choice(range(0, len(current.queens_)))
      rand_state = random.choice(range(0, len(current.queens_)))

      current = move_queen_on(current, rand_queen, rand_state)

    last_score = current.score()

  print(ite, current.score())
  return current


def rand_board(size):
  # board = map(lambda i: random.choice(range(0, size)), range(size))
  board = list(range(0, size))
  return QueenBoard(board)


if __name__ == '__main__':
    # size = int(input())

    # start_board = QueenBoard([1,2,0,3,4,5,6,7])
    start_board = rand_board(10)
    print(str(start_board))

    solution = min_conflicts(start_board)

    print(str(solution))
