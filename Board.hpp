// ID: 315233486
// Mail: Eilonashwal30@gmail.com

#ifndef BOARD_HPP
#define BOARD_HPP

#include "Player.hpp"
#include "Hexagon.hpp"
#include <vector>
#include <string>
#include <map>
#include <iostream>

#define BOARD_SIZE 19

namespace ariel 
{
    class Board 
    {
    private:
        Hexagon hexagons[BOARD_SIZE]; // The board is made of 19 hexagons
        static vector<Hexagon> makeRandomBoard(); // Static function to make a random board for the game

    public:
        // Constructor
        Board(bool testBoard=false);
        ~Board();

        //getters
        Hexagon getHexagon(int index) const;
        vector<vector<int>> getVertexNeighbors(int hexagonIndex, int vertexIndex) ;

        // Place functions
        void placeRoad(int playerID, int hexagonIndex, int vertexIndex);
        void plaseSettlement(int playerID,bool firstTurn, int hexagonIndex, int vertexIndex);
        void placeCity(int playerID, int hexagonIndex, int vertexIndex);

        // other functions
        bool isRoadOnHexagonOnUse(int hexagonIndex, int vertexIndex);
        bool isSettlementOnHexagonOnUse(int hexagonIndex, int vertexIndex);
        void printBoard(bool isTest);
    };
}
#endif // BOARD_HPP
