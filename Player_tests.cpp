// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Player.h"
#include "unit_test_framework.h"

#include <iostream>

using namespace std;

TEST(test_player_get_name) {
    Player * alice = Player_factory("Alice", "Simple");
    ASSERT_EQUAL("Alice", alice->get_name());

    delete alice;
}

// Add more tests here
TEST(test_player_make_trump) {
    Player* player1 = Player_factory("player1", "Simple");
    Suit temp1;
    player1->add_card(Card(QUEEN,DIAMONDS));
    player1->add_card(Card(NINE,DIAMONDS));
    player1->add_card(Card(ACE,DIAMONDS));
    player1->add_card(Card(JACK,DIAMONDS));
    player1->add_card(Card(TEN,DIAMONDS));
    ASSERT_FALSE(player1->make_trump(Card(NINE,HEARTS),true, 1, temp1));
    ASSERT_TRUE(player1->make_trump(Card(NINE,HEARTS),true, 2, temp1));   
    ASSERT_EQUAL(temp1, DIAMONDS);   
    delete player1;

    Player* player2 = Player_factory("player1", "Simple");
    Suit temp2;
    player2->add_card(Card(NINE,DIAMONDS));
    player2->add_card(Card(KING,HEARTS));
    player2->add_card(Card(JACK,HEARTS));
    player2->add_card(Card(TEN,CLUBS));
    player2->add_card(Card(JACK,SPADES));
    ASSERT_TRUE(player2->make_trump(Card(NINE,HEARTS), true, 1, temp2));
    ASSERT_EQUAL(temp2, HEARTS);
    ASSERT_TRUE(player2->make_trump(Card(KING,CLUBS), true, 2, temp2));   
    ASSERT_EQUAL(temp2, SPADES);            
    ASSERT_TRUE(player2->make_trump(Card(KING,SPADES), true, 2, temp2));
    ASSERT_EQUAL(temp2, CLUBS); 
    delete player2;

    Player* player3 = Player_factory("player4","Simple");
    Suit temp3;
    player3->add_card(Card(JACK,CLUBS));
    player3->add_card(Card(NINE,DIAMONDS));
    player3->add_card(Card(JACK,DIAMONDS));
    player3->add_card(Card(JACK,SPADES));
    player3->add_card(Card(JACK,HEARTS));
    ASSERT_TRUE(player3->make_trump(Card(NINE,HEARTS),true, 1, temp3));
    ASSERT_EQUAL(temp3, HEARTS); 
    ASSERT_TRUE(player3->make_trump(Card(KING,CLUBS),false, 1, temp3));
    ASSERT_EQUAL(temp3, CLUBS); 
    ASSERT_TRUE(player3->make_trump(Card(KING,SPADES),true, 1, temp3));   
    ASSERT_EQUAL(temp3, SPADES); 
    ASSERT_TRUE(player3->make_trump(Card(KING,DIAMONDS),false, 1, temp3));
    ASSERT_EQUAL(temp3, DIAMONDS); 
    delete player3;

    Player* player4 = Player_factory("player3","Simple");
    Suit temp4;
    player4->add_card(Card(TEN,DIAMONDS));
    player4->add_card(Card(JACK,HEARTS));
    player4->add_card(Card(QUEEN,SPADES));
    player4->add_card(Card(KING,HEARTS));
    player4->add_card(Card(NINE,DIAMONDS));
    ASSERT_FALSE(player4->make_trump(Card(KING,CLUBS),true, 1, temp4));
    ASSERT_TRUE(player4->make_trump(Card(KING,CLUBS),true, 2, temp4));   
    ASSERT_EQUAL(temp4, SPADES);                       
    delete player4;
}

TEST(test_player_add_and_discard) {
    Player * player1 = Player_factory("player1","Simple");
    player1->add_card(Card(TEN,CLUBS));
    player1->add_card(Card(QUEEN,HEARTS));
    player1->add_card(Card(NINE,CLUBS));
    player1->add_card(Card(QUEEN,DIAMONDS));
    player1->add_card(Card(NINE,SPADES));
    player1->add_and_discard(Card(QUEEN,CLUBS));
    ASSERT_EQUAL(player1->lead_card(CLUBS), Card(QUEEN,DIAMONDS));
    delete player1; 

    Player * player2 = Player_factory("player3","Simple");
    player2->add_card(Card(JACK,CLUBS));
    player2->add_card(Card(QUEEN,CLUBS));
    player2->add_card(Card(QUEEN,DIAMONDS));
    player2->add_card(Card(QUEEN,HEARTS));
    player2->add_card(Card(QUEEN,SPADES));
    player2->add_and_discard(Card(JACK,SPADES));
    ASSERT_EQUAL(player2->lead_card(SPADES), Card(QUEEN,DIAMONDS));
    ASSERT_EQUAL(player2->lead_card(SPADES), Card(QUEEN,CLUBS));
    ASSERT_EQUAL(player2->lead_card(SPADES), Card(JACK,SPADES));
    ASSERT_EQUAL(player2->lead_card(SPADES), Card(JACK,CLUBS));
    ASSERT_EQUAL(player2->lead_card(SPADES), Card(QUEEN,SPADES));
    delete player2;

    Player * player3 = Player_factory("player2", "Simple");
    player3->add_card(Card(TEN,CLUBS));
    player3->add_card(Card(TEN,CLUBS));
    player3->add_card(Card(TEN,CLUBS));
    player3->add_card(Card(TEN,CLUBS));
    player3->add_card(Card(TEN,CLUBS));
    player3->add_and_discard((Card(QUEEN,CLUBS)));
    ASSERT_EQUAL(player3->lead_card(HEARTS), Card(QUEEN,CLUBS));
    delete player3;   
}

TEST(test_player_lead_card_basic){
     Player * player1 = Player_factory("player1","Simple");
     player1->add_card(Card(NINE,HEARTS));
     player1->add_card(Card(TEN,HEARTS));
     player1->add_card(Card(JACK,HEARTS));
     player1->add_card(Card(QUEEN,HEARTS));
     player1->add_card(Card(ACE,HEARTS));
     ASSERT_EQUAL(player1->lead_card(SPADES), Card(ACE,HEARTS));
     ASSERT_EQUAL(player1->lead_card(SPADES), Card(QUEEN,HEARTS));
     delete player1;  

     Player * player2 = Player_factory("player2","Simple");
     player2->add_card(Card(QUEEN,HEARTS));
     player2->add_card(Card(JACK,CLUBS));
     player2->add_card(Card(JACK,SPADES));
     player2->add_card(Card(TEN,HEARTS));
     player2->add_card(Card(QUEEN,SPADES));
     ASSERT_EQUAL(player2->lead_card(SPADES), Card(QUEEN,HEARTS));
     ASSERT_EQUAL(player2->lead_card(SPADES), Card(TEN,HEARTS));
     delete player2; 

     Player * player3 = Player_factory("player3","Simple");
     player3->add_card(Card(QUEEN,SPADES));
     player3->add_card(Card(ACE,SPADES));
     player3->add_card(Card(KING,SPADES));
     player3->add_card(Card(JACK,CLUBS));
     ASSERT_EQUAL(player3->lead_card(SPADES), Card(JACK,CLUBS));
     delete player3; 
 
     Player * player4 = Player_factory("player4","Simple");
     player4->add_card(Card(ACE,DIAMONDS));
     player4->add_card(Card(ACE,CLUBS));
     player4->add_card(Card(JACK,DIAMONDS));
     player4->add_card(Card(ACE,HEARTS));
     player4->add_card(Card(JACK,HEARTS));
     ASSERT_EQUAL(player4->lead_card(SPADES), Card(ACE,DIAMONDS));
     delete player4; 
 
     Player * player5 = Player_factory("player5","Simple");
     player5->add_card(Card(ACE,DIAMONDS));
     player5->add_card(Card(JACK,CLUBS));
     player5->add_card(Card(JACK,DIAMONDS));
     player5->add_card(Card(JACK,SPADES));
     player5->add_card(Card(JACK,HEARTS));
     ASSERT_EQUAL(player5->lead_card(SPADES), Card(ACE,DIAMONDS));
     ASSERT_EQUAL(player5->lead_card(SPADES), Card(JACK,DIAMONDS));
     ASSERT_EQUAL(player5->lead_card(SPADES), Card(JACK,HEARTS));
     ASSERT_EQUAL(player5->lead_card(SPADES), Card(JACK,SPADES));
     ASSERT_EQUAL(player5->lead_card(SPADES), Card(JACK,CLUBS));
     delete player5; 
 }

 TEST(test_player_print_name){
    Player * player1 = Player_factory("player1", "Simple");
    ostringstream ostring;
    ostringstream result;
    ostring << *player1;
    result << "player1";

    ASSERT_EQUAL(ostring.str(),result.str());
    delete player1;
}

 TEST(test_player_play_card){
     Player * player1 = Player_factory("player2","Simple");
     player1->add_card(Card(NINE,DIAMONDS));
     player1->add_card(Card(JACK,CLUBS));
     player1->add_card(Card(KING,SPADES));
     player1->add_card(Card(QUEEN,CLUBS));
     player1->add_card(Card(TEN,SPADES));
     ASSERT_EQUAL(player1->play_card(Card(ACE,CLUBS), DIAMONDS), Card(QUEEN,CLUBS));
     ASSERT_EQUAL(player1->play_card(Card(KING,CLUBS), DIAMONDS),  Card(JACK,CLUBS));
     ASSERT_EQUAL(player1->play_card(Card(QUEEN,SPADES), DIAMONDS),Card(KING,SPADES));
     ASSERT_EQUAL(player1->play_card(Card(JACK,HEARTS), DIAMONDS),Card(NINE,DIAMONDS));
     ASSERT_EQUAL(player1->play_card(Card(TEN,DIAMONDS), DIAMONDS),Card(TEN, SPADES));
     delete player1;

     Player * player2 = Player_factory("player1","Simple");
     player2->add_card(Card(JACK,DIAMONDS));
     player2->add_card(Card(TEN,SPADES));
     player2->add_card(Card(QUEEN,CLUBS));
     player2->add_card(Card(JACK,HEARTS));
     player2->add_card(Card(ACE,HEARTS));
     ASSERT_EQUAL(player2->play_card(Card(ACE,CLUBS), DIAMONDS),Card(QUEEN,CLUBS));
     ASSERT_EQUAL(player2->play_card(Card(QUEEN,CLUBS), DIAMONDS),  Card(TEN,SPADES));
     delete player2; 

     Player * player3 = Player_factory("player3","Simple");
     player3->add_card(Card(ACE,CLUBS));
     player3->add_card(Card(QUEEN,HEARTS));
     player3->add_card(Card(JACK,DIAMONDS));
     player3->add_card(Card(KING,SPADES));
     player3->add_card(Card(NINE,CLUBS));
     ASSERT_EQUAL(player3->play_card(Card(KING,CLUBS),HEARTS), Card(ACE,CLUBS));
     ASSERT_EQUAL(player3->play_card(Card(KING,SPADES), HEARTS),Card(KING,SPADES));
     ASSERT_EQUAL(player3->play_card(Card(KING,DIAMONDS), HEARTS),Card(NINE,CLUBS));
     ASSERT_EQUAL(player3->play_card(Card(JACK,SPADES), HEARTS),Card(QUEEN,HEARTS));
     ASSERT_EQUAL(player3->play_card(Card(JACK,HEARTS), HEARTS),Card(JACK, DIAMONDS));
     delete player3;

     Player * player4 = Player_factory("player4","Simple");
     player4->add_card(Card(KING,CLUBS));
     player4->add_card(Card(QUEEN,DIAMONDS));
     player4->add_card(Card(KING,DIAMONDS));
     player4->add_card(Card(KING,SPADES));
     player4->add_card(Card(JACK,HEARTS));
     ASSERT_EQUAL(player4->play_card(Card(ACE,CLUBS),DIAMONDS), Card(KING,CLUBS));
     ASSERT_EQUAL(player4->play_card(Card(ACE,SPADES), DIAMONDS),Card(KING,SPADES));
     ASSERT_EQUAL(player4->play_card(Card(TEN,CLUBS), DIAMONDS),Card(QUEEN,DIAMONDS));
     delete player4;

    Player * player5 = Player_factory("player6", "Simple");
     player5->add_card(Card(NINE,HEARTS));
     player5->add_card(Card(JACK,HEARTS));
     player5->add_card(Card(JACK,DIAMONDS));
     ASSERT_EQUAL(player5->play_card( Card (ACE, HEARTS), DIAMONDS), Card(NINE,HEARTS));                                                                                         
     delete player5; 

    Player * player6 = Player_factory("player5","Simple");
    player6->add_card(Card(TEN,CLUBS));
    player6->add_card(Card(QUEEN,CLUBS));
    player6->add_card(Card(ACE,CLUBS));
    player6->add_card(Card(JACK,CLUBS));
    player6->add_card(Card(NINE,CLUBS));
    ASSERT_EQUAL(player6->play_card(Card(ACE,SPADES), SPADES), Card(JACK,CLUBS)); 
    ASSERT_EQUAL(player6->play_card(Card(KING,CLUBS), DIAMONDS), Card(ACE,CLUBS));   
    delete player6;
 }

TEST_MAIN()
