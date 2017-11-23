from copy import deepcopy as dcopy
import random

def change_state(state, r, c, val):
  new_state = dcopy(state)
  new_state[r][c] = val

  return new_state


def next_states(state, player):
  for r,row in enumerate(state):
    for c,cell in enumerate(row):
      if cell is ' ':
        yield change_state(state, r, c, player)


def score(state, player):
  winner = has_winner(state)
  if winner is None:
    return 0

  if winner == player:
    return 1

  return -1


def min_max_state(state, max_p, min_p):
  if is_over(state) or has_winner(state):
    return state, score(state, max_p)

  scores = []
  for next_state in next_states(state, max_p):
    _, next_score = min_max_state(next_state, min_p, max_p)
    scores.append((next_state, -next_score))

  random.shuffle(scores)
  return max(scores, key=lambda s: s[1])


def empty_state():
  return [
    [' ',' ',' '],
    [' ',' ',' '],
    [' ',' ',' ']
  ]


def has_winner(state):
  x = ['x'] * 3
  o = ['o'] * 3

  # check rows
  for row in state:
    if row == x or row == o:
      return row[0]

  # check cols
  for c in range(3):
    col = [state[r][c] for r in range(3)]
    if col == x or col == o:
      return col[0]

  # check diagonals
  d1 = [state[0][0], state[1][1], state[2][2]]
  d2 = [state[0][2], state[1][1], state[2][0]]

  if d1 == x or d1 == o:
    return d1[0]
  if d2 == x or d2 == o:
    return d2[0]

  return None


def is_over(state):
  for row in state:
    for cell in row:
      if cell is ' ':
        return False

  return True



def print_state(state):
  for r,row in enumerate(state):
    print(*row, sep=' | ')


def read_human_input():
  return [int(i) for i in input().split()]


def run_game(current_state):
  # player move
  human_row, human_col = read_human_input()
  while current_state[human_row][human_col] is not ' ':
    print('Please make a valid move!')
    human_row, human_col = read_human_input()

  next_state = change_state(current_state, human_row, human_col, 'x')
  print_state(next_state)
  winner = has_winner(next_state)
  if winner:
    print('Winner is %s' % winner)
    return next_state

  # computer move
  next_state = min_max_state(next_state, max_p='o', min_p='x')[0]
  winner = has_winner(next_state)
  if winner:
    print('Winner is %s' % winner)
    return next_state

  return next_state



if __name__ == '__main__':
  current_state = empty_state()
  while not (is_over(current_state) or has_winner(current_state)):
    current_state = run_game(current_state)
    print_state(current_state)
