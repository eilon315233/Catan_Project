// ID: 315233486
// Mail: Eilonashwal30@gmail.com

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>
#include <vector>
#include <memory>

using namespace std;

namespace ariel 
{   
    class DevelopmentCard; // Forward declaration

    class Player 
    {
        private:
            static int numberOfPlayers; // Static variable to count the number of players (until 3 players)
            string name;
            int playerID;
            int resources[5]; // Array to store the number of resources of each type (in the following order: WOOD, BRICK, SHEEP, WHEAT, IRON)
            int points; // The number of points the player has
            vector<shared_ptr<DevelopmentCard>> developmentCards; // Vector to store the development cards the player has

        public:
            Player(); // Default constructor
            Player(string name);
            
            ~Player(); // Destructor
            
            // Getters functions
            string getName() const;
            int getPoints() const;
            int getPlayerID() const;

            // Functions to manipulate resources
            void addResource(int resourceType, int amount);
            void removeResource(int resourceType, int amount);
            int getResource(int resourceType) const;
            int getResourcesCount() const;
            void printResources() const;
            void overSevenResources();


            // Functions to manipulate development cards
            void buyDevelopmentCard(shared_ptr<DevelopmentCard> card);
            void deleteDevelopmentCard(int index);
            shared_ptr<DevelopmentCard> getCardByIndex(int index);
            int useDevelopmentCard( int cardIndex);
            int getCardCount() const;
            void printDevelopmentCards();
            void clearAllDevelopmentCard();
            int numOfKnights();

            // Function to add points to the player
            void addPoints(int amount);           
    };
}

#endif // PLAYER_HPP

