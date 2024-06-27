// ID: 315233486
// Mail: Eilonashwal30@gmail.com

#include "Hexagon.hpp"
#include <iostream>

using namespace ariel;

Hexagon::Hexagon() // default constructor
{
    this->idOfHexagon = 0;
    this->resource = 0;
    for(int i = 0; i < 6; i++){
        roadVertices[i] = Vertex();
        settlementVertices[i] = Vertex();
    }
}

Hexagon::Hexagon(int idOfHexagon, int resource) // constructor with parameters
{
    this->idOfHexagon = idOfHexagon;
    this->resource = resource;
    for(int i = 0; i < 6; i++){
        roadVertices[i] = Vertex();
        settlementVertices[i] = Vertex();
    }
}

int Hexagon::getIdOfHexagon(){ return this->idOfHexagon; }

int Hexagon::getResource(){ return this->resource; }

string Hexagon::getResourceName() // returns the name of the resource
{
    switch(this->resource){
        case WOOD:
            return "Wood";
        case BRICK:
            return "Brick";
        case SHEEP:
            return "Sheep";
        case WHEAT:
            return "Wheat";
        case IRON:
            return "Iron";
        case DESERT:
            return "Desert";
        default:
            return "invalid resource";
    }
}

Vertex& Hexagon::getRoadVertex(int index){ return roadVertices[index]; }

Vertex& Hexagon::getSettlementVertex(int index){ return settlementVertices[index]; }

bool Hexagon::isRoadVertexOnUse(int index){ return roadVertices[index].isOnUseByStructure(); }

bool Hexagon::isSettlementVertexOnUse(int index){ return settlementVertices[index].isOnUseByStructure(); }

int Hexagon::getOwnerOfRoadVertex(int index){ return roadVertices[index].getIDPlayerOwner(); }

int Hexagon::getOwnerOfSettlementVertex(int index){ return settlementVertices[index].getIDPlayerOwner(); }

bool Hexagon::canPlaceRoad(int playerID, int vertexIndex) // checks if a road can be placed on the Hexagon
{
    // neighbors of the vertex
    int rightVertexNeighbor = (vertexIndex + 1) % 6; // right neighbor
    int leftVertexNeighbor = (vertexIndex + 5) % 6; // left neighbor

    // check if there is a road on the neighbors of the vertex

    if(isRoadVertexOnUse(rightVertexNeighbor)) // right neighbor
    {
        if(getOwnerOfRoadVertex(rightVertexNeighbor) == playerID){
            return true;
        }
    }

    if(isRoadVertexOnUse(leftVertexNeighbor)) // left neighbor
    {
        if(getOwnerOfRoadVertex(leftVertexNeighbor) == playerID){
            return true;
        }
    }

    // check if there is a settlement on the neighbor vertex

    if(isSettlementVertexOnUse(rightVertexNeighbor)) // right neighbor
    {
        if(getOwnerOfSettlementVertex(rightVertexNeighbor) == playerID){
            return true;
        }
    }

    if(isSettlementVertexOnUse(leftVertexNeighbor)) // left neighbor
    {
        if(getOwnerOfSettlementVertex(leftVertexNeighbor) == playerID){
            return true;
        }
    }

    return false; // if no road can be placed
}

void Hexagon::placeRoad(int playerID, int vertexIndex) // places a road on the Hexagon
{
    roadVertices[vertexIndex].placeRoad(playerID);
}

int Hexagon::canPlaceSettlement(int playerID, int vertexIndex) // checks if a settlement can be placed on the Hexagon
{
    // Hard no: 0
    // No: 1
    // Yes: 2

    int neighborIndex = (vertexIndex + 5) % 6; // left neighbor
    int neighborIndex2 = (vertexIndex + 1) % 6; // right neighbor

    // check if there is a settlement or a city - on distance of 2 roads from the vertex - Hard no
    if(isSettlementVertexOnUse(neighborIndex) || isSettlementVertexOnUse(neighborIndex2) || isSettlementVertexOnUse(vertexIndex))
    {
        return 0; // Hard no
    }

    //Check for a road from the vertex or from the neighbors - Yes
    
    if((isRoadVertexOnUse(vertexIndex) && getOwnerOfRoadVertex(vertexIndex)==playerID) // 
    || (isRoadVertexOnUse(neighborIndex) && getOwnerOfRoadVertex(neighborIndex)==playerID)) 
    {
        return 2; //Yes
    }

    return 1; //No
}

void Hexagon::placeSettlement(int playerID, int vertexIndex) // places a settlement on the Hexagon
{
    settlementVertices[vertexIndex].placeSettlement(playerID);
}

void Hexagon::placeCity(int playerID, int vertexIndex) // places a city on the Hexagon
{
    Vertex& vertex = getSettlementVertex(vertexIndex);
    int structureType = vertex.getSturcture();

    if(structureType==NO_STRUCTURE)
        throw invalid_argument("There is no settlement in the vertex - Error in the board, in vertex: " + to_string(vertexIndex));
    if(structureType==ROAD)
        throw invalid_argument("There is a road in the vertex - Error in the board, in vertex: " + to_string(vertexIndex));
    if(structureType==CITY)
        throw invalid_argument("There is already a city in the vertex - Error in the board, in vertex: " + to_string(vertexIndex));

    // Check if the player is the owner of the vertex
    if(vertex.getIDPlayerOwner() !=playerID)
        throw invalid_argument("The player is not the owner of the vertex - Error in the board, in vertex: " + to_string(vertexIndex));
        
    // Place the city
    vertex.placeCity(); 
}

void Hexagon::printHexagon() // prints the Hexagon
{
    cout <<  getResourceName() <<":"<<this->idOfHexagon<<" "; // print the resource and the id of the Hexagon
}

 bool Hexagon::isSett(int playerID) // checks if the player can collect resources from the Hexagon
 {
    for(size_t i=0;i<6;i++)
    {
        if(playerID == settlementVertices[i].getIDPlayerOwner() && settlementVertices[i].isCollectable()==false)
        {
            settlementVertices[i].collect();
            return true;
            i--;
        }
    }
    return false;
}






   



    






