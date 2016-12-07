def is_i?(char)
  char == char.to_i.to_s
end

def number_to_taps(number)
  if number == 1
    1
  elsif number == 0
    2
  elsif number != 7 && number != 9
    4
  else
    5
  end
end

def char_to_taps(char)
  c = char.downcase

  if is_i? c
    number_to_taps(c.to_i)
  elsif c < 'a'
    1
  elsif c < 's'
    ((c.ord - 94)%3 + 1)
  elsif c > 's' && c < 'z'
    ((c.ord - 113)%3 + 1)
  else
    4
  end
end

def button_presses(message)
  presses = 0
  message.each_char do |char|
    presses = presses + char_to_taps(char)
  end
  presses
end