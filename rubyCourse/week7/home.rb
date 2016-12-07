class LazyMode
  class Date
    private
    def set_date(year, month, day)
      @year = year.to_i
      @month = month.to_i
      @day = day.to_i
    end

    public
    attr :year, :month, :day, :step

    def Date.new_date(year, month, day)
      Date.new("#{year}-#{month}-#{day}")
    end

    def initialize(date)
      date_match = date.match(/(\d+-\d+-\d+)(\s\+(\d+)([mdw]))?/)

      set_date(*date_match[1].split('-'))

      @step = date_match[3].to_i if date_match[2]

      case date_match[4]
       when 'w' then @step *= 7
       when 'm' then @step *= 30
      end
    end

    def next_day
      year, month, day = @year, @month, @day + 1

      month += 1 if day > 30
      day = 1 if day % 31 == 0

      year += 1 if month > 12
      month = 1 if month % 13 == 0

      Date.new_date(year, month, day)
    end

    def to_s
      year = @year.to_s.rjust(4, '0')
      month = @month.to_s.rjust(2, '0')
      day = @day.to_s.rjust(2, '0')
      "#{year}-#{month}-#{day}"
    end

    def fix(date)
        if @step != nil && date =~ self
          @day = date.day
          @month = date.month
          @year = date.year
        end
    end

    def to_i
      year * 360 + month * 30 + day
    end

    def =~(other)
      return false if to_s < other.to_s
      return true if to_s == other.to_s

      return (to_i - other.to_i) % other.step == 0 if other.step

      false
    end
  end

  class Note
    attr_accessor :header, :file_name, :body, :status, :tags, :date

    def initialize(file_name, header, tags = [])
      @file_name = file_name
      @header = header
      @tags = tags
      @status = :topostpone
      @body = ""
    end
  end

  class NoteDSL
    attr :note, :file

    def initialize(note, file,  &block)
      @note = note
      @file = file
    end

    def body(value)
      @note.body = value
    end

    def status(value)
      @note.status = value
    end

    def scheduled(date_string)
      @note.date = Date.new(date_string)
    end

    def note(*args, &block)
      @file.send(:note, *args, &block)
    end
  end

  class Agenda
    attr :notes

    def initialize(notes, date = nil)
      @notes = notes
      select(date) if date
    end

    def where(tag: nil, text: nil, status: nil)
      notes = @notes.select { |note| tag.nil? || note.tags.include?(tag) }

      notes.select! do |note|
         text.nil? || note.body.match(text) || note.header.match(text)
      end

      notes.select! { |note| status.nil? || note.status == status }

      Agenda.new(notes)
    end

    private
    def select(date)
      @notes = @notes.select { |note| date =~ note.date }

      @notes = @notes.map do |note|
        agenda_note = note.clone
        agenda_note.date.fix(date)
        agenda_note
      end
    end
  end

  class File
    attr :name, :notes

    def initialize(name)
      @name = name
      @notes = []
    end

    def daily_agenda(date)
      Agenda.new(@notes, date)
    end

    def weekly_agenda(date)
      notes = []
      (0...7).each do
        agenda = daily_agenda(date)
        notes += agenda.notes
        date = date.next_day
      end
      Agenda.new(notes)
    end

    private
    def note(header, *tags, &block)
      new_note = Note.new(@name, header, tags)
      @notes.push new_note

      note = NoteDSL.new(new_note, self)
      note.instance_eval(&block)
      new_note
    end
  end

  def self.create_file(name, &block)
    file = File.new name
    file.instance_eval(&block)
    file
  end
end
