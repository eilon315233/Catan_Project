// ID: 315233486
// Mail: Eilonashwal30@gmail.com

#include "Player.hpp"
#include "Catan.hpp"
#include <iostream>
#include <string>


using namespace ariel;

    int Player::numberOfPlayers = 0; // initialize the static variable
    
    Player::Player() { Player("Diffult_Player");} // Default constructor using the other constructor

    Player::Player(string name) // other constructor
    {
        for (int i = 0; i < 5; ++i) 
        {
            resources[i] = 0; // Initialize all resources to 0
        }
        this->name = name;
        this->points = 0;
        numberOfPlayers++; // The first player will have the ID 1
        this->numberOfPlayers = numberOfPlayers; 
        this->developmentCards = vector<shared_ptr<DevelopmentCard>>();
    }

    Player::~Player() {} // Destructor

    // Getters functions
    int Player::getPoints() const{ return this->points;}
    
    int Player::getPlayerID() const{ return this->playerID;}

    string Player::getName() const { return this->name;}

    // Functions to manipulate resources
    void Player::addResource(int resourceType, int amount) // Add resources to the player
    {
        if (resourceType >= 0 && resourceType < 5) 
            resources[resourceType] += amount;
        else
            throw out_of_range("Invalid resource type " + to_string(resourceType));
    }

    void Player::removeResource(int resourceType, int amount) // Remove resources from the player
    {
        if (resourceType >= 0 && resourceType < 5) 
        {
            resources[resourceType] -= amount;
        }
        else if(resources[resourceType] < amount)
            throw out_of_range("Not enough resources to remove");
        else
            throw out_of_range("Invalid resource type " + to_string(resourceType)); // If the resource type is invalid
    }

    int Player::getResource(int resourceType) const  // Get the amount of resources of a specific type
    {
        if (resourceType >= 0 && resourceType < 5)
            return resources[resourceType];
        else
            throw out_of_range( "Invalid resource type"); // If the resource type is invalid
    }

    void Player::printResources() const // Print the resources of the player
    {
        cout << "Player " << this->name << " has the following resources:" << endl;
        cout << "WOOD: " << resources[WOOD] << endl;
        cout << "BRICK: " << resources[BRICK] << endl;
        cout << "SHEEP: " << resources[SHEEP] << endl;
        cout << "WHEAT: " << resources[WHEAT] << endl;
        cout << "IRON: " << resources[IRON] << endl;
    }

    int Player::getResourcesCount() const // Get the total number of resources the player has
    {
        int sum = 0;
        for (int i = 0; i < 5; ++i) 
        {
            sum += resources[i];
        }
        return sum;
    }

    void Player::overSevenResources() // Check if the player has more than 7 resources
    {
        if(getResourcesCount() < 8) // If the player has less than 8 resources, no need to discard resources
            return; 

        else
        {
            int half = getResourcesCount() / 2;
            cout << "Player " << this->name << " has more than 7 resources, must discard " << half << " resources" << endl;
            cout << "Please choose the resources you want to discard" << endl;
            printResources();
        }
    }

    // Functions to manipulate development cards
     void Player::buyDevelopmentCard(shared_ptr<DevelopmentCard> card) // Buy a development card
     {
        this->developmentCards.push_back(card); // Add the card to the player's vector of development cards
    }

    shared_ptr<DevelopmentCard> Player::getCardByIndex(int index) // Get a development card at a specific index
    {
        if(index >= 0 && index < getCardCount()) // If the index is valid
            return developmentCards[index];
        else
            throw out_of_range ("Invalid card index");
    }

    int Player::getCardCount() const
    {
        return this->developmentCards.size();
    }

    void Player::printDevelopmentCards() // Print the development cards of the player
    {
        cout<<endl;
        cout << "Player " << this->name << " has the following development cards:" << endl;

        for (int i = 0; i < getCardCount(); ++i) 
        {
            string ans = getCardByIndex(i)->isUsed() ? "is used" : "is not used"; // If the card is used, print "is used", otherwise, print "is not used"
            cout << i << ".: " << getCardByIndex(i)->getTypeName() << ", " << ans << endl;
        }

        cout << endl;
    }

    int Player::useDevelopmentCard(int cardIndex) // Use a development card
    {
        if(cardIndex >= 0 && cardIndex < getCardCount()) // If the index is valid
        {
           shared_ptr<DevelopmentCard> card = getCardByIndex(cardIndex); // Get the card at the specific index
            
            if(card->isUsed()) // If the card is already used
                throw out_of_range("The card is already used");

            card->useDevelopmentCard();// Use the card
            return card->getType(); // Return the type of the card (Knight, RoadBuilding, YearOfPlenty, Monopoly)
        }
        else // If the index is invalids
            throw std::out_of_range("Invalid card index");
    }

    int Player::numOfKnights()  // Get the number of knight cards the player has
    {
        int count = 0;
        for (int i = 0; i < this->getCardCount(); ++i) {
            if(getCardByIndex(i)->getType() == KNIGHT && getCardByIndex(i)->isUsed())
                count++;
        }
        return count;
    }

    void Player::clearAllDevelopmentCard() // Clear all development cards of the player
    {
        developmentCards.clear();
    }

    void Player::deleteDevelopmentCard(int index) // Delete a development card at a specific index
    {
        if(index >= 0 && index < getCardCount())
            developmentCards.erase(developmentCards.begin() + index); // Erase the card at the specific index
        else
            throw std::out_of_range("Invalid card index");
    }

    void Player::addPoints(int amount) // Add points to the player
    {
        this->points += amount;
    }

    






