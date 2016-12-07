module TurtleGraphics
  class Turtle
    DIRECTION = {left: [0, -1], up: [-1, 0], right: [0, 1], down: [1, 0]}
    ORIENTATION = [:left, :up, :right, :down]

    def initialize(rows, columns)
      @rows, @columns =  rows, columns
      @plane = Array.new(@rows) { Array.new(@columns, 0) }
      @position = nil
      @orientation = :right
    end

    def draw(canvas = nil, &block)
      self.instance_eval(&block) if block_given?
      if canvas.respond_to? :draw
        canvas.draw(@plane)
      else
        @plane
      end
    end

    def move
      spawn_at(0, 0) if @position.nil?

      direction = DIRECTION[@orientation]
      @position = [(@position[0] + direction[0]) % @rows,
                    (@position[1] + direction[1]) % @columns]

      @plane[@position[0]][@position[1]] += 1
    end

    def turn_right
      direction = (ORIENTATION.index(@orientation).next) % ORIENTATION.size
      @orientation = ORIENTATION[direction]
    end

    def turn_left
      direction = (ORIENTATION.index(@orientation).pred) % ORIENTATION.size
      @orientation = ORIENTATION[direction]
    end

    def spawn_at(row, column)
      @position = [row, column]
      @plane[row][column] += 1
    end

    def look(orientation)
      @orientation = orientation
    end
  end # class Turtle

  class Canvas
    def self.find_intensity(canvas)
      intensity = canvas.max
      (intensity == 0) ? 1 : intensity
    end

    class ASCII
      def initialize(symbols)
        @symblos = symbols
      end

      def draw(plane)
        columns = plane[0].size
        canvas = plane.flatten

        max_intensity = Canvas.find_intensity(canvas)

        canvas = canvas.map do |pixel|
          intensity = pixel.fdiv(max_intensity) * (@symblos.size - 1)
          @symblos[intensity.ceil]
        end

        canvas.each_slice(columns).reduce do |row_a, row_b|
          "#{row_a.join("")}\n#{row_b.join("")}"
        end
      end
    end

    class HTML
      def initialize(pixel_size)
        @pixel_size = pixel_size
      end

      def head
        "<!DOCTYPE html><html><head><title>Turtle graphics</title><style>"\
        "table {border-spacing: 0;} tr{padding: 0;} "\
        "td { width: #{@pixel_size}px; height: #{@pixel_size}px; "\
        "background-color: black; padding: 0;} </style></head><body>"
      end

      def footer
        "</body></html>"
      end

      def draw(plane)
        max_intensity = Canvas.find_intensity(plane.flatten)
        canvas = head
        canvas += "<table>"
        plane.each do |row|
          canvas += "<tr>"
          row.each do |pixel|
            intensity = format '%.2f', pixel.fdiv(max_intensity)
            canvas += "<td style=\"opacity: #{intensity}\"></td>"
          end
          canvas += "</tr>"
        end
        canvas += "</table>" + footer
      end
    end
  end # module Canvas
end
