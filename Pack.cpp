// Project UID 1d9f47bfc76643019cfbf037641defe1
#include "Pack.h"
#include "Card.h"
#include <cassert>
#include <iostream>
#include <array>

// EFFECTS: Initializes the Pack to be in the following standard order:
//          the cards of the lowest suit arranged from lowest rank to
//          highest rank, followed by the cards of the next lowest suit
//          in order from lowest to highest rank, and so on.
// NOTE: The standard order is the same as that in pack.in.
// NOTE: Do NOT use pack.in in your implementation of this function
Pack::Pack(){
    int count = 0;
    next = 0;
    for(int s = SPADES; s<=DIAMONDS; ++s){
        for(int r = NINE; r<=ACE; ++r){
            Card card = Card(static_cast<Rank>(r),static_cast<Suit>(s));
            cards[count] = card;
            count++;
        }
    }
}
  
// REQUIRES: pack_input contains a representation of a Pack in the
//           format required by the project specification
// MODIFIES: pack_input
// EFFECTS: Initializes Pack by reading from pack_input.
Pack::Pack(std::istream& pack_input){
    next = 0;
    for(int i=0; i<PACK_SIZE; i++){
        if(pack_input>>cards[i]);
    }
}

// REQUIRES: cards remain in the Pack
// EFFECTS: Returns the next card in the pack and increments the next index
Card Pack::deal_one(){
    assert(!empty());
    next++;
    //std::cout<<cards[0]<<std::endl;
    return(cards[next-1]);
}

// EFFECTS: Resets next index to first card in the Pack
void Pack::reset(){
    next = 0;
}

// EFFECTS: Shuffles the Pack and resets the next index. This
//          performs an in shuffle seven times. See
//          https://en.wikipedia.org/wiki/In_shuffle.
void Pack::shuffle(){
    for(int i=0; i<7; i++){ //Shuffle for seven times
        std::array<Card, PACK_SIZE> cards_old = cards;
        int pos_new = 0;
        for(int pos=PACK_SIZE/2; pos<PACK_SIZE; pos++){
            cards[pos_new] = cards_old[pos];
            pos_new = pos_new+2;
        }
        pos_new = 1;
        for(int pos=0; pos<PACK_SIZE/2; pos++){
            cards[pos_new] = cards_old[pos];
            pos_new = pos_new+2;
        }
        //std::array<Card, PACK_SIZE/2> first_half;
        //std::array<Card, PACK_SIZE/2> second_half;
        //for(int i=0; i<PACK_SIZE/2; i++){
        //    first_half[i] = cards[i];
        //    second_half[i] = cards[i+PACK_SIZE/2];
        //}
        //for(int i=0; i<PACK_SIZE/2; i++){
        //    cards[2*i] = second_half[i];
        //}
        //for(int i=0; i<PACK_SIZE/2; i++){
        //    cards[2*i+1] = first_half[i];
        //}

    }
    reset();
   // std::cout<<"Here"<<std::endl;
}

// EFFECTS: returns true if there are no more cards left in the pack
bool Pack::empty() const{
    return next>=PACK_SIZE;
}