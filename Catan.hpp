// ID: 315233486
// Mail: Eilonashwal30@gmail.com

#ifndef CATAN_HPP
#define CATAN_HPP
#include "Player.hpp"
#include "Board.hpp"
#include <vector>
#include <string>
#include <iostream>
#include <memory>

//incloding all the DevelopCards folder
#include "DevelopmentCards/DevelopmentCard.hpp"
#include "DevelopmentCards/KnightCard.hpp"
#include "DevelopmentCards/MonopolyCard.hpp"
#include "DevelopmentCards/RoadBuildingCard.hpp"
#include "DevelopmentCards/VictoryPointCard.hpp"
#include "DevelopmentCards/YearOfPlentyCard.hpp"

namespace ariel
{
    class Catan
    {
        private:
        vector<Player*> players; // vector of players 
        Board board; // the board of the game
        int playerTurn;// the current player turn: 1-player1, 2-player2, 3-player3
        vector<shared_ptr<DevelopmentCard>> devePack; // the development cards pack

        public:
        Catan(Player& p1, Player& p2, Player& p3, bool isTest=false); //Constructor
        ~Catan(); //destructor

        //getters
        Board& getBoard();
        int getPlayerTurn()const;
        Player& getPlayerByName(string name);
        Player& getPlayer(int num);
        Player& getCurrentPlayer();
        string getResorcesName(int resorceType);

        //Place functions
        void placeSettlement(int playerNum, int landIndex, int spotIndex);
        void placeRoad(int playerNum, int landIndex, int spotIndex);
        void placeCity(int playerNum, int landIndex, int spotIndex);

        //Game functions
        void rollDice(int playerNum);
        void rollDice(int playerNum, int dice);
        void ChooseStartingPlayer(bool isTest=false);
        void endPlayerTurn(int playerNum);
        bool checkWinner(int playerNum);
        void tradeResorces(int p1, int p2, int res1, int res2, int amount1, int amount2);
        void tradeDevelopmentCard(int p1, int p2, int cardIndex1, int cardIndex2);\
        void chooseResorces(int playerNum);
        void addResource(int playerNum,int resourceType, int amount);
        void addPoints(int playerNum,int amount);
        void updateResourceByDice(int dice);

        //Print functions
        void printPoints();
        void printWinner();
        void printBoard(bool isTest);
        void printDevelopmentCards(int playerNum);
        
        //Development card functions
        void buyDevelopmentCard(int playerNum);
        void useDevelopmentCard(int playerNum, int cardIndex, bool isTest=false);
        void initializeDevePack(bool isTest=false);
    };
}
#endif // CATAN_HPP