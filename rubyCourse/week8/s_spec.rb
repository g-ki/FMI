describe Spreadsheet do
  describe '#new' do
    it 'creates an empty sheet from a string' do
      expect(Spreadsheet.new()).to be_empty
      expect(Spreadsheet.new('   ')).to be_empty
    end
    it 'creates a non-empty sheet from a string' do
      expect(Spreadsheet.new('foo')).not_to be_empty
    end
  end

  describe '#empty?' do
    it 'returns true if the sheet is empty' do
      expect(Spreadsheet.new().empty?).to eq true
    end
    it 'returns false if the sheet is not empty' do
      expect(Spreadsheet.new("asd\tasd").empty?).to eq false
    end
  end

  describe '#to_s' do
    it 'returns tables as a string' do
      expect(Spreadsheet.new("foo\tbar\nbaz\tlarodi").to_s).to eq "foo\tbar\nbaz\tlarodi"
    end

    it 'returns the evaluated spreadsheet as a table' do
      sheet = Spreadsheet.new <<-TABLE
        1  2  =ADD(1, B1)
        4  5  6
      TABLE

      expect(sheet.to_s).to eq \
        "1\t2\t3\n" \
        "4\t5\t6"

      sheet = Spreadsheet.new <<-TABLE
        1  =ADD(A2, 3.5)  =ADD(1, B1)
        4  5  6
      TABLE

      expect(sheet.to_s).to eq \
        "1\t7.50\t8.50\n" \
        "4\t5\t6"

      sheet = Spreadsheet.new <<-TABLE
        1  =ADD(1, C1)  =ADD(A2, 3.5)
        4  5  6
      TABLE

      expect(sheet.to_s).to eq \
        "1\t8.50\t7.50\n" \
        "4\t5\t6"
    end

    it 'evaluates all functions correctly' do
      sheet = Spreadsheet.new <<-TABLE
        =DIVIDE(1, 3)  =ADD(2, 3.0)  =MULTIPLY(2, 3, 4.000)
        =MOD(4, 3)  =SUBTRACT(5, 2)  =6
      TABLE

      expect(sheet.to_s).to eq \
        "0.33\t5\t24\n" \
        "1\t3\t6"

      sheet = Spreadsheet.new <<-TABLE
        =DIVIDE(1, 3)  =ADD(2, 3.0)  =MULTIPLY(2, 3, 4.000)
        =MOD(4, 3)  =SUBTRACT(5, 2)  =A1
      TABLE

      expect(sheet.to_s).to eq \
        "0.33\t5\t24\n" \
        "1\t3\t0.33"
    end

    it 'raises an exception for wrong formulas in the table' do
      sheet = Spreadsheet.new("\t\t=ADD(\t\t1   ,   3,  18   )")
      expect { sheet.to_s }.to raise_error(Spreadsheet::Error, "Invalid expression 'ADD('")
    end
  end

  describe '#cell_at' do
    it 'raises an exception for wrong cell addresses' do
      expect { Spreadsheet.new('foo')['FOO'] }.to raise_error(Spreadsheet::Error, "Invalid cell index 'FOO'")
    end

    it 'calculates the cell address correctly' do
      expect(Spreadsheet.new([*(1..29)].join("\t")).cell_at 'AB1').to eq '28'
      expect(Spreadsheet.new([*(1..29)].join("\n")).cell_at 'A12').to eq '12'
    end

    it 'correctly returns raw cell contents' do
      sheet = Spreadsheet.new("\t\t=ADD(\t\t1   ,   3,  18   )")
      expect(sheet.cell_at 'A1').to eq '=ADD('

      sheet = Spreadsheet.new '=ADD(1,1,1)'
      expect(sheet.cell_at 'A1').to eq '=ADD(1,1,1)'
    end
  end

  describe '#[]' do
    it 'raises an exception for non-existant cells' do
      expect { Spreadsheet.new('foo')['C42'] }.to raise_error(Spreadsheet::Error, /Cell 'C42' does not exist/)
    end

    it 'raises an exception for wrong formulas' do
      sheet = Spreadsheet.new("\t\t=ADD(\t\t1   ,   3,  18   )")
      expect { sheet['A1'] }.to raise_error(Spreadsheet::Error, "Invalid expression 'ADD('")
    end

    it 'returns the value of existing cells' do
      sheet = Spreadsheet.new <<-TABLE
        foo  bar
        baz  larodi
      TABLE

      expect(sheet['A2']).to eq 'baz'
    end

    it 'returns the evaluated expression' do
      sheet = Spreadsheet.new("=ADD(2, 2)")

      expect(sheet['A1']).to eq('4')
    end

    it 'raises an exception when a function expects other fixed number of arguments' do
      sheet = Spreadsheet.new("=DIVIDE(6, 3, 4)")
      expect { sheet['A1'] }.to raise_error(Spreadsheet::Error, "Wrong number of arguments for 'DIVIDE': expected 2, got 3")
    end

    it 'raises an exception when a function expects more arguments' do
      sheet = Spreadsheet.new("=ADD(6)")
      expect { sheet['A1'] }.to raise_error(Spreadsheet::Error, "Wrong number of arguments for 'ADD': expected at least 2, got 1")
    end
  end
end
