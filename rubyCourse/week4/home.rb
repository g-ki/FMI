class Card
  attr :rank
  attr :suit

  def initialize(rank, suit)
    @rank, @suit = rank, suit
  end

  def to_s
    @rank.to_s.capitalize + " of " + @suit.to_s.capitalize
  end

  def ==(other)
    @rank == other.rank && @suit == other.suit
  end
end

class Deck
  include Enumerable

  def ranks
    [2, 3, 4, 5, 6, 7, 8, 9, 10, :jack, :queen, :king, :ace]
  end

  def get_rank(card)
    ranks.index(card.rank)
  end

  def suits
    [:clubs, :diamonds, :hearts, :spades]
  end

  def get_suit(card)
    suits.index(card.suit)
  end

  def full_deck
    suits.product(ranks).map { |suit, rank| Card.new(rank, suit) }
  end

  def initialize(cards = full_deck)
    @cards = cards
  end

  def each
    @cards.each { |card| yield card }
  end

  def size
    @cards.size
  end

  def draw_top_card
    @cards.slice!(0)
  end

  def draw_bottom_card
    @cards.slice!(-1)
  end

  def top_card
    @cards.first
  end

  def bottom_card
    @cards.last
  end

  def shuffle
    @cards.shuffle!
  end

  def sort
    @cards = @cards.sort_by { |card|
      p card.to_s + " " + get_suit(card).to_s + " " + get_rank(card).to_s
      [ -get_suit(card), -get_rank(card)] }
  end

  def to_s
    @cards.inject("") { |s, card| s = s + card.to_s + "\n" }
  end

  def deal
    Hand.new(self, 0)
  end

  class Hand < Deck
    def initialize(deck, size)
      super deck.to_a.slice!(0, size)
      @deck = deck
      (0..size).each { deck.draw_top_card }
      self.sort
    end

    def ranks
      @deck.ranks
    end
  end
end

class WarDeck < Deck
  def deal
    Hand.new(self, 26)
  end

  class Hand < Deck::Hand
    def play_card
      draw_top_card
    end

    def allow_face_up?
      size <= 3
    end
  end
end

class BeloteDeck < Deck

  def ranks
    [7, 8, 9, :jack, :queen, :king, 10, :ace]
  end

  def deal
    Hand.new(self, 8)
  end

  class Hand < Deck::Hand
    def consecutive? (length)
      sort
      @cards.each_cons(length).any? do |cons|
        if(cons.first.suit == cons.last.suit)
          get_rank(cons.first) - get_rank(cons.last) == length - 1
        end
      end
    end

    def carre_of?(rank)
      @cards.count { |card| card.rank == rank } == 4
    end

    def all_of_suit(suit)
      @cards.select { |card| card.suit == suit }
    end

    def highest_of_suit(suit)
      all_of_suit(suit).max_by { |card| get_rank(card) }
    end

    def belote?
      sort
      @cards.each_cons(2).any? do |pair|
        pair.first.suit == pair.last.suit &&
          pair.first.rank == :king && pair.last.rank == :queen
      end
    end

    def tierce?
      consecutive?(3)
    end

    def quarte?
      consecutive?(4)
    end

    def quint?
      consecutive?(5)
    end

    def carre_of_jacks?
      carre_of?(:jack)
    end

    def carre_of_nines?
      carre_of?(9)
    end

    def carre_of_aces?
      carre_of?(:ace)
    end
  end #BeloteDeck::Hand
end

class SixtySixDeck < Deck
  def ranks
    [9, :jack, :queen, :king, 10, :ace]
  end

  def deal
    Hand.new(self, 6)
  end

  class Hand < Deck::Hand
    def king_and_queen
      sort
      @cards.each_cons(2).find_all do |pair|
        pair.first.suit == pair.last.suit &&
          pair.first.rank == :king && pair.last.rank == :queen
      end
    end

    def twenty?(trump_suit)
      king_and_queen.any?{ |pair| ! pair.nil? && pair.first.suit != trump_suit }
    end

    def forty?(trump_suit)
      king_and_queen.any?{ |pair| ! pair.nil? && pair.first.suit == trump_suit }
    end
  end #SixtySixDeck::Hand
end


# a = Card.new(:jack, :clubs)
# b = Card.new(:queen, :clubs)
# c = Card.new(:king, :clubs)
#
# d = Card.new(:queen, :spades)
# e = Card.new(:king, :spades)
#
# d = SixtySixDeck.new([c,a,b,d,e])
#
# p1 = d.deal
# puts p1.to_s
# p1.shuffle
# puts p1.twenty?(:spades)

hand = SixtySixDeck.new([
  Card.new(:ace, :clubs),
  Card.new(:jack, :spades),
  Card.new(7, :clubs),
  Card.new(10, :hearts),
  Card.new(:queen, :clubs),
  Card.new(:king, :clubs),
]).deal

puts hand.twenty?(:hearts)
