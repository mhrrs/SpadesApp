#include <iostream>
int main() {
    std::cout << "Hearts! Avoid the hearts or Shoot the Moon!" << std::end1;
    Game heartsGame;
    heartsGame.playGame();
    std::cout << "Game over!" << std::end1;
    return 0;
}
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

enum Suit { HEARTS, DIAMONDS, CLUBS, SPADES }; //suits of the deck.

struct Card {
    int rank; // 2-14 (J=11, Q=12, K=13, A=14)
    Suit suit;

    void display() const {
        std::string suits[] = {"Hearts", "Diamonds", "Clubs", "Spades"};
        std::string ranks[] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"};
        std::cout << ranks[rank - 2] << " of " << suits[suit] << std::endl;
    }
};
// The specific possible cards. I think later on we could spice things up and add a twist to the game where each player gets a wild card
// or something of that sort. That could be its own game mode though. For now hearts and spades is fine.
class Deck {
private:
    std::vector<Card> cards;

public:
    Deck() {
        // Populate the deck with 52 cards
        for (int suit = HEARTS; suit <= SPADES; ++suit) {
            for (int rank = 2; rank <= 14; ++rank) {
                cards.push_back(Card{rank, static_cast<Suit>(suit)});
            }
        }
    }

    void shuffle() {
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::shuffle(cards.begin(), cards.end(), std::default_random_engine(seed));
    }

    std::vector<Card> deal(int count) {
        // Deal `count` cards and remove them from the deck
        std::vector<Card> dealtCards(cards.end() - count, cards.end());
        cards.erase(cards.end() - count, cards.end());
        return dealtCards;
    }
};
class Player {
private:
    std::vector<Card> hand;

public:
    void receiveCards(const std::vector<Card>& cards) {
        hand.insert(hand.end(), cards.begin(), cards.end());
    }

    void showHand() const {
        std::cout << "Your hand:\n";
        for (size_t i = 0; i < hand.size(); ++i) {
            std::cout << i + 1 << ": ";
            hand[i].display();
        }
    }

    std::vector<Card> selectCardsToPass() {
        std::vector<Card> selectedCards;
        std::cout << "Select 3 cards to pass by entering their numbers (1-" << hand.size() << "):\n";

        for (int i = 0; i < 3; ++i) {
            int choice;
            std::cin >> choice;

            while (choice < 1 || choice > hand.size()) {
                std::cout << "Invalid choice. Try again: ";
                std::cin >> choice;
            }

            selectedCards.push_back(hand[choice - 1]);
            hand.erase(hand.begin() + (choice - 1));

            // Re-display the hand after removing a card
            showHand();
        }

        return selectedCards;
    }
};
void passCards(std::vector<Player>& players) {
    std::vector<std::vector<Card>> cardsToPass(players.size());

    // Each player selects three cards to pass
    for (size_t i = 0; i < players.size(); ++i) {
        std::cout << "Player " << i + 1 << ", select your cards to pass.\n";
        players[i].showHand();
        cardsToPass[i] = players[i].selectCardsToPass();
    }

    // Pass the selected cards to the next player (rotate left)
    for (size_t i = 0; i < players.size(); ++i) {
        size_t nextPlayer = (i + 1) % players.size(); // Circular rotation
        players[nextPlayer].receiveCards(cardsToPass[i]);
    }

    std::cout << "Cards have been passed to the next player.\n";
}
int main() {
    std::cout << "Hearts! Avoid the hearts or Shoot the Moon!" << std::endl;

    Deck deck;
    deck.shuffle();

    // Create four players
    std::vector<Player> players(4);

    // Deal 13 cards to each player
    for (auto& player : players) {
        player.receiveCards(deck.deal(13));
    }

    // Show hands and pass cards
    passCards(players);

    std::cout << "Game over!" << std::endl;
    return 0;
}
