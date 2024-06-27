// ID: 315233486
// Mail: Eilonashwal30@gmail.com

#include "Vertex.hpp"
#include "Player.hpp"
#include <iostream>



namespace ariel 
{
    Vertex:: Vertex ()
    {
       this->idPlayerOwner = -1; // no owner on the start
       this->isCollect = false; // not collectable on the start
       this->sturcture = NO_STRUCTURE; // no structure on the start
    }

    //getters

    int Vertex:: getIDPlayerOwner() const  { return this->idPlayerOwner; }

    int Vertex:: getSturcture() const { return this->sturcture; }

    //setters

    void Vertex:: setIDPlayerOwner(int idPlayer) { this->idPlayerOwner = idPlayer; }

    void Vertex:: setSturcture(int structure) { this->sturcture = structure; }

    // inUse functions

    bool Vertex:: isOnUseByStructure() const { return this->sturcture != -1; }

    bool Vertex:: isOnUseByPlayer(int idPlayer) const { return this->idPlayerOwner == idPlayer; }

    // collect functions
    void Vertex:: collect() { this->isCollect = true; }

    bool Vertex:: isCollectable() const { return this->isCollect; }

    // place functions

    void Vertex:: placeRoad(int idPlayer) 
    {
        if (isOnUseByStructure())
        {
            throw std::invalid_argument("The Vertex is already used");
        }
        {
            this->setIDPlayerOwner(idPlayer);
            this->setSturcture(ROAD);
        }
    }

    void Vertex:: placeSettlement(int idPlayer) 
    {
        if (isOnUseByStructure())
        {
            throw std::invalid_argument("The Vertex is already used");
        }
        {
            this->setIDPlayerOwner(idPlayer);
            this->setSturcture(SETTLEMENT);
        }
    }    
    
    void Vertex:: placeCity() 
    {
        this->setSturcture(CITY);
    }

    bool Vertex:: isSturctureOfPlayer(int idPlayer) const  // check if the structure is of the player
    { 
        if(isOnUseByStructure()) // if the vertex is in use
            return getIDPlayerOwner() == idPlayer;
        return false;
    }

}