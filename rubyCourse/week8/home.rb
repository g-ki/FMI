class Spreadsheet
private
  def parse(text)
    lines = text.strip.split(/\n/)
    lines.map { |line| line.strip.split(/\t+| {2,}/).map(&:strip) }
  end

  def get_cell_index(cell_index)
    return nil unless cell_index = Expression.index?(cell_index)

    column = cell_index[1].each_byte.reverse_each.map { |byte| byte - 64 }
    column.map!.with_index { |byte, index| byte * (26 ** index) }

    row = cell_index[2].to_i - 1
    column = column.reduce(:+) - 1

    [row, column]
  end

  def validate_cell_index(cell_index)
    row, column = get_cell_index cell_index
    if row.nil?
       raise Error, "Invalid cell index '#{cell_index}'"
    elsif @table[row].nil? || @table[row][column].nil?
       raise Error, "Cell '#{cell_index}' does not exist"
    end
  end

public
  def initialize(table = "")
    @table = parse table
  end

  def empty?
    @table.empty?
  end

  def cell_at(cell_index)
    validate_cell_index cell_index

    row, column = get_cell_index cell_index

    @table[row][column]
  end

  def [](cell_index)
    cell = cell_at cell_index

    Expression.evaluate(cell, self).to_s
  end

  def to_s
    @table.map do |row|
      row.map do |cell|
        Expression.evaluate(cell, self).to_s
      end.join("\t")
    end.join("\n")
  end

  class Error < RuntimeError
  end

  module Expression
    def self.match?(string)
      not string.match(/^=/).nil?
    end

    def self.number?(string)
      string.match(/^\d+(\.\d+)?$/)
    end

    def self.index?(cell_index)
      cell_index.match(/^([A-Z]+)(\d+)$/)
    end

    def self.normalize(result)
      result = result.to_f
      if result == result.floor then ("%d" % result) else ("%.2f" % result) end
    end

    def self.evaluate(string, sheet)
      string = evaluate_string(string, sheet) if match? string
      string
    end
private
    def self.evaluate_string(string, sheet)
      expression = string.match(/[\w.]+/)[0]

      return normalize(expression) if number? expression

      return sheet[expression] if index? expression

      normalize evaluate_formula(string, sheet)
    end

    def self.evaluate_formula(formula, sheet)
      Formula.verify formula

      formula, *args = formula.scan(/[\w.]+/)
      formula = formula.sub(/=/, "").downcase

      args.map! { |argument| Expression.evaluate_string(argument, sheet).to_f }

      Formula.send(formula, *args)
    end
  end

  module Formula
    def self.add(first, second, *more)
      first + second + more.reduce(0, :+)
    end

    def self.multiply(first, second, *more)
      first * second * more.reduce(1, :*)
    end

    def self.subtract(first, second)
      first - second
    end

    def self.divide(first, second)
      first / second
    end

    def self.mod(first, second)
      first % second
    end

    def self.verify(string)
      unless string.match(/^= ?[A-Z]+\([\w\s,.=]+\)$/) &&
              string.count(",") == string.scan(/[\w.]+/).size - 2
        raise Error, "Invalid expression '#{string.sub(/^=/, "")}'"
      end
    end

    def self.verify_arguments(formula, args)
      real_args = method(formula).arity
      message = "Wrong number of arguments for '#{formula.upcase}': expected "
      if real_args > 0 && real_args != args
        raise Error, message + "#{real_args}, got #{args}"
      elsif real_args < 0 && real_args.abs - 1 > args
        raise Error, message + "at least #{real_args.abs - 1}, got #{args}"
      end
    end

    def self.send(name, *args, &block)
      if methods.include?(name.to_sym)
        verify_arguments(name, args.size)
        super
      elsif
        raise Error, "Unknown function '#{name.upcase}'"
      end
    end
  end
end
