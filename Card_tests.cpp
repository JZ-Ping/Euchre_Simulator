// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Card.h"
#include "unit_test_framework.h"
#include <iostream>

using namespace std;


TEST(test_card_ctor) {
    Card c(ACE, HEARTS);
    ASSERT_EQUAL(ACE, c.get_rank());
    ASSERT_EQUAL(HEARTS, c.get_suit());
}

// Add more test cases here
TEST(test_card_default) {
    Card d = Card();
    ASSERT_EQUAL(TWO, d.get_rank());
    ASSERT_EQUAL(SPADES, d.get_suit());
}

TEST(test_card_3_get) {
    Card c1 = Card(JACK, SPADES);
    Card c2 = Card(JACK, CLUBS);
    Card c3 = Card(ACE, SPADES);
    Card c4 = Card(ACE, CLUBS);
    Card c5 = Card(ACE, HEARTS);
    Card c6 = Card(ACE, DIAMONDS);

    ASSERT_EQUAL(JACK, c1.get_rank());
    ASSERT_EQUAL(SPADES, c1.get_suit());
    ASSERT_EQUAL(SPADES, c1.get_suit(SPADES));
    ASSERT_EQUAL(JACK, c2.get_rank());
    ASSERT_EQUAL(CLUBS, c2.get_suit());
    ASSERT_EQUAL(SPADES, c2.get_suit(SPADES));
    ASSERT_EQUAL(ACE, c3.get_rank());
    ASSERT_EQUAL(SPADES, c3.get_suit());
    ASSERT_EQUAL(SPADES, c3.get_suit(SPADES));
    ASSERT_EQUAL(ACE, c4.get_rank());
    ASSERT_EQUAL(CLUBS, c4.get_suit());
    ASSERT_EQUAL(CLUBS, c4.get_suit(SPADES));
    ASSERT_EQUAL(ACE, c5.get_rank());
    ASSERT_EQUAL(HEARTS, c5.get_suit());
    ASSERT_EQUAL(HEARTS, c5.get_suit(SPADES));
    ASSERT_EQUAL(ACE, c6.get_rank());
    ASSERT_EQUAL(DIAMONDS, c6.get_suit());
    ASSERT_EQUAL(DIAMONDS, c6.get_suit(SPADES));
}

TEST(test_card_4_is) {
    Card c1 = Card(JACK, SPADES);
    Card c2 = Card(JACK, CLUBS);
    Card c3 = Card(ACE, SPADES);
    Card c4 = Card(ACE, CLUBS);
    Card c5 = Card(ACE, HEARTS);
    Card c6 = Card(ACE, DIAMONDS);
    Card c7 = Card(TWO, HEARTS);
    Card c8 = Card(TWO, DIAMONDS);

    ASSERT_TRUE(c1.is_face_or_ace());
    ASSERT_TRUE(c1.is_right_bower(SPADES));
    ASSERT_FALSE(c1.is_left_bower(SPADES));
    ASSERT_TRUE(c1.is_trump(SPADES));
    ASSERT_TRUE(c2.is_face_or_ace());
    ASSERT_FALSE(c2.is_right_bower(SPADES));
    ASSERT_TRUE(c2.is_left_bower(SPADES));
    ASSERT_TRUE(c2.is_trump(SPADES));
    ASSERT_TRUE(c3.is_face_or_ace());
    ASSERT_FALSE(c3.is_right_bower(SPADES));
    ASSERT_FALSE(c3.is_left_bower(SPADES));
    ASSERT_TRUE(c3.is_trump(SPADES));
    ASSERT_TRUE(c4.is_face_or_ace());
    ASSERT_FALSE(c4.is_right_bower(SPADES));
    ASSERT_FALSE(c4.is_left_bower(SPADES));
    ASSERT_FALSE(c4.is_trump(SPADES));
    ASSERT_TRUE(c5.is_face_or_ace());
    ASSERT_FALSE(c5.is_right_bower(SPADES));
    ASSERT_FALSE(c5.is_left_bower(SPADES));
    ASSERT_FALSE(c5.is_trump(SPADES));
    ASSERT_TRUE(c6.is_face_or_ace());
    ASSERT_FALSE(c6.is_right_bower(SPADES));
    ASSERT_FALSE(c6.is_left_bower(SPADES));
    ASSERT_FALSE(c6.is_trump(SPADES));
    ASSERT_FALSE(c7.is_face_or_ace());
    ASSERT_FALSE(c7.is_right_bower(SPADES));
    ASSERT_FALSE(c7.is_left_bower(SPADES));
    ASSERT_FALSE(c7.is_trump(SPADES));
    ASSERT_FALSE(c8.is_face_or_ace());
    ASSERT_FALSE(c8.is_right_bower(SPADES));
    ASSERT_FALSE(c8.is_left_bower(SPADES));
    ASSERT_FALSE(c8.is_trump(SPADES));
}

TEST(test_iostream) {
    std::string c1 = "Jack of Spades";
    Card testCard = Card(JACK, SPADES);
    ostringstream os;
    ostringstream ans;
    os << testCard;
    ans << c1;
    ASSERT_EQUAL(os.str(), ans.str());
}

TEST(test_compare) {
    Card c1 = Card(ACE, CLUBS);
    Card c2 = Card(ACE, SPADES);
    Card c3 = Card(TEN, SPADES);

    ASSERT_FALSE(c1 > c1);
    ASSERT_TRUE(c1 >= c1);
    ASSERT_FALSE(c1 < c1);
    ASSERT_TRUE(c1 <= c1);
    ASSERT_FALSE(c1 != c1);
    ASSERT_TRUE(c1 == c1);
    ASSERT_TRUE(c2 > c3);
    ASSERT_FALSE(c3 >= c2);
    ASSERT_TRUE(c3 < c2);
    ASSERT_FALSE(c2 <= c3);
    ASSERT_TRUE(c2 != c3);
    ASSERT_FALSE(c2 == c3);
    ASSERT_TRUE(c1 > c2);
    ASSERT_FALSE(c2 >= c1);
    ASSERT_TRUE(c2 < c1);
    ASSERT_FALSE(c1 <= c2);
    ASSERT_TRUE(c1 != c2);
    ASSERT_FALSE(c1 == c2);
    ASSERT_TRUE(c2 > c3);
    ASSERT_FALSE(c3 >= c2);
    ASSERT_TRUE(c3 < c2);
    ASSERT_FALSE(c2 <= c3);
    ASSERT_TRUE(c2 != c3);
    ASSERT_FALSE(c2 == c3);
}

TEST(test_card_less) {
    Card c1a = Card(JACK, SPADES);
    Card c1b = Card(TEN, SPADES);
    Card c1c = Card(ACE, SPADES);
    Card c2a = Card(JACK, DIAMONDS);
    Card c2b = Card(TEN, SPADES);
    Card c2c = Card(ACE, HEARTS);
    Card c2d = Card(KING, CLUBS);
    Card c3a = Card(JACK, DIAMONDS);
    Card c3b = Card(ACE, HEARTS);
    Card c3c = Card(JACK, HEARTS);
    Card lead_3 = Card(KING, HEARTS);
    Card c4a = Card(JACK, DIAMONDS);
    Card c4b = Card(ACE, DIAMONDS);
    Card lead_4 = Card(JACK, HEARTS);
    Card hand5_a = Card(JACK, DIAMONDS);

    ASSERT_TRUE(Card_less(c1b, c1a, SPADES));
    ASSERT_FALSE(Card_less(c1a, c1c, SPADES));
    ASSERT_TRUE(Card_less(c1b, c1c, SPADES));
    ASSERT_TRUE(Card_less(c1b, c1a, c1c, SPADES));
    ASSERT_FALSE(Card_less(c1a, c1c, c1b, SPADES));
    ASSERT_TRUE(Card_less(c1b, c1c, c1a, SPADES)); 
    ASSERT_FALSE(Card_less(c2b, c2a, SPADES));
    ASSERT_FALSE(Card_less(c2a, c2c, HEARTS));
    ASSERT_TRUE(Card_less(c2b, c2c, DIAMONDS));
    ASSERT_FALSE(Card_less(c2b, c2a, c2c, SPADES));
    ASSERT_FALSE(Card_less(c2a, c2c, c2b, HEARTS));
    ASSERT_TRUE(Card_less(c2b, c2c, c2a, DIAMONDS)); 
    ASSERT_TRUE(Card_less(c2b, c2c, c2a, DIAMONDS)); 
    ASSERT_TRUE(Card_less(c2c, c2d, c2d, DIAMONDS));
    ASSERT_FALSE(Card_less(c3a, c3b, HEARTS));
    ASSERT_TRUE(Card_less(c3a, c3c, HEARTS));
    ASSERT_TRUE(Card_less(c3b, c3c, HEARTS));
    ASSERT_FALSE(Card_less(c3a, c3b, lead_3, HEARTS));
    ASSERT_FALSE(Card_less(c3a, lead_3, lead_3, HEARTS));
    ASSERT_FALSE(Card_less(c4a, c4b, DIAMONDS));
    ASSERT_FALSE(Card_less(c4a, c4b, lead_4, DIAMONDS));
    ASSERT_FALSE(Card_less(c4a, lead_4, lead_4, DIAMONDS));
    ASSERT_FALSE(Card_less(hand5_a, hand5_a, HEARTS));
    ASSERT_FALSE(Card_less(hand5_a, hand5_a, hand5_a,HEARTS));
}

TEST_MAIN()
