// ID: 315233486
// Mail: Eilonashwal30@gmail.com

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN // This tells the compiler to create a main function

#include "doctest.h"
#include "Catan.hpp"

using namespace ariel;
using namespace std;

// Static variables for the game and players to keep them between the tests
static bool isCreated = false; // To create the game only once
static Catan* catan = nullptr; // The game
static Player* p1 = nullptr; // The players
static Player* p2 = nullptr;
static Player* p3 = nullptr;

void createGame()  // Create the game and the players
{
    if (!isCreated) // Create the game only once
    {
        // Create the players
        p1 = new Player("Lior(1)");
        p2 = new Player("Roi(2)");
        p3 = new Player("David(3)");

        // Create the game with the players on the test mode (true -not random)
        catan = new Catan(*p1, *p2, *p3, true); 

        //Start the game - print the welcome message
        cout<<endl;
        cout<<endl;
        cout<< "Welcome to Catan game !"<<endl;

        // Print the board - choosen by me
        catan->printBoard(true);

        // This is a variable to keep the current player turn
        int cp = catan->getPlayerTurn();
        
        // Player 1's turn:
        cout << "It's now " << catan->getPlayer(cp).getName() << "'s turn: " << endl;
        // places a settlement on (0,0)
        int hexagon = 0; int vertex = 0; 
        catan->placeSettlement(cp, hexagon, vertex);
        // Add one Iron to the player
        catan->addResource(catan->getPlayerTurn(), IRON, 1);
        // Try to place a road in a vertex that is not connected to the settlement (0,4)
        hexagon = 0; vertex = 4;
        CHECK_THROWS(catan->placeRoad(cp, hexagon, vertex));
        // places a road on (0,5)
        hexagon = 0; vertex = 5;
        catan->placeRoad(cp, hexagon, vertex);

        // places a settlement on (1,1) 
        hexagon = 1; vertex = 1; 
        catan->placeSettlement(cp, hexagon, vertex);
        // Add one sheep to the player
        catan->addResource(cp, catan->getBoard().getHexagon(hexagon).getResource(), 1);
        // places a road on (1,0)
        hexagon = 1; vertex = 0;
        catan->placeRoad(cp, hexagon, vertex);

        // Player 1's end turn
        catan->endPlayerTurn(cp);

        // Player 2's turn:
        cp = catan->getPlayerTurn();

        // places a settlement on (1,4)
        hexagon = 1; vertex = 4;
        catan->placeSettlement(cp, hexagon, vertex);
        // Add one Sheep to the player
        catan->addResource(cp, catan->getBoard().getHexagon(hexagon).getResource(), 1);
        // places a road on (1,5)
        hexagon = 5; vertex = 0;
        catan->placeRoad(cp, hexagon, vertex);

        // places a settlement on (8,2)
        hexagon = 8; vertex = 2;
        catan->placeSettlement(cp, hexagon, vertex);
        // Add one Wood to the player
        catan->addResource(cp, catan->getBoard().getHexagon(hexagon).getResource(), 1);
        // places a road on (9,0)
        hexagon = 9; vertex = 0; 
        catan->placeRoad(cp, hexagon, vertex);

        // Player 2's end turn
        catan->endPlayerTurn(cp);

        // Player 3's turn:
        cp = catan->getPlayerTurn();

        // places a settlement on (18,4)
        hexagon = 18; vertex = 4;
        catan->placeSettlement(cp, hexagon, vertex);
        // Add one Sheep to the player
        catan->addResource(cp, catan->getBoard().getHexagon(hexagon).getResource(), 1); 
        // places a road on (18,4)
        hexagon = 18; vertex = 4;
        catan->placeRoad(cp, hexagon, vertex);

        // places a settlement on (17,4)
        hexagon = 17; vertex = 4;
        catan->placeSettlement(cp, hexagon, vertex);
        // Add one Wood to the player
        catan->addResource(cp, catan->getBoard().getHexagon(hexagon).getResource(), 1); 
        // places a road on (17,4)
        hexagon = 17; vertex = 4;
        catan->placeRoad(cp, hexagon, vertex);

        // Player 3's end turn
        catan->endPlayerTurn(cp);

        //Turn isCreated to true to not create the game again
        isCreated = true;
    }
}

TEST_CASE("Test Catan") 
{
    createGame(); // Create the game and the players

    SUBCASE("Check the resources collection of the players on the beginning of the game") 
    {
        // First player should have 1 Iron and 1 Sheep
        CHECK_EQ(p1->getResource(IRON), 1);
        CHECK_EQ(p1->getResource(SHEEP), 1);
        CHECK_EQ(p1->getResource(WOOD), 0);
        CHECK_EQ(p1->getResource(WHEAT), 0);
        CHECK_EQ(p1->getResource(BRICK), 0);

        // Second player should have 1 Sheep and 1 Wood
        CHECK_EQ(p2->getResource(SHEEP), 1);
        CHECK_EQ(p2->getResource(WOOD), 1);
        CHECK_EQ(p2->getResource(WHEAT), 0);
        CHECK_EQ(p2->getResource(BRICK), 0);
        CHECK_EQ(p2->getResource(IRON), 0);

        // Third player should have 1 Sheep and 1 Wheat
        CHECK_EQ(p3->getResource(SHEEP), 1);
        CHECK_EQ(p3->getResource(WHEAT), 1);
        CHECK_EQ(p3->getResource(WOOD), 0);
        CHECK_EQ(p3->getResource(BRICK), 0);
        CHECK_EQ(p3->getResource(IRON), 0);
    }

    SUBCASE("Check every player has 2 points on the beginning of the game") 
    {
        CHECK_EQ(catan->getPlayer(1).getPoints(), 2);
        CHECK_EQ(catan->getPlayer(2).getPoints(), 2);
        CHECK_EQ(catan->getPlayer(3).getPoints(), 2);
    }
    
    SUBCASE("Adding 20 resources of each type to each player to check the addResource function")
    {
        // Add 20 resources from each type to each player
        for(int i=1;i< 4;i++)
        {
            catan->addResource(i, WOOD, 20);
            catan->addResource(i, BRICK, 20);
            catan->addResource(i, SHEEP, 20);
            catan->addResource(i, WHEAT, 20);
            catan->addResource(i, IRON, 20);
        }
        // check if the resources were added correctly

        // First player
        CHECK_EQ(p1->getResource(IRON), 21);
        CHECK_EQ(p1->getResource(SHEEP), 21);
        CHECK_EQ(p1->getResource(WOOD), 20);
        CHECK_EQ(p1->getResource(WHEAT), 20);
        CHECK_EQ(p1->getResource(BRICK), 20);
        // Second player
        CHECK_EQ(p2->getResource(SHEEP), 21);
        CHECK_EQ(p2->getResource(WOOD), 21);
        CHECK_EQ(p2->getResource(WHEAT), 20);
        CHECK_EQ(p2->getResource(BRICK), 20);
        CHECK_EQ(p2->getResource(IRON), 20);
        // Third player
        CHECK_EQ(p3->getResource(SHEEP), 21);
        CHECK_EQ(p3->getResource(WHEAT), 21);
        CHECK_EQ(p3->getResource(WOOD), 20);
        CHECK_EQ(p3->getResource(BRICK), 20);
        CHECK_EQ(p3->getResource(IRON), 20);
    }

    SUBCASE("Trade resources between players")
    {
        // All the resources of the players before the trade
        int p1Wood = p1->getResource(WOOD);
        int p1Brick = p1->getResource(BRICK);
        int p2Wood = p2->getResource(WOOD);
        int p2Brick = p2->getResource(BRICK);

        // p1 trades with p2 1 wood for 1 brick
        catan->tradeResorces(1,2 , WOOD, BRICK, 1, 1);

        // Check if the trade was done correctly
        CHECK_EQ(p1->getResource(WOOD), p1Wood-1);
        CHECK_EQ(p1->getResource(BRICK), p1Brick+1);
        CHECK_EQ(p2->getResource(WOOD), p2Wood+1);
        CHECK_EQ(p2->getResource(BRICK), p2Brick-1);

        //Try to trade more than p1 has (p1 has 19 woods)
        CHECK_THROWS(catan->tradeResorces(1,2 , WOOD, BRICK, 20, 1));
        
        // Try to trade with a resource that the p2 doesn't have (p2 has 19 bricks)
        CHECK_THROWS(catan->tradeResorces(1,2 , WOOD, BRICK, 1, 23));

        // Try to trade with himself
        CHECK_THROWS(catan->tradeResorces(1,1 , WOOD, BRICK, 1, 1));
    }

    SUBCASE("Build a different roads on the board for each player")
    {
        // Player 1's turn:
        // All the resources of the players before placing the roads
        int p1Brick = p1->getResource(BRICK);
        int p1Wood = p1->getResource(WOOD);

        // places different roads on the board
        catan->placeRoad(1, 1, 1);
        catan->placeRoad(1, 0, 1);
        catan->placeRoad(1, 1, 2);
        catan->placeRoad(1, 2, 0);
        catan->placeRoad(1, 3, 0);
        catan->placeRoad(1, 3, 5);

        // Check if road on (3,0) was placed correctly by player 1
        CHECK_EQ(catan->getBoard().getHexagon(3).getRoadVertex(0).isOnUseByPlayer(1), 1);
        
        // Check if the resources were updated correctly(each road costs 1 wood and 1 brick)
        CHECK_EQ(p1->getResource(BRICK), p1Brick-6);
        CHECK_EQ(p1->getResource(WOOD), p1Wood-6);
        
        // Try to place a roads on problematic vertices
        CHECK_THROWS(catan->placeRoad(1, 0, 1));// has already a road in this vertex
        CHECK_THROWS(catan->placeRoad(1, 0, 3));// not connected to the settlement
        CHECK_THROWS(catan->placeRoad(1, 5, 0));// Belong to the other player
        CHECK_THROWS(catan->placeRoad(2, 5, 0));// Not the turn of the player

        // Remove 14 wood from p1 and check if the player can place a road with 0 wood
        catan->getPlayer(1).removeResource(WOOD, 14);
        CHECK_THROWS(catan->placeRoad(1, 1, 1));

        //Return the resources to the player
        catan->getPlayer(1).addResource(WOOD, 14);

        //End the turn of player 1
        catan->endPlayerTurn(1);

        // Player 2's turn:
        // places different roads on the board
        catan->placeRoad(2, 5, 1);
        catan->placeRoad(2, 8, 1);
        catan->placeRoad(2, 8, 0);
        catan->placeRoad(2, 7, 1);
        
        // End the turn of player 2
        catan->endPlayerTurn(2);

        // Player 3's turn:
        // places different roads on the board
        catan->placeRoad(3, 17, 3);
        catan->placeRoad(3, 17, 2);

        // End the turn of player 3
        catan->endPlayerTurn(3);
    }
    
    SUBCASE("Build a different settlements on the board for each player")
    {
        // Player 1's turn:
        // All the resources of the players before placing the settlements
        int brick = p1->getResource(BRICK);
        int wood = p1->getResource(WOOD);
        int sheep = p1->getResource(SHEEP);
        int wheat = p1->getResource(WHEAT);
        
        // places a settlement on (2,1)
        catan->placeSettlement(1, 2, 1);

        //Try to build a settlement in a vertex that is not connected to the road
        CHECK_THROWS(catan->placeSettlement(1, 2, 3));

        //Try to build a settlement close to another settlement
        CHECK_THROWS(catan->placeSettlement(1, 1, 2));

        // Check if the resources were updated correctly(each settlement costs 1 wood, 1 brick, 1 sheep, 1 wheat)
        CHECK_EQ(p1->getResource(BRICK), brick-1);
        CHECK_EQ(p1->getResource(WOOD), wood-1);
        CHECK_EQ(p1->getResource(SHEEP), sheep-1);
        CHECK_EQ(p1->getResource(WHEAT), wheat-1);

        // End the turn of player 1
        catan->endPlayerTurn(1);

        // Player 2's turn:
        // All the resources of the players before placing the settlements
        brick = p2->getResource(BRICK);
        wood = p2->getResource(WOOD);
        sheep = p2->getResource(SHEEP);
        wheat = p2->getResource(WHEAT);

        // places 2 settlements on the board
        catan->placeSettlement(2, 6, 0);
        catan->placeSettlement(2, 3, 5);

        // Check different problematic cases of placing a settlement
        CHECK_THROWS(catan->placeSettlement(2, 9, 1));// close to another settlement
        CHECK_THROWS(catan->placeSettlement(2, 6, 2));// not connected to the road
        CHECK_THROWS(catan->placeSettlement(3, 5, 0));// not the turn of the player

        // Check if the resources were updated correctly(each settlement costs 1 wood, 1 brick, 1 sheep, 1 wheat)
        CHECK_EQ(p2->getResource(BRICK), brick-2);
        CHECK_EQ(p2->getResource(WOOD), wood-2);
        CHECK_EQ(p2->getResource(SHEEP), sheep-2);
        CHECK_EQ(p2->getResource(WHEAT), wheat-2);

        // End the turn of player 2
        catan->endPlayerTurn(2);

        // Player 3's turn:
        // All the resources of the players before placing the settlements
        brick = p3->getResource(BRICK);
        wood = p3->getResource(WOOD);
        sheep = p3->getResource(SHEEP);
        wheat = p3->getResource(WHEAT);
        
        // places a settlement on (14,4)
        catan->placeSettlement(3, 14, 4);

        // Check if the resources were updated correctly(each settlement costs 1 wood, 1 brick, 1 sheep, 1 wheat)
        CHECK_EQ(p3->getResource(BRICK), brick-1);
        CHECK_EQ(p3->getResource(WOOD), wood-1);
        CHECK_EQ(p3->getResource(SHEEP), sheep-1);
        CHECK_EQ(p3->getResource(WHEAT), wheat-1);
        
        // End the turn of player 3
        catan->endPlayerTurn(3);
    }

    SUBCASE("Build a different cities on the board for each player")
    {   
        //Player 1's turn
        //All the resources of the players before placing the cities
        int brick = p1->getResource(BRICK);
        int wood = p1->getResource(WOOD);
        int sheep = p1->getResource(SHEEP);
        int wheat = p1->getResource(WHEAT);
        int iron = p1->getResource(IRON);

        // places a city on (2,1)
        catan->placeCity(1, 2, 1);

        //Try to build a city in a vertex that is not connected to the settlement
        CHECK_THROWS(catan->placeCity(1, 2, 3));

        //Try to build a city close to another city
        CHECK_THROWS(catan->placeCity(1, 1, 2));

        //Try to build a city in a vertex that has a settlement but not the player's
        CHECK_THROWS(catan->placeCity(1, 1, 4));

        //Check if the resources were updated correctly(each city costs 2 wheat and 3 iron)
        CHECK_EQ(p1->getResource(WHEAT), wheat-2);
        CHECK_EQ(p1->getResource(IRON), iron-3);
        CHECK_EQ(p1->getResource(BRICK), brick);
        CHECK_EQ(p1->getResource(WOOD), wood);
        CHECK_EQ(p1->getResource(SHEEP), sheep);

        //End the turn of player 1
        catan->endPlayerTurn(1);

        //Player 2's turn
        //All the resources of the players before placing the cities
        brick = p2->getResource(BRICK);
        wood = p2->getResource(WOOD);
        sheep = p2->getResource(SHEEP);
        wheat = p2->getResource(WHEAT);
        iron = p2->getResource(IRON);
        
        // places a city on (6,0)
        catan->placeCity(2, 6, 0);
        // places a city on (3,5)
        catan->placeCity(2, 3, 5);

        //Check different problematic cases of placing a city:
        CHECK_THROWS(catan->placeCity(2, 9, 1));// close to another city
        CHECK_THROWS(catan->placeCity(2, 6, 2));// not connected to the settlement
        CHECK_THROWS(catan->placeCity(3, 5, 0));// not the turn of the player

        //Check if the resources were updated correctly(each city costs 2 wheat and 3 iron)
        CHECK_EQ(p2->getResource(WHEAT), wheat-4);
        CHECK_EQ(p2->getResource(IRON), iron-6);
        CHECK_EQ(p2->getResource(BRICK), brick);
        CHECK_EQ(p2->getResource(WOOD), wood);
        CHECK_EQ(p2->getResource(SHEEP), sheep);
        
        //End the turn of player 2
        catan->endPlayerTurn(2);

        //Player 3's turn:
        //All the resources of the players before placing the cities
        brick = p3->getResource(BRICK);
        wood = p3->getResource(WOOD);
        sheep = p3->getResource(SHEEP);
        wheat = p3->getResource(WHEAT);
        iron = p3->getResource(IRON);

        // places a city on (14,4)
        catan->placeCity(3, 14, 4); 

        //Check if the resources were updated correctly(each city costs 2 wheat and 3 iron)
        CHECK_EQ(p3->getResource(WHEAT), wheat-2);
        CHECK_EQ(p3->getResource(IRON), iron-3);
        CHECK_EQ(p3->getResource(BRICK), brick);
        CHECK_EQ(p3->getResource(WOOD), wood);
        CHECK_EQ(p3->getResource(SHEEP), sheep);

        //End the turn of player 3
        catan->endPlayerTurn(3);
    }

    SUBCASE("Rool the dice and collect resources for each player from the hexagons")
    {
        // All the Sheep resources of player 1 and 2 before rolling the dice
        int p1Sheep = p1->getResource(SHEEP);
        int p2Sheep = p2->getResource(SHEEP);

        //Player 1's turn:
        // roll the dice on 2 to receive sheeps (for each player that has a settlement or city on the hexagon)
        catan->rollDice(1, 2);
        CHECK_EQ(p1->getResource(SHEEP), p1Sheep+1);
        CHECK_EQ(p2->getResource(SHEEP), p2Sheep+1);
        
        //End turn of player 1
        catan->endPlayerTurn(1);
        
        //All the Iron and Wheat resources of player 1 and 3 before rolling the dice
        int brick = p2->getResource(BRICK);
        int wheat = p3->getResource(WHEAT);

        //Player 2's turn:
        // roll the dice on 6 to receive bricks or wheat (for each player that has a settlement or city on the hexagon)
        catan->rollDice(2, 6);
        CHECK_EQ(p2->getResource(BRICK), brick+2);
        CHECK_EQ(p3->getResource(WHEAT), wheat+3);

        //End turn of player 2
        catan->endPlayerTurn(2);

        // All the resources of player 2 before rolling the dice
        int iron = p2->getResource(IRON);
        int wood = p2->getResource(WOOD);
        brick = p2->getResource(BRICK);
        wheat = p2->getResource(WHEAT);
        int sheep = p2->getResource(SHEEP);

        //Player 3's turn:
        // roll the dice on 12 to receive wheat (for each player that has a settlement or city on the hexagon)
        catan->rollDice(3, 12);
        CHECK_EQ(p2->getResource(IRON), iron);
        CHECK_EQ(p2->getResource(SHEEP), sheep);
        CHECK_EQ(p2->getResource(WOOD), wood);
        CHECK_EQ(p2->getResource(WHEAT), wheat+2);//City
        CHECK_EQ(p2->getResource(BRICK), brick);

        //End turn of player 3
        catan->endPlayerTurn(3);
    }

    SUBCASE("Playing not in the turn of the player")
    {
        //Now is p1 turn and p2/p3 try to play - should throw exception
        CHECK_THROWS(catan->placeSettlement(2, 1, 1));
        CHECK_THROWS(catan->placeRoad(3, 1, 1));
        CHECK_THROWS(catan->placeCity(2, 1, 1));
        CHECK_THROWS(catan->rollDice(2, 2));
        CHECK_THROWS(catan->buyDevelopmentCard(2));
    }

    SUBCASE("Buying development cards and check the resources of the players")
    {
        //Initialize the development cards pack - like the test mode
        catan->initializeDevePack(true);

        //Player 1's turn: (Do nothing)
        //End turn of player 1
        catan->endPlayerTurn(1);

        //Player 2's turn:
        //All the resources of the player 2 before buying the development cards
        int brick = p2->getResource(BRICK);
        int wood = p2->getResource(WOOD);
        int sheep = p2->getResource(SHEEP);
        int wheat = p2->getResource(WHEAT);
        int iron = p2->getResource(IRON);

        //Buy 2 development cards
        //print the first card on the deck
        catan->buyDevelopmentCard(2);
        catan->buyDevelopmentCard(2);

        //Check if the resources were updated correctly(each development card costs 1 sheep, 1 wheat, 1 iron)
        CHECK_EQ(p2->getResource(BRICK), brick);
        CHECK_EQ(p2->getResource(WOOD), wood);
        CHECK_EQ(p2->getResource(SHEEP), sheep-2);
        CHECK_EQ(p2->getResource(WHEAT), wheat-2);
        CHECK_EQ(p2->getResource(IRON), iron-2);

        //End turn of player 2
        catan->endPlayerTurn(2);

        //Player 3's turn:
        //All the resources of the player 3 before buying the development cards
        brick = p3->getResource(BRICK);
        wood = p3->getResource(WOOD);
        sheep = p3->getResource(SHEEP);
        wheat = p3->getResource(WHEAT);
        iron = p3->getResource(IRON);

        //Buy 1 development card
        catan->buyDevelopmentCard(3);

        //Check if the resources were updated correctly(each development card costs 1 sheep, 1 wheat, 1 iron)
        CHECK_EQ(p3->getResource(BRICK), brick);
        CHECK_EQ(p3->getResource(WOOD), wood);
        CHECK_EQ(p3->getResource(SHEEP), sheep-1);
        CHECK_EQ(p3->getResource(WHEAT), wheat-1);
        CHECK_EQ(p3->getResource(IRON), iron-1);

        //Remove all the iron from the player 3 and try to buy a development card (after that - return him 20 iron)
        p3->removeResource(IRON, p3->getResource(IRON));
        CHECK_THROWS(catan->buyDevelopmentCard(3));
        p3->addResource(IRON, 20);

        //Remove all the wheat from the player 3 and try to buy a development card (after that - return him 20 wheat)
        p3->removeResource(WHEAT, p3->getResource(WHEAT));
        CHECK_THROWS(catan->buyDevelopmentCard(3));
        p3->addResource(WHEAT, 20);

        //Remove all the sheep from the player 3 and try to buy a development card (after that - return him 20 sheep)
        p3->removeResource(SHEEP, p3->getResource(SHEEP));
        CHECK_THROWS(catan->buyDevelopmentCard(3));
        p3->addResource(SHEEP, 20);

        //End turn of player 3
        catan->endPlayerTurn(3);
    }

    SUBCASE("Buy all the development card by p1 and use them")
    {
        // Add 10 resources from iron, wheat, sheep to player 1 (to buy development cards)
        p1->addResource(IRON, 10);
        p1->addResource(WHEAT, 10);
        p1->addResource(SHEEP, 10);

        //Initialize the development cards pack - like the test mode
        catan->initializeDevePack(true);

        // Clear all the development cards from the players
        p1->clearAllDevelopmentCard();
        p2->clearAllDevelopmentCard();
        p3->clearAllDevelopmentCard();

        //Buy 9 development cards for player 1 (one card left in the deck)
        for(int i=0;i<9;i++)
        {
            catan->buyDevelopmentCard(1);
        }

        // Check if there is an option to buy another card
        CHECK_NOTHROW(catan->buyDevelopmentCard(1));
        
        /* 
            The cards on the deck:
            0.Year of Plenty 1.Monopoly 2.Road Building 3.Victory Point 4.Victory Point 5.Victory Point
            6.Knight 7.Knight 8.Knight
         */

        //Check using Year of Plenty card - get 1 wood and 1 brick
        SUBCASE("Year of Plenty")
        {
            //Player 1's turn:
            // All the Wood and Brick resources of player 1 before using the card
            int wood = p1->getResource(WOOD);
            int brick = p1->getResource(BRICK);

            // Use the Year of Plenty card - get 1 wood and 1 brick
            catan->useDevelopmentCard(1, 0, true);
            CHECK_EQ(p1->getResource(WOOD), wood+1);
            CHECK_EQ(p1->getResource(BRICK), brick+1);
            
            //Try to use the card again after using it
            CHECK_THROWS(catan->useDevelopmentCard(1, 0, true));
        }    

        //Check using Monopoly card - get all the woods for player 1
        SUBCASE("Monopoly")
        {
            //Delete all the resources from Player 1 and add him 1 wood
            p1->removeResource(WOOD, p1->getResource(WOOD));
            p1->removeResource(BRICK, p1->getResource(BRICK));
            p1->removeResource(SHEEP, p1->getResource(SHEEP));
            p1->removeResource(WHEAT, p1->getResource(WHEAT));
            p1->removeResource(IRON, p1->getResource(IRON));
            p1->addResource(WOOD, 1);

            //Delete all the resources from Player 2 and add him 2 wood
            p2->removeResource(WOOD, p2->getResource(WOOD));
            p2->removeResource(BRICK, p2->getResource(BRICK));
            p2->removeResource(SHEEP, p2->getResource(SHEEP));
            p2->removeResource(WHEAT, p2->getResource(WHEAT));
            p2->removeResource(IRON, p2->getResource(IRON));
            p2->addResource(WOOD, 2);

            //Delete all the resources from Player 3 and add him 3 wood
            p3->removeResource(WOOD, p3->getResource(WOOD));
            p3->removeResource(BRICK, p3->getResource(BRICK));
            p3->removeResource(SHEEP, p3->getResource(SHEEP));
            p3->removeResource(WHEAT, p3->getResource(WHEAT));
            p3->removeResource(IRON, p3->getResource(IRON));
            p3->addResource(WOOD, 3);

            //Use the Monopoly card - get all the woods from the other players (2+3)
            catan->useDevelopmentCard(1, 1, true);

            //Check if the resources were updated correctly
            CHECK_EQ(p1->getResource(WOOD), 1+2+3);
            CHECK_EQ(p2->getResource(WOOD), 0);
            CHECK_EQ(p3->getResource(WOOD), 0);

            //Try to use the card again after using it
            CHECK_THROWS(catan->useDevelopmentCard(1, 1, true));
        }

        //Check using Victory Point card - get 3 points for player 1
        SUBCASE("Victory Point")
        {              
            //Get the points of the player 1 - before using the card
            int points = p1->getPoints();

            //Use the Victory Point card 3 times - get 3 points
            catan->useDevelopmentCard(1, 3, true);
            catan->useDevelopmentCard(1, 4, true);
            catan->useDevelopmentCard(1, 5, true);

            //Check if the points were updated correctly
            CHECK_EQ(p1->getPoints(), points+3);

            //Try to use the card again after using it
            CHECK_THROWS(catan->useDevelopmentCard(1, 3, true));
            CHECK_THROWS(catan->useDevelopmentCard(1, 4, true));
            CHECK_THROWS(catan->useDevelopmentCard(1, 5, true));
        }

        //Check using Road Building card - build 2 roads for player 1 (on known places)
        SUBCASE("Road Building")
        {   
            //Get the Wood and Brick resources of player 1 - before using the card
            int wood = p1->getResource(WOOD);
            int brick = p1->getResource(BRICK);
            
            //Check 3 roads: (2,1) and (0,0) - not built yet, (3,0) - built by player 1
            CHECK_FALSE(catan->getBoard().getHexagon(2).getRoadVertex(1).isOnUseByStructure());
            CHECK_FALSE(catan->getBoard().getHexagon(0).getRoadVertex(0).isOnUseByStructure());
            CHECK_EQ(catan->getBoard().getHexagon(3).getRoadVertex(0).getIDPlayerOwner(), 1);

            //Use the Road Building card - build 2 roads on known places (2,1) and (0,0)
            catan->useDevelopmentCard(1, 2, true);

            //Check if the 2 roads were built correctly and by player 1
            CHECK(catan->getBoard().getHexagon(2).getRoadVertex(1).isOnUseByStructure());
            CHECK(catan->getBoard().getHexagon(0).getRoadVertex(0).isOnUseByStructure());
            CHECK_EQ(catan->getBoard().getHexagon(2).getRoadVertex(1).getIDPlayerOwner(), 1);
            CHECK_EQ(catan->getBoard().getHexagon(0).getRoadVertex(0).getIDPlayerOwner(), 1);

            //Check if the resources were not changed
            CHECK_EQ(p1->getResource(WOOD), wood);
            CHECK_EQ(p1->getResource(BRICK), brick);
        }

        // Check using Knight card - get 2 points for player 1
        SUBCASE("Knight")
        {
            //Get the points of the player 1 - before using the card
            int points = p1->getPoints();

            //Use the Knight card 3 times - get 2 points for having the largest army
            catan->useDevelopmentCard(1, 7, true);
            catan->useDevelopmentCard(1, 8, true);
            catan->useDevelopmentCard(1, 9, true);

            //Check if the points were updated correctly
            CHECK_EQ(p1->getPoints(), points+2);

            //Try to use the card again after using it
            CHECK_THROWS(catan->useDevelopmentCard(1, 7, true));
            CHECK_THROWS(catan->useDevelopmentCard(1, 8, true));
            CHECK_THROWS(catan->useDevelopmentCard(1, 9, true));
        }
    }
    
    SUBCASE("Trade development cards between players")
    {
        //Clear all the development cards from the players
        p1->clearAllDevelopmentCard();
        p2->clearAllDevelopmentCard();
        p3->clearAllDevelopmentCard();

        //Initialize the development cards pack - like the test mode
        catan->initializeDevePack(true);

        //Add 20 resources from iron, wheat, sheep to p1 and p2
        p1->addResource(IRON, 20);
        p1->addResource(WHEAT, 20);
        p1->addResource(SHEEP, 20);

        p2->addResource(IRON, 20);
        p2->addResource(WHEAT, 20);
        p2->addResource(SHEEP, 20);

        // Add 1 wood to each player
        p1->addResource(WOOD, 1);
        p2->addResource(WOOD, 1);
        p3->addResource(WOOD, 1);

        //Try to use the card before buying it - should throw exception
        CHECK_THROWS(catan->useDevelopmentCard(1, 0, true));

        //p1 buys development card (the first card on the deck is Year of Plenty)
        catan->buyDevelopmentCard(1);

        //End the turn of the player 1
        catan->endPlayerTurn(1);
        
        //Player 2's turn:
        //Try to use the card before buying it - should throw exception
        CHECK_THROWS(catan->useDevelopmentCard(2, 0, true));

        //Buy development card (the second card on the deck is Monopoly)
        catan->buyDevelopmentCard(2);

        //End the turn of the player 2
        catan->endPlayerTurn(2);

        //Player 3's turn: (Do nothing)
        //End the turn of the player 3
        catan->endPlayerTurn(3);

        //Player 1's turn:
        //Player 1 trades with player 2: 1 Year of Plenty for 1 Monopoly
        catan->tradeDevelopmentCard(1, 2, 0, 0);

        // Sum all the woods of the players - for the next test
        int sumWood = p1->getResource(WOOD) + p2->getResource(WOOD) + p3->getResource(WOOD);

        //Uses the Monopoly card (that he got from player 2) - get all the woods from the other players
        catan->useDevelopmentCard(1, 0, true);

        //Check if the card was used correctly (player 1 got sumWood and the other players 0)
        CHECK_EQ(p1->getResource(WOOD), sumWood);
        CHECK_EQ(p2->getResource(WOOD), 0);
        CHECK_EQ(p3->getResource(WOOD), 0);

        //Try to trade a card after using it - should throw exception
        CHECK_THROWS(catan->tradeDevelopmentCard(1, 2, 0, 0));

        //End the turn of the player 1
        catan->endPlayerTurn(1);

        //Player 2's turn:
        //All the Wood and Brick resources of player 2 before using the card
        int wood = p2->getResource(WOOD);
        int brick = p2->getResource(BRICK);

        // Uses the Year of Plenty card - get 1 wood and 1 brick
        catan->useDevelopmentCard(2, 0, true);

        //Check if the resources were updated correctly
        CHECK_EQ(p2->getResource(WOOD), wood+1);
        CHECK_EQ(p2->getResource(BRICK), brick+1);

        //player 3 try to trade not on his turn - should throw exception
        CHECK_THROWS(catan->tradeDevelopmentCard(3, 1, 0, 0));

        //player 2 try to trade with himself - should throw exception
        CHECK_THROWS(catan->tradeDevelopmentCard(2, 2, 0, 0));

        //End the turn of the player 2
        catan->endPlayerTurn(2);

        //Player 3's turn: (Do nothing)
        //End the turn of the player 3
        catan->endPlayerTurn(3);

        //Player 1's turn:
        //player 1 try to trade on cards that he doesn't have - should throw exception
        CHECK_THROWS(catan->tradeDevelopmentCard(1, 2, 0, 0));
    }

    SUBCASE("Winning the game")
    {
        //Check that no one won the game (got 10 points)
        CHECK_FALSE(catan->checkWinner(1)); // got 9 points
        CHECK_FALSE(catan->checkWinner(2)); // got 6 points
        CHECK_FALSE(catan->checkWinner(3)); // got 4 points

        //Add 1 point to player 1 - to check if he won the game
        p1->addPoints(1);

        //Check that player 1 won the game and the other players didn't
        CHECK(catan->checkWinner(1));
        CHECK_FALSE(catan->checkWinner(2));
        CHECK_FALSE(catan->checkWinner(3));
    }
}
