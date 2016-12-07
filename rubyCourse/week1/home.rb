#=begin
dimensions = {width: 10, height: 10}

snake = [[4, 5], [4, 6], [5, 6], [5, 7]]

direction = [0, 1]

food = [[3, 2], [1, 1], [0, 5]]
#=end

def next_position(position, direction)
  [position[0] + direction[0], position[1] + direction[1]]
end

def move(snake, direction)
  new_head = next_position(snake.last, direction)
  snake.drop(1).push(new_head)
end

def grow(snake, direction)
  new_head = next_position(snake.last, direction)
  snake.dup.push(new_head)
end

def new_food(food, snake, dimensions)
  map = [*0..dimensions[:width]-1].product([*0..dimensions[:height]-1])
  (map - (snake | food)).sample
end

def obstacle_ahead?(snake, direction, dimensions)
  next_x, next_y = next_position(snake.last, direction)
  wall_ahead = (next_x < 0 || next_y < 0) ||
                  (next_x == dimensions[:width]) ||
                  (next_y == dimensions[:height])

  snake.include?([next_x, next_y]) or wall_ahead
end

def danger?(snake, direction, dimensions)
  obstacle_ahead?(snake, direction, dimensions) or
    obstacle_ahead?(move(snake, direction), direction, dimensions)
end