// ID: 315233486
// Mail: Eilonashwal30@gmail.com

#include "Catan.hpp"
#include <iostream>
#include <stdexcept>
#include <random>
#include <algorithm>

using namespace std;
using namespace ariel;

    Catan::Catan(Player& p1, Player& p2, Player& p3, bool isTest) // Constructor
    {
        // Add the players to the vector
        players.push_back(&p1);
        players.push_back(&p2);
        players.push_back(&p3);
        
        if(isTest)
            board = Board(true); // Tset Board is initialized with known values for testing
        else
            board = Board(); // Random Board

        ChooseStartingPlayer(isTest); // Choose the starting player

        initializeDevePack(isTest); // Initialize the development cards pack
    }
    Catan::~Catan() // Destructor
    {
        for (size_t i = 0; i < players.size(); i++) // Delete all the players from the vector 
        {
            delete players[i];
        }
    }
    void Catan::placeRoad(int playerID, int hexagonIndex, int vertexIndex) // Place a road on the board
    {
        // Check if it's the player's turn
        if (getPlayerTurn() != playerID)
            throw invalid_argument("It's not your turn");

        // Check if the player has enough resources(1 wood and 1 brick)
        if ((players[playerID-1]->getResource(WOOD) < 1 || players[playerID-1]->getResource(BRICK) < 1))
            throw invalid_argument("You don't have enough resources to place a road");
            
        // put the road on the board (if there is a problem, an exception will be thrown)
        board.placeRoad(playerID, hexagonIndex, vertexIndex);
        
        // update the player's resources
        players[playerID-1]->removeResource(WOOD, 1);
        players[playerID-1]->removeResource(BRICK, 1);
        
        // Print that the road was placed successfully
        cout << players[playerID-1]->getName()<<" placed road successfully (" << hexagonIndex << ", " << vertexIndex << ")" << endl;
    }

    void Catan::placeSettlement(int playerID, int hexagonIndex, int vertexIndex) // Place a settlement on the board
    {
        // Check if it's the player's turn
        if (getPlayerTurn() != playerID)
        {
            throw std::invalid_argument("It's not your turn");
        }
        
        // On the beginning of the game, the player can place 2 settlements and then he get 2 points
        bool firstTurn = players[playerID-1]->getPoints()<2;

        if (firstTurn) // beginning of the game
        {
            // put the settlement on the board (if there is a problem, an exception will be thrown)
            board.plaseSettlement(playerID,firstTurn,hexagonIndex, vertexIndex);
            
            addPoints(playerID,1); // Add 1 point to the player (for placing the settlement)

            // Add to the player the road resources
            players[playerID-1]->addResource(WOOD, 1);
            players[playerID-1]->addResource(BRICK, 1);

            // Print that the settlement was placed successfully
            cout << players[playerID-1]->getName()<<" placed settlement successfully (" << hexagonIndex << ", " << vertexIndex << ")" << endl;
            return;
        }

        // Check if the player has enough resources (1 wood, 1 brick, 1 sheep, 1 wheat)
        else if (players[playerID-1]->getResource(WOOD) < 1 || players[playerID-1]->getResource(BRICK) < 1||players[playerID-1]->getResource(SHEEP) < 1||players[playerID-1]->getResource(WHEAT) < 1)
            throw invalid_argument("You don't have enough resources to place a settlement");
        
        // put the settlement on the board (if there is a problem, an exception will be thrown)
        board.plaseSettlement(playerID,firstTurn, hexagonIndex, vertexIndex);
        
        // update the player's resources
        players[playerID-1]->removeResource(WOOD, 1);
        players[playerID-1]->removeResource(BRICK, 1);
        players[playerID-1]->removeResource(SHEEP, 1);
        players[playerID-1]->removeResource(WHEAT, 1);

        players[playerID-1]->addPoints(1); // Add 1 point to the player (for placing the settlement)

        // Print that the settlement was placed successfully
        cout << players[playerID-1]->getName()<<" placed settlement successfully (" << hexagonIndex << ", " << vertexIndex << ")" << endl;
    }

    void Catan::placeCity(int playerID, int hexagonIndex, int vertexIndex)
    {
        // Check if it's the player's turn
        if (getPlayerTurn() != playerID)
            throw invalid_argument("It's not your turn");

        // Check if the player has enough resources
        if (players[playerID-1]->getResource(WHEAT) < 2 || players[playerID-1]->getResource(IRON) < 3)
            throw invalid_argument("You don't have enough resources to place a city");
        
        // put the city on the board (if there is a problem, an exception will be thrown)
        board.placeCity(playerID, hexagonIndex, vertexIndex);

        // update the player's resources
        players[playerID-1]->removeResource(WHEAT, 2);
        players[playerID-1]->removeResource(IRON, 3);

        players[playerID-1]->addPoints(1); // Add 1 point to the player (for placing the city)

        // Print that the city was placed successfully
        cout << players[playerID-1]->getName()<<" placed city successfully (" << hexagonIndex << ", " << vertexIndex << ")" << endl;
    }

    void Catan::rollDice(int playerID) // Roll the dice
    {
        // Check if it's the player's turn
        if (this->getPlayerTurn() != playerID)
            throw invalid_argument("It's not your turn");

        
        srand(time(0)); // Seed the random number generator

        // Generate 2 random numbers between 1 and 6
        int dice1 = rand() % 6 + 1;
        int dice2 = rand() % 6 + 1;
        int sum = dice1 + dice2; // Calculate the sum of the 2 numbers
        
        // if the sum is 7, all players should lose half of their resources
        if (sum == 7)
        {
            cout << "The sum is 7, all players should lose half of their resources" << endl;
            
            //Every player with more than 7 resources will lose half of his resources (just print for now)
            for(size_t i=0;i<this->players.size();i++)
                players[i]->overSevenResources();   

            return;
        }
        // print the result of the dice roll
        cout << players[playerID-1]->getName() << " rolled " << sum << " on the (" << dice1 << " + " << dice2 << ")" << endl;

        // update the resources of the players according to the sum of the dice
        updateResourceByDice(sum);
    }

    void Catan::rollDice(int playerID, int dice) // Roll the dice with a specific number for testing
    {
        // Check if it's the player's turn
        if (this->getPlayerTurn() != playerID)
            throw invalid_argument("It's not your turn");

        // I make the sum to be the dice number for testing and the dice1 and dice2 to be the sum of the dice
        int sum = dice;
        int dice1 = dice-1;
        int dice2=1;

        // if the sum is 7, all players should lose half of their resources
        if (sum == 7)  
        {
            cout << "The sum is 7, all players should lose half of their resources" << endl;
            
            //Every player with more than 7 resources will lose half of his resources
            for(size_t i=0;i<this->players.size();i++)
                players[i]->overSevenResources();   
        
            return;
        }

        // Print the result of the dice roll
        cout << players[playerID-1]->getName() << " rolled " << sum << " on the dice (" << dice1 << " + " << dice2 << ")" << endl;

        // update the resources of the players according to the sum of the dice and there settlements or cities
        updateResourceByDice(sum);

    }

    void Catan::endPlayerTurn(int playerID) // End the player's turn
    {
        // Check if it's the player's turn
        if (this->getPlayerTurn() != playerID)
            throw invalid_argument("It's not your turn");

        this->playerTurn = (this->playerTurn % 3) + 1; // to be shure that the playerTurn is between 1-3

        // Print the result
        cout << "Player " << players[playerID-1]->getName() << " ended his turn." << endl;
        cout << endl;
        cout << "It's now " << players[playerTurn - 1]->getName() << "'s turn: " << endl;

        // Check if the player has 10 points
        checkWinner(playerID);
    }

    bool Catan::checkWinner( int playerID) // Check if the player has 10 points
    {
        // Check if the player has 10 points
        if (players[playerID-1]->getPoints() >= 10) 
        {
            //Print the winner
            cout << players[playerID-1]->getName() << " got 10 points and he is the winner !!!" << endl;
            return true;
        }
        return false;
    }

    void Catan::tradeResorces(int p1, int p2, int res1, int res2, int amount1, int amount2) // p1 try to trade amount1 of res1 with p2 for amount2 of res2
    {
        // Check if it's the p1 turn
        if (this->getPlayerTurn() != p1)
            throw invalid_argument("It's not your turn");
        
        // Check if the p1 and p2 are different
        if (p1 == p2)
            throw invalid_argument("You can't trade with yourself");
        
        // Check if player 1 has the resources
        if (players[p1-1]->getResource(res1) < amount1)
            throw invalid_argument("You don't have enough resources to trade");
            
        // Check if player 2 has the resources
        if (players[p2-1]->getResource(res2) < amount2)
            throw invalid_argument("The other player doesn't have enough resources to trade");
        
        // Remove the resources from the p1
        players[p1-1]->removeResource(res1, amount1); 

        // Add the resources to the p2
        players[p1-1]->addResource(res2, amount2);

        // Remove the resources from the p2
        players[p2-1]->removeResource(res2, amount2);

        // Add the resources to the p1
        players[p2-1]->addResource(res1, amount1);

        //savin res 1 and res2 as a string for the print
        string res1Name,res2Name;
        res1Name = getResorcesName(res1);
        res2Name = getResorcesName(res2);

        // Print the trade
        cout << players[p1-1]->getName() << " traded " << amount1 << " " << res1Name << " with " << players[p2-1]->getName() << " for " << amount2 << " " << res2Name << endl;
    }

    void Catan::printPoints() // Print the points of the players
    {
        for(size_t i=0;i<this->players.size();i++)
            cout << this->players[i]->getName() << " has: " << this->players[i]->getPoints() << " points" << endl;
    }
    
    // Initialize the development cards pack (3-knights, 4-victory points, 1-road building, 1-monopoly, 1-year of plenty)
    void Catan::initializeDevePack(bool isTest) 
     {
        // Clear the DevePack from the previous game
        devePack.clear();
        // Add the cards to the devePack
        devePack.push_back(make_shared<KnightCard>());
        devePack.push_back(make_shared<KnightCard>());
        devePack.push_back(make_shared<KnightCard>());
        devePack.push_back(make_shared<VictoryPointCard>());
        devePack.push_back(make_shared<VictoryPointCard>());
        devePack.push_back(make_shared<VictoryPointCard>());
        devePack.push_back(make_shared<VictoryPointCard>());
        devePack.push_back(make_shared<RoadBuildingCard>());
        devePack.push_back(make_shared<MonopolyCard>());
        devePack.push_back(make_shared<YearOfPlentyCard>());
        
        if(isTest) // If it's a test, don't shuffle the devePack
        {
            return;
        }

        // If it's not a test, shuffle the devePack using the random number generator
        auto rng = default_random_engine(time(nullptr));
        shuffle(devePack.begin(), devePack.end(), rng);
    }

    void Catan::buyDevelopmentCard(int playerID) // Buy a development card (the last card in the devePack)
    {
    // Check if it's the player's turn
    if (this->getPlayerTurn() != playerID)
        throw invalid_argument("It's not your turn");
    
    // Check if the player has enough resources
    if (players[playerID-1]->getResource(WHEAT) < 1 || players[playerID-1]->getResource(SHEEP) < 1 || players[playerID-1]->getResource(IRON) < 1)
        throw invalid_argument("You don't have enough resources to buy a development card");

    // Check if there are development cards available
    if (devePack.empty())
        throw out_of_range("No more development cards available in the devePack");
    
    shared_ptr<DevelopmentCard> card = devePack.back();// Get the last card in the devePack

    devePack.pop_back();// Remove the card from the devePack

    players[playerID-1]->buyDevelopmentCard(card);// Add the card to the player's devePack

    // Update the player's resources
    players[playerID-1]->removeResource(WHEAT, 1);
    players[playerID-1]->removeResource(SHEEP, 1);
    players[playerID-1]->removeResource(IRON, 1);
    }

    void Catan::useDevelopmentCard(int playerID, int cardIndex, bool isTest) // Use a development card
    {
        // Check if it's the player's turn
        if (this->getPlayerTurn() != playerID)
            throw invalid_argument("It's not your turn");

        // Check if the player has the card he wants to use
        if (cardIndex < 0 || cardIndex >= players[playerID-1]->getCardCount())
            throw invalid_argument("Invalid card index");
        
        // Check if the card has already been used
        bool isUsed = players[playerID-1]->getCardByIndex(cardIndex)->isUsed();
        if (isUsed)
            throw invalid_argument("The card has already been used");

        // Use the card
        int type = players[playerID-1]->useDevelopmentCard(cardIndex);

        if (type == KNIGHT) 
        {
            // print the player use a knight card
            cout << players[playerID-1]->getName() << " used a knight card and has " << players[playerID-1]->numOfKnights() << " knights now" << endl;
           
            // Check if the player has more than 2 knights and give him 2 points
            if(players[playerID-1]->numOfKnights()>2)
            {
                players[playerID-1]->addPoints(2);
                cout << players[playerID-1]->getName() << " Has the biggest army and got 2 points, now he has " << players[playerID-1]->getPoints() << " points" << endl;
            }
        }
        else if (type == VICTORY_POINT) 
        {
            // Give the player 1 point
            players[playerID-1]->addPoints(1);
            // Print the result
            cout << players[playerID-1]->getName() << " used a victory point card and got 1 point, now he has " << players[playerID-1]->getPoints() << " points" << endl;
        }
        else if (type == ROAD_BUILDING) 
        {
            // Give the player resources for placing 2 roads
            players[playerID-1]->addResource(WOOD, 2);
            players[playerID-1]->addResource(BRICK, 2);

            // Ask the player to choose 2 vertex to place the roads
            int hexagonIndex1, vertexIndex1, hexagonIndex2, vertexIndex2;
            
            if(isTest) // If it's a test, place the roads in known places (2,1) and (0,0)
            {
                hexagonIndex1=2;
                vertexIndex1=1;
                hexagonIndex2=0;
                vertexIndex2=0;
            }
            else // If it's not a test, ask the player to choose the places
            {
                cout << "Choose the first vertex to place the road: " << endl;
                cin >> hexagonIndex1 >> vertexIndex1;
                cout << "Choose the second vertex to place the road: " << endl;
                cin >> hexagonIndex2 >> vertexIndex2;
            }

            // Build the roads on the board (if there is a problem, an exception will be thrown)
            this->placeRoad(playerID, hexagonIndex1, vertexIndex1);
            this->placeRoad(playerID, hexagonIndex2, vertexIndex2);

            // Print the result
            cout << players[playerID-1]->getName() << " used a road building card and placed 2 roads successfully" << endl;
        }
        else if (type == MONOPOLY) // Get resources from all the other players of a specific type
        {
            int resourceType;

            if(isTest)// for testing assume the player will choose WOOD
                resourceType=WOOD;
            else
            {
                // Ask the player to choose a resource type
                cout << "Choose a resource type to monopolize: 0: WOOD, 1: BRICK, 2: SHEEP, 3: WHEAT, 4: IRON" << endl;
                cin >> resourceType;

                //check if the resource type is valid
                if (resourceType < 0 || resourceType > 4)
                    throw invalid_argument("Invalid resource type");
            }

            // Get the total amount of the resource
            cout<< players[playerID-1]->getName() << " used a Monopoly card: "<<endl;
            int total = 0;
            for (size_t i = 0; i < this->players.size(); i++) 
            {
                //Skip the current player
                if (i == static_cast<size_t>(playerID-1))
                    continue;

                // Get the current amount of the resource from the player
                int current = players[i]->getResource(resourceType); 

                this->players[i]->removeResource(resourceType, current); // Remove the resource from the player

                total += current; // Add the amount to the total

                // Print the result
                cout<<"Took "<<current<<" resources of "<<getResorcesName(resourceType)<<" from "<<players[i]->getName()<<endl;
            }
            // Add the total amount of the resource to the player
            players[playerID-1]->addResource(resourceType, total);

            // Print the result
            cout << "For total, he got an " << total << " " << getResorcesName(resourceType) << " from all the other players" << endl;
        }
        else if (type == YEAR_OF_PLENTY) // Get 2 resources from the bank
        {
            int resourceType1, resourceType2;
            if(isTest) // for testing assume the player will choose WOOD and BRICK
            {
                resourceType1=WOOD;
                 resourceType2=BRICK;
            }
            else
            {
            // Ask the player to choose 2 resource types
            cout << "Choose 2 resource types to get: 0: WOOD, 1: BRICK, 2: SHEEP, 3: WHEAT, 4: IRON" << endl;
            cin >> resourceType1 >> resourceType2;
            }
            //check if the resource type is valid
            if (resourceType1 < 0 || resourceType1 > 4 || resourceType2 < 0 || resourceType2 > 4)
                throw invalid_argument("Invalid resource type");

            players[playerID-1]->addResource(resourceType1, 1);
            players[playerID-1]->addResource(resourceType2, 1);

            // Print the result
            cout << players[playerID-1]->getName() << " used a Year of Plenty card and got 1 " << getResorcesName(resourceType1) << " and 1 " << getResorcesName(resourceType2) << " from the bank" << endl;
        }
    }

    void Catan::printDevelopmentCards(int playerID) // Print the development cards of the player
    {
        // Print for all the players there development cards and if they are used
        for(int i=0;i<players[playerID]->getCardCount();i++)
            cout << "Card " << i << ": " << players[playerID]->getCardByIndex(i)->getType() << " Used: " << players[playerID]->getCardByIndex(i)->isUsed() << endl;

        // if the player doesn't have development cards
        if(players[playerID]->getCardCount()==0)
            cout << "You dont have a development cards" << endl;
    }

    void Catan::ChooseStartingPlayer(bool isTest) // Choose the starting player
    {
        if(isTest) // If it's a test, the starting player is player 1
        {
            this->playerTurn = 1;
            return;
        }

        // Seed the random number generator
        srand(time(0));
        int startingPlayer = rand() % 3 + 1; // 1-player1, 2-player2, 3-player3

        // Print the starting player
        if(startingPlayer == 1)
            cout << "The starting player is " << players[0]->getName() << ". (chosen randomly)" << endl;
        else if(startingPlayer == 2)
            cout << "The starting player is " << players[1]->getName() << ". (chosen randomly)" << endl;
        else
            cout << "The starting player is " << this->players[2]->getName() << ". (chosen randomly)" << endl;

        this->playerTurn = startingPlayer; // Set the starting player
    }

    void Catan::printBoard(bool isTest) // Print the board by calling the printBoard function of the board
    {
        board.printBoard(isTest);
    }

    Player& Catan::getCurrentPlayer() // Get the current player
    {
        // check if the playerTurn is between 1-3 and return the player
        if (this->playerTurn >= 1 && static_cast<size_t>(playerTurn) <= players.size()) {
            return *players[playerTurn - 1];
        } 
        else 
        {
            throw out_of_range("Invalid turn value");
        }
    }

    int Catan::getPlayerTurn()const // Get the player turn
    {
        return this->playerTurn;
    }

    Player& Catan:: getPlayerByName(string name) // Get the player by his name
    {
        // Move over the players and return the player with the same name
        for(size_t i=0;i<players.size();i++)
        {
            if(name == players[i]->getName())
                return *players[i];
        }
        // If there is no player with that name, throw an exception
        throw invalid_argument("There is noplayer with that name");
    }

    void Catan::chooseResorces(int playerID) // Choose the first resources of the player in the beginning of the game
    {
        string print="";
        int count=1;
        vector<vector<int>> option;

        for (int i = 0; i < BOARD_SIZE; ++i) 
        {
            // Check if the hexagon is a desert and if the player can get the resource from the hexagon
            if(getBoard().getHexagon(i).isSett(playerID) && getBoard().getHexagon(i).getResource()!= DESERT )
            {
                // print the resource name and add it to the option vector
                print+=to_string(count);
                print+=". "+getBoard().getHexagon(i).getResourceName()+"\n";
                option.push_back({i,getBoard().getHexagon(i).getResource()});
                count++;
            }
        }
        // Ask the player to choose 2 resources
        cout << "Player " << players[playerID-1]->getName() << ", please choose 2 resources to collect: (n1 n2)" << endl
             << print;
        int res, res2;
        cin >> res >> res2;
        
        //Assuming the player will enter valid numbers
        players[playerID-1]->addResource(option[res-1][1],1);//Add the resource
        players[playerID-1]->addResource(option[res2-1][1],1);//Add the resource

    }

    Board &Catan::getBoard() // Get the board
    {
        return board;
    }

    void Catan::addResource(int playerID, int resourceType, int amount) // Add resources to the player
    {
        players[playerID-1]->addResource(resourceType, amount);
    }

    void Catan::updateResourceByDice(int diceRoll) // Update the resources of the players by the dice roll
    {
        // Move over the board and check if the hexagon has the number of the dice roll
        for(size_t i=0;i<BOARD_SIZE;i++)
        {
            Hexagon hexagon = board.getHexagon(i);

            if(hexagon.getIdOfHexagon()==diceRoll) // If the hexagon has the number of the dice roll
            {
                // Move over the 6 vertexs of the hexagon and check if the vertex is on use
                for(size_t j=0;j<6;j++)
                {
                    if(hexagon.getSettlementVertex(j).isOnUseByStructure()) // If the vertex is on use
                    {
                        int ownerID = hexagon.getSettlementVertex(j).getIDPlayerOwner(); // Get the owner of the vertex
                        Player* owner = players[ownerID - 1]; 
                        int resource = hexagon.getResource(); // Get the resource of the hexagon
                        int structure = hexagon.getSettlementVertex(j).getSturcture(); // Get the structure of the vertex
                        
                        if (structure == CITY) // If the structure is a city, add 2 resources to the player
                        {
                            cout<< "Player " << owner->getName() << " got 2 " << hexagon.getResourceName() << " from his city on hexagon " << i << endl;
                            owner->addResource(resource, 2);
                        }
                        else // If the structure is a settlement, add 1 resource to the player
                        {
                            cout<< "Player " << owner->getName() << " got 1 " << hexagon.getResourceName() << " from his settlement on hexagon " << i << endl;
                            owner->addResource(resource, 1);
                        }

                    }
                }
            }
        }
    }

    Player& Catan::getPlayer(int num)
    {
        return *players[num-1]; // Return the player by his number (1-3)
    }

    void Catan::addPoints(int playerID,int amount) // Add points to the player
    {
        players[playerID-1]->addPoints(amount);
    }

    string Catan::getResorcesName(int resorceType) // Get the name of the resource by the type
    {
        switch (resorceType)
        {
        case WOOD:
            return "WOOD";
        case BRICK:
            return "BRICK";
        case SHEEP:
            return "SHEEP";
        case WHEAT:
            return "WHEAT";
        case IRON:
            return "IRON";
        default:
            return "Invalid resource type";
        }
    }

    void Catan::tradeDevelopmentCard(int p1, int p2, int cardIndex1, int cardIndex2) // p1 try to trade cardIndex1 with p2 for cardIndex2
    {
        // Check if it's the player's turn
        if (this->getPlayerTurn() != p1)
            throw invalid_argument("It's not your turn");
        
        // Check if the players are different
        if (p1 == p2)
            throw invalid_argument("You can't trade with yourself");
        
        // Check if player 1 has the card
        if (cardIndex1 < 0 || cardIndex1 >= players[p1-1]->getCardCount())
            throw invalid_argument("Invalid card index");

        // Check if player 2 has the card
        if (cardIndex2 < 0 || cardIndex2 >= players[p2-1]->getCardCount())
            throw invalid_argument("Invalid card index");

        //Check if one of the card is used
        if (players[p1-1]->getCardByIndex(cardIndex1)->isUsed() || players[p2-1]->getCardByIndex(cardIndex2)->isUsed())
            throw invalid_argument("One of the cards is already used");
        
        // Get the cards from the players
        shared_ptr<DevelopmentCard> card1 = players[p1-1]->getCardByIndex(cardIndex1);
        shared_ptr<DevelopmentCard> card2 = players[p2-1]->getCardByIndex(cardIndex2);

        // remove the cards from the players
        players[p1-1]->deleteDevelopmentCard(cardIndex1);
        players[p2-1]->deleteDevelopmentCard(cardIndex2);
        
        // Add the cards to the players
        players[p1-1]->buyDevelopmentCard(card2);
        players[p2-1]->buyDevelopmentCard(card1);

        //savin card 1 and card 2 as a string for the print
        string card1Name,card2Name;
        card1Name = card1->getTypeName();
        card2Name = card2->getTypeName();

        // Print the result
        cout << players[p1-1]->getName() << " trade card - " << card1Name << " with " << players[p2-1]->getName() << " for card - " << card2Name << endl;
    }
