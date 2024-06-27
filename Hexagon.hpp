// ID: 315233486
// Mail: Eilonashwal30@gmail.com

#ifndef HEXAGON_HPP
#define HEXAGON_HPP

#include "Vertex.hpp"

#define WOOD 0
#define BRICK 1
#define SHEEP 2
#define WHEAT 3
#define IRON 4
#define DESERT -1

namespace ariel{
    
    class Hexagon{

        private:
            Vertex roadVertices[6];// 0: top left, 1: top, 2: top right, 3: bottom right, 4: bottom, 5: bottom left
            Vertex settlementVertices[6];// 0: top left, 1: top right, 2: right, 3: bottom right, 4: bottom left, 5: left
            int idOfHexagon; // 2-12
            int resource; // 0-4

        public:
             // Constructor
            Hexagon();
            Hexagon(int idOfHexagon, int resource);

            // Getters
            int getIdOfHexagon();
            int getResource(); 
            string getResourceName();

            // Getters for vertices
            Vertex& getRoadVertex(int index);
            Vertex& getSettlementVertex(int index);
            bool isRoadVertexOnUse(int index);
            bool isSettlementVertexOnUse(int index);
            int getOwnerOfRoadVertex(int index);
            int getOwnerOfSettlementVertex(int index);

            // place functions
            bool canPlaceRoad(int playerNum, int vertexIndex);
            void placeRoad(int playerNum, int vertexIndex);
            int canPlaceSettlement(int playerNum, int vertexIndex);
            void placeSettlement(int playerNum, int vertexIndex);
            void placeCity(int playerNum, int vertexIndex);


            void printHexagon();
            bool isSett(int playerNum);
    };
}
#endif // HEXAGON_HPP
