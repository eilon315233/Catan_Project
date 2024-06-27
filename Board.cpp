// ID: 315233486
// Mail: Eilonashwal30@gmail.com

#include "Board.hpp"
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <random>
#include <iomanip>
#include <sstream>
#include <chrono>
#include <stdexcept>


using namespace ariel;
using namespace std;


Board::Board(bool testBoard) 
{
    if(testBoard) // For testing, initialize the board with a Board that I chose from a picture of the game
    {
        hexagons[0] = Hexagon(10,IRON);
        hexagons[1] = Hexagon(2,SHEEP);
        hexagons[2] = Hexagon(9,WOOD);
        hexagons[3] = Hexagon(12,WHEAT);
        hexagons[4] = Hexagon(6,BRICK);
        hexagons[5] = Hexagon(4,SHEEP);
        hexagons[6] = Hexagon(10,BRICK);
        hexagons[7] = Hexagon(9,WHEAT);
        hexagons[8] = Hexagon(11,WOOD);
        hexagons[9] = Hexagon(0,DESERT);
        hexagons[10] = Hexagon(3,WOOD);
        hexagons[11] = Hexagon(8,IRON);
        hexagons[12] = Hexagon(8,WOOD);
        hexagons[13] = Hexagon(3,IRON);
        hexagons[14] = Hexagon(4,WHEAT);
        hexagons[15] = Hexagon(5,SHEEP);
        hexagons[16] = Hexagon(5,BRICK);
        hexagons[17] = Hexagon(6,WHEAT);
        hexagons[18] = Hexagon(11,SHEEP);
        return;
    }
    else // For the real game, initialize the board with random resources
    {
        for (int i = 0; i < BOARD_SIZE; ++i) 
        {
            hexagons[i] = Hexagon(); // Initialize all hexagons with default constructor
        }

        vector<Hexagon> randomBoard = makeRandomBoard(); // make a random board for the game

        for (size_t i = 0; i < randomBoard.size(); ++i) 
        {
            hexagons[i] = randomBoard[i]; // Copy the random board to the game board
        }
    }
}

Board::~Board(){} // Destructor

vector<Hexagon> Board::makeRandomBoard() 
{
    // Define resources and their counts (excluding the desert)
    std::vector<int> resources = {
        WOOD, WOOD, WOOD, WOOD,  // 4 forests
        BRICK, BRICK, BRICK,     // 3 hills
        SHEEP, SHEEP, SHEEP, SHEEP, // 4 pastures
        WHEAT, WHEAT, WHEAT, WHEAT, // 4 fields
        IRON, IRON, IRON,        // 3 mountains
        DESERT // 1 desert
    };

    // Define the numbers for the tiles (excluding the desert)
    std::vector<int> numbers = { 
        2, 3, 3, 4, 4, 5, 5, 6, 6, 8, 8, 9, 9, 10, 10, 11, 11, 12
    };

    // Shuffle resources
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(resources.begin(), resources.end(), std::default_random_engine(seed));

    // Shuffle numbers
    std::shuffle(numbers.begin(), numbers.end(), std::default_random_engine(seed));

    int numberIndex = 0;
    std::vector<Hexagon> ans(BOARD_SIZE);  // Resize the vector to the board size
    // Assign resources and numbers to lands
    for (int i = 0; i < BOARD_SIZE; ++i) {
        int resource = resources[i];
        int number;
        if (resource == DESERT)
            number = 0;  // desert
        else
            number = numbers[numberIndex++];
        ans[i] = Hexagon(number, resource);
    }
    return ans;
}

bool Board::isRoadOnHexagonOnUse(int hexagonIndex, int vertexIndex) // check if there is a road on a specific vertex of a hexagon
{
    return hexagons[hexagonIndex].isRoadVertexOnUse(vertexIndex);
}

bool Board::isSettlementOnHexagonOnUse(int hexagonIndex, int vertexIndex) // check if there is a settlement on a specific vertex of a hexagon
{
    return hexagons[hexagonIndex].isSettlementVertexOnUse(vertexIndex);
}

Hexagon Board::getHexagon(int index) const
{
    return hexagons[index];
}

void Board::placeRoad(int playerID, int hexagonIndex, int vertexIndex) // check if a road can be placed on a specific vertex of a hexagon
{
    // Check if there is a road on the vertex
    if (isRoadOnHexagonOnUse(hexagonIndex, vertexIndex))
    {
        throw invalid_argument("Can't place a road3 at the position ("+to_string(hexagonIndex)+","+to_string(vertexIndex)+")");
    }

    //Check if there are a settlement or a city of the player on the vertex or on the next vertex (road can be placed frome this vertex or the next one)
    if( hexagons[hexagonIndex].getSettlementVertex(vertexIndex).isOnUseByPlayer(playerID) || 
    hexagons[hexagonIndex].getSettlementVertex((vertexIndex+1)%6).isOnUseByPlayer(playerID) )
    {
        hexagons[hexagonIndex].placeRoad(playerID, vertexIndex);
        return;
    }
    
    // Reset the neighbor indexes
    int neighborHexagonIndex = -1;
    int neighborVertexIndex = -1;
    
    // Check Neighbors: (All the check is according to the TestBoard)

    // check if the road is between two hexagons

    if(vertexIndex == 0) // Top left neighbor (hexagon: 4,5,6,8,9,10,11,12,13,14,15,16,17,18)
    {
        if ((hexagonIndex>=4 && hexagonIndex<=6)||(hexagonIndex>=16&& hexagonIndex<=18)) //4,5,6 ,16,17,18
        {
            neighborHexagonIndex = hexagonIndex-4; // The hexagon index of the road's neighbor
            neighborVertexIndex = 3; // The vertex index of the road's neighbor
        }
        if(hexagonIndex>=8&& hexagonIndex<=15) //8-15
        {
            neighborHexagonIndex = hexagonIndex-5; // The hexagon index of the road's neighbor
            neighborVertexIndex = 3; // The vertex index of the road's neighbor
        }
    }

    if(vertexIndex==1) // Top right neighbor (hexagon: 3,4,5,7,8,9,10,12,13,14,15,16,17,18)
    {
        if ((hexagonIndex>=3 && hexagonIndex<=5)||(hexagonIndex>=16&& hexagonIndex<=18)) //3,4,5 ,16,17,18
        {
            neighborHexagonIndex = hexagonIndex-3; // The hexagon index of the road's neighbor
            neighborVertexIndex = 4; // The vertex index of the road's neighbor
        }
        if(hexagonIndex>=7&&hexagonIndex!= 11&&hexagonIndex<=18) //7-18 without 11
        {
            neighborHexagonIndex = hexagonIndex-4; // The hexagon index of the road's neighbor
            neighborVertexIndex = 4; // The vertex index of the road's neighbor
        }
    }
    
    if(vertexIndex==2) // Right neighbor (hexagon: 0,1,3,4,5,7,8,9,10,12,13,14,16,17)
    {
        if(!(hexagonIndex==2||hexagonIndex==6||hexagonIndex==11||hexagonIndex==15||hexagonIndex==18)) //without 2,6,11,15,18
        {
            neighborHexagonIndex = hexagonIndex+1; // The hexagon index of the road's neighbor
            neighborVertexIndex = 5; // The vertex index of the road's neighbor
        }
    }
    
    if(vertexIndex==3) // Bottom right neighbor (hexagon: 0,1,2,3,4,5,6,7,8,9,10,12,13,14)
    {
        if((hexagonIndex>=0&&hexagonIndex<=2)||(hexagonIndex<=14 && hexagonIndex>=12)) //0,1,2 , 12,13,14
        {
            neighborHexagonIndex = hexagonIndex+4; // The hexagon index of the road's neighbor
            neighborVertexIndex = 0; // The vertex index of the road's neighbor
        }

        if (hexagonIndex>=3 && hexagonIndex<=10) //3-10
        {
            neighborHexagonIndex = hexagonIndex+5; // The hexagon index of the road's neighbor
            neighborVertexIndex = 0; // The vertex index of the road's neighbor
        }
    }
    
    if(vertexIndex == 4) // Bottom left neighbor (hexagon: 0,1,2,3,4,5,6,8,9,10,11,13,14,15)
    {
        if((hexagonIndex>=0&&hexagonIndex<=3)||(hexagonIndex>=13&& hexagonIndex<=15)) //0-3, 13-15
        {
            neighborHexagonIndex = hexagonIndex+3; // The hexagon index of the road's neighbor
            neighborVertexIndex = 1;  // The vertex index of the road's neighbor
        }
        if (hexagonIndex>=4 && hexagonIndex<=11 && hexagonIndex!= 7) //4-11 withot 7
        {
            neighborHexagonIndex = hexagonIndex+4; // The hexagon index of the road's neighbor
            neighborVertexIndex = 1; // The vertex index of the road's neighbor
        }
    }

    if(vertexIndex==5) // Left neighbor (hexagon: 1,2,4,5,6,8,9,10,11,13,14,15,17,18)
    {
        if(!(hexagonIndex==0||hexagonIndex==3||hexagonIndex==7||hexagonIndex==12||hexagonIndex==16)) //without 0,3,7,12,16
        {
            neighborHexagonIndex = hexagonIndex-1; // The hexagon index of the road's neighbor
            neighborVertexIndex = 2; // The vertex index of the road's neighbor
        }
    }

    //Check if there is another road of the player on the before vertex or the next vertex
    if(hexagons[hexagonIndex].getRoadVertex((vertexIndex+1)%6).isOnUseByPlayer(playerID) || hexagons[hexagonIndex].getRoadVertex((vertexIndex+5)%6).isOnUseByPlayer(playerID))
    {
        hexagons[hexagonIndex].placeRoad(playerID,vertexIndex); // Place the road on the vertex

        if(neighborVertexIndex != -1) // If the road has a neighbor - place the road also on the neighbor
            hexagons[neighborHexagonIndex].placeRoad(playerID,neighborVertexIndex);
        return;
    }


    if(neighborVertexIndex == -1) // We dont find a neighbor, check if there is a road on other hexagon that near this road
    {
        bool nearRoad=false; // On the beginning be fale, if we find a road near the road we will change it to true

        if(vertexIndex==0)
        {
            if(hexagonIndex==3)
                nearRoad=hexagons[hexagonIndex-3].getRoadVertex(5).isSturctureOfPlayer(playerID);
            else if(hexagonIndex==7)
                nearRoad=hexagons[hexagonIndex-4].getRoadVertex(5).isSturctureOfPlayer(playerID);
            else if(hexagonIndex==1||hexagonIndex==2)
                nearRoad=hexagons[hexagonIndex-1].getRoadVertex(1).isSturctureOfPlayer(playerID);
        }

        else if(vertexIndex==1&&(hexagonIndex<=1))
            nearRoad=hexagons[hexagonIndex+1].getRoadVertex(1).isSturctureOfPlayer(playerID);
            
        else if(vertexIndex==2)
        {
            if(hexagonIndex==2)
                nearRoad=this->hexagons[hexagonIndex+4].getOwnerOfRoadVertex(1)==playerID;
            else if(hexagonIndex==6)
                nearRoad=this->hexagons[hexagonIndex+5].getOwnerOfRoadVertex(1)==playerID;
        }

        else if(vertexIndex==3)
        {
            if(hexagonIndex==11)
                nearRoad=hexagons[hexagonIndex+4].getRoadVertex(2).isSturctureOfPlayer(playerID);
            else if(hexagonIndex==15)
                nearRoad=hexagons[hexagonIndex+3].getRoadVertex(2).isSturctureOfPlayer(playerID);
        }

        else if(vertexIndex==4)
        {
            if(hexagonIndex ==17||hexagonIndex==18)
                nearRoad=hexagons[hexagonIndex-1].getRoadVertex(3).isSturctureOfPlayer(playerID);
            else if(hexagonIndex==7)
                nearRoad=hexagons[hexagonIndex+5].getRoadVertex(5).isSturctureOfPlayer(playerID);
            else if(hexagonIndex==12)
                nearRoad=hexagons[hexagonIndex+5].getRoadVertex(5).isSturctureOfPlayer(playerID);
        }

        else if(vertexIndex==5)
        {
            if(hexagonIndex==0)
                nearRoad=hexagons[hexagonIndex+3].getRoadVertex(0).isSturctureOfPlayer(playerID);
            else if(hexagonIndex==3)
                nearRoad=hexagons[hexagonIndex+4].getRoadVertex(0).isSturctureOfPlayer(playerID);
        }

        if(nearRoad) // if there is a road near the road        
        {
            hexagons[hexagonIndex].placeRoad(playerID,vertexIndex); // Place the road on the vertex
        }
        else // If there is no road near the road
            throw invalid_argument("Can't place a road1 at the position ("+to_string(hexagonIndex)+","+to_string(vertexIndex)+")");
    }
    
    else // We found a neighbor but there is no road of the player near the road
    {
        // Check if one of the hexagons can place the road
        bool me = hexagons[hexagonIndex].canPlaceRoad(playerID,vertexIndex);
        bool neighbor = hexagons[neighborHexagonIndex].canPlaceRoad(playerID,neighborVertexIndex);

        if(me||neighbor) // If one of the hexagons can place the road        
        {
            hexagons[hexagonIndex].placeRoad(playerID,vertexIndex);
            hexagons[neighborHexagonIndex].placeRoad(playerID,neighborVertexIndex);
        }
        else
            throw invalid_argument("Can't place a road2 at the position ("+to_string(hexagonIndex)+","+to_string(vertexIndex)+")");
    }
}

vector<vector<int>> Board::getVertexNeighbors(int hexagonIndex,int vertexIndex) // Get the neighbors of a specific vertex of a hexagon
{
    // Initialize the indexes of the neighbors
    int neighborHexagonIndex_1 = -1;
    int neighborVertexIndex_1 = -1;
    int neighborHexagonIndex_2 = -1;
    int neighborVertexIndex_2 = -1;

    // over all the options of the vertex

        if(vertexIndex == 0 &&hexagonIndex !=0 &&hexagonIndex !=3&&hexagonIndex !=7) // Top left neighbor (hexagon: All Without 0,3,7)
        {
            //For the first neighbor
            if(hexagonIndex !=12&&hexagonIndex !=16) //1,2,4,5,6,8,9,10,11,13,14,15,17,18
            {
                neighborHexagonIndex_1= hexagonIndex-1;
                neighborVertexIndex_1=2;
            }
            
            // For the second neighbor
            if(hexagonIndex>3&&hexagonIndex !=7) //4,5,6,8,9,10,11,12,13,14,15,16,17,18
            {
                neighborVertexIndex_2=4;
                
                if((hexagonIndex>=4&&hexagonIndex<=6)||(hexagonIndex>=16)) //4,5,6,16,17,18
                    neighborHexagonIndex_2= hexagonIndex-4;
                else //8-15
                    neighborHexagonIndex_2= hexagonIndex-5;
            }
        }
        
        if(vertexIndex == 1 &&hexagonIndex >2) // Top neighbor (hexagon: All Without 0,1,2)
        {
            //For the first neighbor (hexagon: 3,6,7,11)
            if(hexagonIndex ==3)
            {
                neighborHexagonIndex_1= hexagonIndex-3;
                neighborVertexIndex_1=5;
            }
            else if(hexagonIndex ==6||hexagonIndex ==7)
            {
                neighborHexagonIndex_1= hexagonIndex-4;
                neighborVertexIndex_1=5;
                if(hexagonIndex ==6)
                    neighborVertexIndex_1=3;
            }
            else if(hexagonIndex ==11)
            {
                neighborHexagonIndex_1= hexagonIndex-5;
                neighborVertexIndex_1=3;
            }
        
            // For the second neighbor (hexagon: 4,5,8,9,10,12,13,14,15,16,17,18)
            else if(hexagonIndex==4||hexagonIndex==5||hexagonIndex>=16) // 4,5,16,17,18
            {
                neighborHexagonIndex_1=hexagonIndex-4;
                neighborVertexIndex_1=3;

                neighborHexagonIndex_2=hexagonIndex-3;
                neighborVertexIndex_2=5;
            }
            else //8,9,10,12,13,14,15
            {
                neighborHexagonIndex_1=hexagonIndex-5;
                neighborVertexIndex_1=3;

                neighborHexagonIndex_2=hexagonIndex-4;
                neighborVertexIndex_2=5;
            }
        
        }

        if(vertexIndex==2&&hexagonIndex!=2&&hexagonIndex!=6&&hexagonIndex!=11) // Top right neighbor (hexagon: All Without 2,6,11)
        {
            // For the first neighbor (hexagon: 0,1,15,18)
            if(hexagonIndex==0||hexagonIndex==1) 
            {
                neighborHexagonIndex_1=hexagonIndex+1;
                neighborVertexIndex_1= 0;
            }
            else if(hexagonIndex==15||hexagonIndex==18)
            {
                if(hexagonIndex==15)
                {
                    neighborHexagonIndex_1=11;
                    neighborVertexIndex_1= 4;
                }
                else
                {
                    neighborHexagonIndex_1=15;
                    neighborVertexIndex_1= 4;
                }
            }
            // For the second neighbor (hexagon: 3,4,5,7,8,9,10,12,13,14,16,17)
            else
            {
                neighborHexagonIndex_1=hexagonIndex+1;
                neighborVertexIndex_1= 0;
                neighborVertexIndex_2= 4;
                if(hexagonIndex<=5||hexagonIndex>=16)
                {
                    neighborHexagonIndex_2=hexagonIndex-3;
                }
                else
                    neighborHexagonIndex_2=hexagonIndex-4;
            }
        }
        
        if(vertexIndex==3&&hexagonIndex!=11&&hexagonIndex!=15&&hexagonIndex!=18)// Bottom right neighbor (hexagon: All Without 11,15,18)
        {
        // For the first neighbor - 2,6,16,17
        if(hexagonIndex==2|| hexagonIndex==6)
        {
            neighborVertexIndex_1 = 1;
            if(hexagonIndex==2)
                neighborHexagonIndex_1 = 6;
            else
            neighborHexagonIndex_1 = 11;
        }
        else if(hexagonIndex==16|| hexagonIndex==17)
        {
            neighborHexagonIndex_1= hexagonIndex+1;
            neighborVertexIndex_1=5;
        }
        //For the second neighbor - 0,1,3,4,5,7,8,9,10,12,13,14
        else
        {
            if(hexagonIndex<=1||hexagonIndex>=12) //0,1,12,13,14
            {
                neighborHexagonIndex_1=hexagonIndex+1;
                neighborVertexIndex_1 = 5;

                neighborHexagonIndex_2 = hexagonIndex+4;
                neighborVertexIndex_2 = 1;
            }
            else //3,4,5,7,8,9,10
            {
                neighborHexagonIndex_1=hexagonIndex+1;
                neighborVertexIndex_1 = 5;

                neighborHexagonIndex_2 = hexagonIndex+5;
                neighborVertexIndex_2 = 1;
            }
        }
        }
    
        if(vertexIndex==4&&hexagonIndex!=16&&hexagonIndex!=17&&hexagonIndex!=18)// Bottom neighbor (hexagon: All Without 16,17,18)
        {
            // For the first neighbor - 7,11,12,15
            if(hexagonIndex==11||hexagonIndex==12) 
            {
                neighborHexagonIndex_1=hexagonIndex+4;
                neighborVertexIndex_1=0;
            }
            else if(hexagonIndex==7)
            {
                neighborHexagonIndex_1=hexagonIndex+5;
                neighborVertexIndex_1=0;
            }
            else if(hexagonIndex==15)
            {
                neighborHexagonIndex_1=hexagonIndex+3;
                neighborVertexIndex_1=0;
            }

            // For the second neighbor - 0,1,2,3,4,5,6,8,9,10,13,14
            else
            {
                if(hexagonIndex<=2||hexagonIndex>=13) // 0,1,2,13,14
                {
                    neighborHexagonIndex_1=hexagonIndex+4;
                    neighborVertexIndex_1=0;

                    neighborHexagonIndex_2=hexagonIndex+3;
                    neighborVertexIndex_2=2;
                }
                else // 3,4,5,6,8,9,10
                {
                    neighborHexagonIndex_1=hexagonIndex+5;
                    neighborVertexIndex_1=0;

                    neighborHexagonIndex_2=hexagonIndex+4;
                    neighborVertexIndex_2=2;
                }
            }
        }
    
        if(vertexIndex==5&&hexagonIndex!=12&&hexagonIndex!=16&&hexagonIndex!=7)// Bottom left neighbor(hexagon: All Without 7,12,16)
        {
            // For the first neighbor - 0,3,17,18
            if(hexagonIndex==0)
            {
                neighborHexagonIndex_1=3;
                neighborVertexIndex_1=1;
            }
            else if(hexagonIndex==3)
            {
                neighborHexagonIndex_1=7;
                neighborVertexIndex_1=1;   
            }
            else if (hexagonIndex==17||hexagonIndex==18)
            {
                neighborHexagonIndex_1=hexagonIndex-1;
                neighborVertexIndex_1 = 3;
            }
            // For the second neighbor - 1,2,4,5,6,8,9,10,11,13,14,15 
            else
            {
                neighborHexagonIndex_1=hexagonIndex-1;
                neighborVertexIndex_1 = 3;
                if(hexagonIndex==1||hexagonIndex==2||hexagonIndex>=13) // 1,2,13,14,15
                {
                    neighborHexagonIndex_2=hexagonIndex+3;
                    neighborVertexIndex_2 = 1;
                }
                else // 4,5,6,8,9,10,11
                {
                    neighborHexagonIndex_2=hexagonIndex+4;
                    neighborVertexIndex_2 = 1;
                }
            }
        }

    // Return the neighbors as a vector with 2 vectors (each vector is a neighbor with the hexagon index and the vertex index)
    return 
    {{neighborHexagonIndex_1,neighborVertexIndex_1},{neighborHexagonIndex_2,neighborVertexIndex_2}};
}

void Board::plaseSettlement(int playerID,bool firsTurn, int hexagonIndex, int vertexIndex)
{
    //Check if there is a settlement already on use on the vertex
    if(isSettlementOnHexagonOnUse(hexagonIndex,vertexIndex))
    {
        throw invalid_argument("This vertex is already on use");
    }
    
    // get the neighbors of the vertex to a vector of vectors
    vector<vector<int>> neighbors = getVertexNeighbors(hexagonIndex,vertexIndex);

    // We put the neighbors in the matching variables
    int neighborHexagonIndex_1 = neighbors[0][0];
    int neighborVertexIndex_1 = neighbors[0][1];
    int neighborHexagonIndex_2 = neighbors[1][0];
    int neighborVertexIndex_2 = neighbors[1][1];

    
    if(neighborVertexIndex_1==-1 && neighborVertexIndex_2==-1) // if there is no neighbors to the vertex
    {
        int canPlace = hexagons[hexagonIndex].canPlaceSettlement(playerID,vertexIndex); // 0- Hard no, 1- No, 2- Yes

        // If the first turn and the vertex has no settlement near it
        if(firsTurn&&canPlace!=0)
        {
            hexagons[hexagonIndex].placeSettlement(playerID,vertexIndex); // Place the settlement
        }
        else if(canPlace >1)
        {
            this->hexagons[hexagonIndex].placeSettlement(playerID,vertexIndex); // Place the settlement
        }
        else
            throw std::invalid_argument("Can't place a settlement11 at the position("+to_string(hexagonIndex)+","+to_string(vertexIndex)+")");
    }

    else if(neighborVertexIndex_1==-1) // One neighbor (number 1)
    {
        int canPlace = hexagons[hexagonIndex].canPlaceSettlement(playerID,vertexIndex); // 0- Hard no, 1- No, 2- Yes
        canPlace*= hexagons[neighborHexagonIndex_2].canPlaceSettlement(playerID,neighborVertexIndex_2); // check if the neighbor can place a settlement

        // If the first turn and the vertex has no settlement near it
        if(firsTurn&&canPlace!=0)
        {
            //Place the settlement on the vertex and the neighbor
            this->hexagons[hexagonIndex].placeSettlement(playerID,vertexIndex);
            this->hexagons[neighborHexagonIndex_2].placeSettlement(playerID,neighborVertexIndex_2);
        }

        else if(canPlace >1) // If the vertex and the neighbor can place a settlement
        {
            //Place the settlement on the vertex and the neighbor
            this->hexagons[hexagonIndex].placeSettlement(playerID,vertexIndex);
            this->hexagons[neighborHexagonIndex_2].placeSettlement(playerID,neighborVertexIndex_2);
        }
        else
            throw std::invalid_argument("Can't place a settlement12 at the position("+to_string(hexagonIndex)+","+to_string(vertexIndex)+")");
    }
    else if(neighborVertexIndex_2==-1) // One neighbor (number 2)
    {
        int canPlace = hexagons[hexagonIndex].canPlaceSettlement(playerID,vertexIndex); // 0- Hard no, 1- No, 2- Yes
        canPlace *=hexagons[neighborHexagonIndex_1].canPlaceSettlement(playerID,neighborVertexIndex_1); // check if the neighbor can place a settlement

        // If the first turn and the vertex has no settlement near it
        if(firsTurn&&canPlace!=0)
        {
            //Place the settlement on the vertex and the neighbor
            this->hexagons[hexagonIndex].placeSettlement(playerID,vertexIndex);
            this->hexagons[neighborHexagonIndex_1].placeSettlement(playerID,neighborVertexIndex_1);
        }

        else if(canPlace >1) // If the vertex and the neighbor can place a settlement
        {
            //Place the settlement on the vertex and the neighbor
            this->hexagons[hexagonIndex].placeSettlement(playerID,vertexIndex);
            this->hexagons[neighborHexagonIndex_1].placeSettlement(playerID,neighborVertexIndex_1);
        }
        else
            throw std::invalid_argument("Can't place a settlement13 at the position("+to_string(hexagonIndex)+","+to_string(vertexIndex)+") ");
    }
    else // Two neighbors
    {
        int canPlace = this->hexagons[hexagonIndex].canPlaceSettlement(playerID,vertexIndex); // 0- Hard no, 1- No, 2- Yes
        // Check if the neighbors can place a settlement
        canPlace *= this->hexagons[neighborHexagonIndex_1].canPlaceSettlement(playerID,neighborVertexIndex_1);
        canPlace *= this->hexagons[neighborHexagonIndex_2].canPlaceSettlement(playerID,neighborVertexIndex_2);

        // If the first turn and the vertex has no settlement near it
        if(firsTurn&&canPlace!=0)
        {
            //Place the settlement on the vertex and the neighbors
            this->hexagons[hexagonIndex].placeSettlement(playerID,vertexIndex);
            this->hexagons[neighborHexagonIndex_1].placeSettlement(playerID,neighborVertexIndex_1);
            this->hexagons[neighborHexagonIndex_2].placeSettlement(playerID,neighborVertexIndex_2);
        }

        else if(canPlace >1) // If the vertex and the neighbors can place a settlement
        {
            //Place the settlement on the vertex and the neighbors
            this->hexagons[hexagonIndex].placeSettlement(playerID,vertexIndex);
            this->hexagons[neighborHexagonIndex_1].placeSettlement(playerID,neighborVertexIndex_1);
            this->hexagons[neighborHexagonIndex_2].placeSettlement(playerID,neighborVertexIndex_2);
        }
        else
            throw std::invalid_argument("Can't place a settlement14 at the position("+to_string(hexagonIndex)+","+to_string(vertexIndex)+")");
    }

}

void Board::placeCity(int playerID, int hexagonIndex, int vertexIndex)
{
        // get the neighbors of the vertex to a vector of vectors
        vector<vector<int>> neighbors = getVertexNeighbors(hexagonIndex,vertexIndex);

        // We put the neighbors in the matching variables
        int neighborHexagonIndex_1 = neighbors[0][0];
        int neighborVertexIndex_1 = neighbors[0][1];
        int neighborHexagonIndex_2 = neighbors[1][0];
        int neighborVertexIndex_2 = neighbors[1][1];
        
        // Place the city on the vertex
        hexagons[hexagonIndex].placeCity(playerID,vertexIndex);

        // If there is a neighbor, place the city on the neighbor
        if(neighborVertexIndex_1==-1 && neighborVertexIndex_2==-1)//No neighbor
            return;

        else if(neighborVertexIndex_1==-1)// Number 2 is a neighbor
            this->hexagons[neighborHexagonIndex_2].placeCity(playerID,neighborVertexIndex_2);    
        
        else if(neighborVertexIndex_2==-1)// Number 1 is a neighbor
            this->hexagons[neighborHexagonIndex_1].placeCity(playerID,neighborVertexIndex_1);
        
        else // Both are neighbors
        {
            this->hexagons[neighborHexagonIndex_1].placeCity(playerID,neighborVertexIndex_1);
            this->hexagons[neighborHexagonIndex_2].placeCity(playerID,neighborVertexIndex_2);
        }
}

void Board::printBoard(bool isTest) // Print the board 
{
    if(isTest) // If it is a test board - choosen by me
    {
    cout<<endl;
    cout << "\t This is the Board: (choosen by me)" << endl;
    }
    else // If it is a real board - choosen randomly
    {
    cout<<endl;
    cout << "\t This is the Board: (choosen randomly)" << endl;
    }

    for (int i = 0; i < BOARD_SIZE; ++i) 
    {
            if(i==0||i==3||i==7||i==12||i==16)
                cout << endl;
            if(i==7)
                cout<<"\t";
            if(i==0||i==16)//Tab twice
                cout << "\t\t";
            else if(i==3||i==12)//Tab once
                cout << "\t    ";
            this->hexagons[i].printHexagon();
    }
        cout<<endl;
        cout<<endl;
}
    


