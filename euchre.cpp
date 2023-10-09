// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Pack.h"
#include "Player.h"
#include <cassert>
#include <iostream>
#include <string>
#include <fstream>
#include <string.h>

using namespace std;

class Game {
 public:
  Game(istream &pack_file, string shuf, int ptw, vector<Player*>player_list){
    players = player_list;
    pack = Pack(pack_file);
    if (shuf == "shuffle") {
        pack.shuffle();
        shuffle = true;
    }else{
        shuffle = false;
    }
    score_02 = 0;
    score_13 = 0;
    order_up_02 = false;
    order_up_13 = false;
    points2win = ptw;
  }
  void play(){
    assert(!pack.empty());
    int hand = 0;
    int dealer = 0;
    while(score_02<points2win&&score_13<points2win){
        int leader = (dealer+1)%4;
        deal(hand, dealer);
        Suit order_up_suit;
        make_trump(dealer, order_up_suit);
        trump = order_up_suit;
        play_hand(leader);
        leader = (leader+1)%4;
        pack.reset();
        if(shuffle) pack.shuffle();
        hand++;
        dealer=(dealer+1)%4;
        order_up_02 = false;
        order_up_13 = false;
    }

    if(score_02>score_13){
        cout<<players[0]->get_name()<<" and "<<players[2]->get_name()<<
        " win!"<<endl;
    }else{
        cout<<players[1]->get_name()<<" and "<<players[3]->get_name()<<
        " win!"<<endl;       
    }


  }

  ~Game(){
    for (size_t i = 0; i < players.size(); ++i) delete players[i];
  }

 private:
  std::vector<Player*> players;
  bool shuffle;
  Pack pack;
  Suit trump;
  Card upcard;
  int score_02;
  int score_13;
  bool order_up_02;
  bool order_up_13;
  int points2win;

  void deal(int hand, int dealer){
    // Deal Cards
    cout<<"Hand "<<hand<<endl;
    cout<<players[dealer]->get_name()<<" deals"<<endl;
    // First round
    for(size_t i = 0; i < players.size(); ++i){
        int cur_p = (dealer+i+1)%4;
        int num_cards;
        if(i%2==0) num_cards=3;
        else num_cards = 2;
        for(int j = 0; j<num_cards; j++){
            players[cur_p]->add_card(pack.deal_one());
        }
    }
    // Second round
    for(size_t i = 0; i < players.size(); ++i){
        int cur_p = (dealer+i+1)%4;
        int num_cards;
        if(i%2==0) num_cards=2;
        else num_cards = 3;
        for(int j = 0; j<num_cards; j++){
            players[cur_p]->add_card(pack.deal_one());
        }
    }
    // Getting the upcard
    upcard = pack.deal_one();
    cout<<upcard<<" turned up"<<endl;
  }

  void make_trump(int dealer, Suit &order_up_suit){
    // Round 1
    for(size_t i = 0; i < players.size(); ++i){
        int cur_p = (dealer+1+i)%4;
        bool ifdealer = ((int)cur_p==dealer);
        if(players[cur_p]->make_trump(upcard, ifdealer, 1, order_up_suit)) {
            cout << players[cur_p]->get_name() << " orders up "<<
                order_up_suit<<endl<<endl;
            players[dealer]->add_and_discard(upcard);   
            if(cur_p%2==0) order_up_02 = true;
            else order_up_13 = true;
            return;
        }
        cout << players[cur_p]->get_name() << " passes"<<endl;
    }
    // Round 2
    for(size_t i = 0; i < players.size(); ++i){
        int cur_p = (dealer+1+i)%4;
        bool ifdealer = ((int)i==dealer);
        if(players[cur_p]->make_trump(upcard, ifdealer, 2, order_up_suit)) {
            if(cur_p%2==0) order_up_02 = true;
            else order_up_13 = true;
            cout << players[cur_p]->get_name() << " orders up "<<
                order_up_suit<<endl<<endl;
            return;
        }
        cout << players[cur_p]->get_name() << " passes"<<endl;
    }
  }
  void play_trick(int &leader, int& tc02, int& tc13){
    vector<Card> cards_played;
    vector<int> players_num;
    Card led_card;
    Card max_card;
    for(size_t i=0; i< players.size(); ++i){
        int cur_player = (leader+i)%4;
        if(cur_player==leader){
            led_card = players[cur_player]->lead_card(trump);
            cout<<led_card<<" led by "<<players[cur_player]->get_name()<<endl;
            max_card = led_card;
            players_num.push_back(cur_player);
            cards_played.push_back(led_card);
        }else{
            cards_played.push_back(players[cur_player]->play_card(
                led_card, trump));
            cout<<cards_played.at(i)<<" played by "
                <<players[cur_player]->get_name()<<endl;
            players_num.push_back(cur_player);
            if(Card_less(max_card, cards_played.at(i),led_card, trump)){
                max_card = cards_played.at(i);
            }
        }
    }


    // Determining the winner
    int winner;
    for(size_t i=0; i< players.size(); ++i){
        if(cards_played.at(i)==max_card){
            winner = players_num[i];
        }
    }
    cout<<players[winner]->get_name()<<" takes the trick"<<endl<<endl;
    if (winner%2==0) tc02++;
    else tc13++;
    leader = winner;
    return;
  }
  
  void play_hand(int &leader){
    int tc02 = 0;
    int tc13 = 0;
    for(int i=0; i<5; i++){
        play_trick(leader, tc02, tc13);
    }
    if(tc02>tc13){
        cout<<players[0]->get_name()<<" and "<<
        players[2]->get_name()<<" win the hand"<<endl;
        if(order_up_02){
            if(tc02==5) {
                cout<<"march!"<<endl;
                score_02 = score_02+2;
            }
            if(tc02==4||tc02==3) score_02++;
        }
        else {
            cout<<"euchred!"<<endl;
            score_02=score_02+2;
        }
    }else{
        cout<<players[1]->get_name()<<" and "<<
        players[3]->get_name()<<" win the hand"<<endl;
        if(order_up_13){
            if(tc13==5) {
                cout<<"march!"<<endl;
                score_13 = score_13+2;
            }
            if(tc13==4||tc13==3) score_13++;
        }
        else {
            cout<<"euchred!"<<endl;
            score_13=score_13+2;
        }
    }
    cout<<players[0]->get_name()<<" and "<<
        players[2]->get_name()<<" have "<<
        score_02<<" points"<<endl;  
    cout<<players[1]->get_name()<<" and "<<
        players[3]->get_name()<<" have "<<
        score_13<<" points"<<endl<<endl;
    
  }

};


int main(int argc, char *argv[]) {
    // Check conditions
//    if(argc!=12||stoi(argv[3])>100||stoi(argv[3])<0||
//        (argv[2]!="shuffle"&&argv[2]!="noshuffle")||
//        (argv[5]!="Simple"&&argv[5]!="Human")||    
//        (argv[7]!="Simple"&&argv[7]!="Human")||    
//        (argv[9]!="Simple"&&argv[9]!="Human")||    
//        (argv[11]!="Simple"&&argv[11]!="Human")){
    for(int i=0; i<argc; i++){
        cout<<argv[i]<<" ";
    }
    cout<<endl;

    if(argc!=12||stoi(argv[3])>100||stoi(argv[3])<0||
        (strcmp(argv[2], "shuffle")!=0&&strcmp(argv[2], "noshuffle")!=0)||
        (strcmp(argv[5], "Simple")!=0&&strcmp(argv[5], "Human")!=0)||
        (strcmp(argv[7], "Simple")!=0&&strcmp(argv[7], "Human")!=0)||
        (strcmp(argv[9], "Simple")!=0&&strcmp(argv[9], "Human")!=0)||
        (strcmp(argv[11], "Simple")!=0&&strcmp(argv[11], "Human")!=0)){
    cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
     << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
     << "NAME4 TYPE4" << endl;
     return -1;
    }

    // Open file
    ifstream infile(argv[1], ifstream::in);
    if (!infile.is_open())
    {
        cout << "Error opening " << argv[1] << endl;
        exit(0);
    };

    vector<Player*> player_list; 
    Player* p1 = Player_factory(argv[4], argv[5]);
    player_list.push_back(p1);
    Player* p2 = Player_factory(argv[6], argv[7]);
    player_list.push_back(p2);
    Player* p3 = Player_factory(argv[8], argv[9]);
    player_list.push_back(p3);
    Player* p4 = Player_factory(argv[10], argv[11]);
    player_list.push_back(p4);

    Game newgame(infile, argv[2], stoi(argv[3]), player_list);

    newgame.play();


    return 0;
}