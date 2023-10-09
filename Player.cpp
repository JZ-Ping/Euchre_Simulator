// Project UID 1d9f47bfc76643019cfbf037641defe1
#include "Player.h"
#include <algorithm>
#include <cassert>

using namespace std;

class SimplePlayer: public Player{
  public:
    // Simple Player class constructor
    SimplePlayer(const string &name):player_name(name){};

    //EFFECTS returns player's name
    const std::string & get_name() const override{
      return player_name;
    };

    //REQUIRES player has less than MAX_HAND_SIZE cards
    //EFFECTS  adds Card c to Player's hand
    void add_card(const Card &c) override{
      assert(hand.size()<=MAX_HAND_SIZE);
      Card card_new = c;
      hand.push_back(card_new);
      //sort(hand.begin(), hand.end(), greater<Card>());
    };

    //REQUIRES round is 1 or 2
    //MODIFIES order_up_suit
    //EFFECTS If Player wishes to order up a trump suit then return true and
    //  change order_up_suit to desired suit.  If Player wishes to pass, then do
    //  not modify order_up_suit and return false.
    bool make_trump(const Card &upcard, bool is_dealer,
                          int round, Suit &order_up_suit) 
                          const override{

      Suit up_suit = upcard.get_suit();
      // Consider the case with round 
      if(round==1){
        int count_face_ace = 0;
        for(unsigned long int i=0; i<hand.size(); i++){
          if(hand[i].is_face_or_ace()&&hand[i].get_suit(up_suit)==up_suit){
            count_face_ace++;
          }
        }
        // If there are more cards that satisfies, return true(ie make trump)
        if(count_face_ace>=2) {
          order_up_suit = up_suit;
          return true;
        }
        return false;
      }
      // Same color suit
      Suit next_suit = Suit_next(up_suit);
      if(round==2){
        if(is_dealer){
          order_up_suit = next_suit;
          return true;
        }
        for(unsigned long int i=0; i<hand.size(); i++){
          if(hand[i].is_face_or_ace()&&hand[i].get_suit(next_suit)==next_suit){
            order_up_suit = next_suit;
            return true;
          }
        }
        return false;
      }
      return false;
    };

  //REQUIRES Player has at least one card
  //EFFECTS  Player adds one card to hand and removes one card from hand.
  void add_and_discard(const Card &upcard) override{
    assert(hand.size()>=1);
    Card new_card = upcard;
    //vector<Card> temp_hand = hand;
    //temp_hand.push_back(new_card);
    add_card(new_card);
    Suit trump = upcard.get_suit();
    sort_hand(trump);
    hand.pop_back();
    //vector<Card> temp_hand_new;
    //while(!temp_hand.empty()){
    //    Card max_card = temp_hand[0];
    //    int max_pos = 0;
    //    for(unsigned long int i=1; i<temp_hand.size(); i++){
    //      if(Card_less(max_card, temp_hand[i], trump)){
    //        max_pos = i;
    //        max_card = temp_hand[i];
    //      }
    //    }
    //    temp_hand.erase(hand.begin()+max_pos);
    //    temp_hand_new.push_back(max_card);
    //  }
    //  temp_hand = temp_hand_new;
    //temp_hand.pop_back();
    //hand = temp_hand;
  };
  
  //REQUIRES Player has at least one card
  //EFFECTS  Leads one Card from Player's hand according to their strategy
  //  "Lead" means to play the first Card in a trick.  The card
  //  is removed the player's hand.
  Card lead_card(Suit trump) override{
    assert(hand.size()>=1);
    sort_hand(trump);
    unsigned long int num_trump = 0;
    for(unsigned long int i=0; i<hand.size();++i){
      if(hand[i].is_trump(trump)) num_trump++;
    }
    // If all of the cards are trump cards
    if(num_trump==hand.size()){
      Card lead = hand[0];
      hand.erase(hand.begin());
      return lead;
    }
    // Other cases
    for(unsigned long int i=0; i<hand.size();++i){
      if(!hand[i].is_trump(trump)){
        Card lead = hand[i];
        hand.erase(hand.begin()+i);
        return lead;
      }
    }
    //Unexpected Behavior
    assert(false);
  };
  
  //REQUIRES Player has at least one card
  //EFFECTS  Plays one Card from Player's hand according to their strategy.
  //  The card is removed from the player's hand.
  Card play_card(const Card &led_card, Suit trump) override{
    assert(hand.size()>=1);
    sort_hand(trump, led_card);
    Suit led_suit = led_card.get_suit(trump);
    // If a led_suit card is found in hand
    for(unsigned long int i=0; i<hand.size();i++){
      if(hand[i].get_suit(trump)==led_suit){
        Card play = hand[i];
        hand.erase(hand.begin()+i);
        return play;
      }
    }
    //for(size_t i=0; i<hand.size(); i++){
    //  cout<<hand[i]<<endl;
    //}
    // Play the lowest card at hand
    Card play = hand[hand.size()-1];
    hand.pop_back();
    return play;
  }

  private:
    const string player_name;
    vector<Card> hand;

    //REQUIRES at least one card in hand
    //EFFECTS sords the hand in descending order considering trump
    void sort_hand(Suit trump){
      vector<Card> hand_new;
      while(!hand.empty()){
        Card max_card = hand[0];
        int max_pos = 0;
        for(unsigned long int i=1; i<hand.size(); i++){
          if(Card_less(max_card, hand[i], trump)){
            max_pos = i;
            max_card = hand[i];
          }
        }
        hand.erase(hand.begin()+max_pos);
        hand_new.push_back(max_card);
      }
      hand = hand_new;
    }

    void sort_hand(Suit trump, const Card &led_card){
      vector<Card> hand_new;
      while(!hand.empty()){
        Card max_card = hand[0];
        int max_pos = 0;
        for(unsigned long int i=1; i<hand.size(); i++){
          if(Card_less(max_card, hand[i], led_card, trump)){
            max_pos = i;
            max_card = hand[i];
          }
        }
        hand.erase(hand.begin()+max_pos);
        hand_new.push_back(max_card);
      }
      hand = hand_new;
    }
};


class HumanPlayer: public Player{
  public:
    HumanPlayer(const string &name):player_name(name){};

    //REQUIRES player has less than MAX_HAND_SIZE cards
    //EFFECTS  adds Card c to Player's hand
    void add_card(const Card &c) override{
      Card new_card = c;
      assert(hand.size()<MAX_HAND_SIZE);
      hand.push_back(new_card);
      sort(hand.begin(), hand.end());
    };

    //REQUIRES round is 1 or 2
    //MODIFIES order_up_suit
    //EFFECTS If Player wishes to order up a trump suit then return true and
    //  change order_up_suit to desired suit.  If Player wishes to pass, then do
    //  not modify order_up_suit and return false.
    bool make_trump(const Card &upcard, bool is_dealer,
                          int round, Suit &order_up_suit) 
                          const override{
      //sort(hand.begin(), hand.end());
      //print_hand();
      vector<Card> hand_sort = hand;
      sort(hand_sort.begin(), hand_sort.end());
      print_hand();

      cout<<"Human player "<<player_name<<", please enter a suit, or \"pass\":\n";
      string decision;
      cin >> decision;
      //if(round==2) assert(string_to_suit(decision)!=order_up_suit);
      if(decision != "pass"){
        order_up_suit = string_to_suit(decision);
        return true;
      }else{
        assert(!is_dealer||round!=2);
        return false;
      }     
    };

    //REQUIRES Player has at least one card
    //EFFECTS  Player adds one card to hand and removes one card from hand.
    void add_and_discard(const Card &upcard) override{
      assert(hand.size()>=1);
      sort(hand.begin(), hand.end());
      print_hand();
      cout<< "Discard upcard: [-1]\n";
      cout << "Human player " << player_name << ", please select a card to discard:\n";
      string decision;
      cin >> decision;
      int num = stoi(decision);
      if(num==-1){
        return;
      }else{
        assert(num>=0&&num<(int)hand.size());
        hand.erase(hand.begin()+num);
        Card new_card = upcard;
        hand.push_back(new_card);
      }
    };

    //REQUIRES Player has at least one card
    //EFFECTS  Leads one Card from Player's hand according to their strategy
    //  "Lead" means to play the first Card in a trick.  The card
    //  is removed the player's hand.
    Card lead_card(Suit trump) override{
      assert(hand.size()>0);
      sort(hand.begin(), hand.end());
      print_hand();
      cout << "Human player " << player_name << ", please select a card:\n";
      string decision;
      cin >> decision;
      unsigned long int num = stoi(decision);
      assert(num>=0&&num<hand.size());
      Card lead_card = hand[num];
      hand.erase(hand.begin()+num);
      return lead_card;
    };

    //REQUIRES Player has at least one card
    //EFFECTS  Plays one Card from Player's hand according to their strategy.
    //  The card is removed from the player's hand.
    Card play_card(const Card &led_card, Suit trump) override{
      assert(hand.size()>0);
      sort(hand.begin(), hand.end());
      print_hand();
      cout << "Human player " << player_name << ", please select a card:\n";
      string decision;
      cin >> decision;
      unsigned long int num = stoi(decision);
      assert(num>=0&&num<hand.size());
      Card play_card = hand[num];
      hand.erase(hand.begin()+num);
      return play_card;
    };

    //EFFECTS returns player's name
    const std::string & get_name() const override{
      return player_name;
    };

  private:
    const string player_name;
    vector<Card> hand;
    // Prints out the hand of the human player
    void print_hand() const {
      for (size_t i=0; i < hand.size(); ++i)
      cout << "Human player " << player_name << "'s hand: "
           << "[" << i << "] " << hand[i] << "\n";
    };
};

//EFFECTS: Returns a pointer to a player with the given name and strategy
//To create an object that won't go out of scope when the function returns,
//use "return new Simple(name)" or "return new Human(name)"
//Don't forget to call "delete" on each Player* after the game is over
Player * Player_factory(const std::string &name, const std::string &strategy) {
  // We need to check the value of strategy and return 
  // the corresponding player type.
  if (strategy == "Simple") {
    // The "new" keyword dynamically allocates an object.
    return new SimplePlayer(name);
  }
    if (strategy == "Human") {
    // The "new" keyword dynamically allocates an object.
    return new HumanPlayer(name);
  }
  assert(false);
  return nullptr;
}

//EFFECTS: Prints player's name to os
std::ostream & operator<<(std::ostream &os, const Player &p) {
  os<<p.get_name();
  return os;
}


