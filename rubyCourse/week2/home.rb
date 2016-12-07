class RationalSequence
  include Enumerable

  def initialize(size)
    @size = size
  end

  def get_raw_rational(position)
    n, k = position, 1
    while n >= k
      n -= k
      k += 1
    end
    if k.even? then [k - n, n + 1] else [n + 1, k - n] end
  end

  def each
    current, current_size = 0, 0
    while current_size < @size
      numerator, denominator = get_raw_rational current

      if numerator.gcd(denominator) == 1
        yield Rational(numerator, denominator)
        current_size += 1
      end
      current += 1
    end
  end
end

class Integer
  def prime?
    return false if self <= 1
    2.upto(Math.sqrt(self)).each {|i| return false if self % i == 0}
    true
  end
end

class PrimeSequence
  include Enumerable

  def initialize(size)
    @size = size
  end

  def each
    current = 2
    current_size = 0
    while current_size < @size
      if(current.prime?)
        yield current
        current_size += 1
      end
      current += 1
    end
  end
end

class FibonacciSequence
  include Enumerable

  def initialize(size, first: 1, second: 1)
    @size, @first, @second = size, first, second
  end

  def each
    current, previous = @second, @first
    (0...@size).each do
      yield previous
      current, previous = current + previous, current
    end
  end
end

module DrunkenMathematician
  module_function

  def meaningless(n)
    groups = RationalSequence.new(n).partition do |rational|
              rational.numerator.prime? or rational.denominator.prime?
            end
    groups[0].reduce(1, :*) / groups[1].reduce(1, :*)
  end

  def aimless(n)
    aimless_sum = 0
    PrimeSequence.new(n).each_slice(2) do |prime|
      aimless_sum += Rational(prime[0], prime.fetch(1, 1))
    end
    aimless_sum
  end

  def worthless(n)
    limit = FibonacciSequence.new(n).to_a.fetch(-1, 0)
    rationals = RationalSequence.new(Float::INFINITY).lazy

    sum  = 0
    rationals.take_while do |rational|
      sum += rational
      sum <= limit
    end.force
  end
end