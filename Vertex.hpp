// ID: 315233486
// Mail: Eilonashwal30@gmail.com

#ifndef VERTEX_HPP
#define VERTEX_HPP
#include <string>
#include "Player.hpp"

#define NO_STRUCTURE -1
#define ROAD 1
#define SETTLEMENT 2
#define CITY 3

using namespace std;

namespace ariel
{
    class Vertex
    {
    private:
        int idPlayerOwner;
        int sturcture; // -1 = no structure, 1 = Road, 2 = Settlement, 3 = City
        bool isCollect;


    public:
        // Constructor
        Vertex();

        // Getters
        int getIDPlayerOwner() const;
        int getSturcture() const;

        // Setters
        void setIDPlayerOwner(int id);
        void setSturcture(int structure);

        // Other functions
        bool isOnUseByStructure() const;
        bool isOnUseByPlayer(int idPlayer) const;

        void placeRoad(int idPlayer);
        void placeSettlement(int idPlayer);
        void placeCity();
        bool isSturctureOfPlayer(int idPlayer) const;

        // Collect Function
        void collect();
        bool isCollectable() const;

    };
} 





#endif // VERTEX_HPP