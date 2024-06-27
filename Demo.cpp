// ID: 315233486
// Mail: Eilonashwal30@gmail.com

#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <vector>
#include "Catan.hpp"
#include "Player.hpp"
#include "Board.hpp"

using namespace std;
using namespace ariel;

int main()
{
    // make a space between the terminal and the game 
    cout<<endl;
    cout<<endl;

    // start the game
    cout << "Welcome to Catan!" << endl;
    cout << endl;

    // Create the players
    Player p1("Lior");
    Player p2("Roi");
    Player p3("David");

    // Create the board
    Catan catan(p1, p2, p3);
    catan.printBoard(false); // Print the board - choosen randomly

    for (int i = 0; i < 3; i++)
    {
        int cp= catan.getPlayerTurn();// The current player
        int hexagon, vertex; // The location of the settlement and the road that the player will insert

        // Ask the player to insert the location (hexagon and vertex) of the settlement
        cout << "Player " << catan.getPlayer(cp).getName() << ", please insert the location of the settlement:" << endl;
        cout << "hexagon: ";
        cin >> hexagon;
        cout << "vertex: ";
        cin >> vertex;
        catan.placeSettlement(cp, hexagon, vertex); // Place the settlement in the location that the player inserted

        // Ask the player to insert the location (hexagon and vertex) of the road
        cout << "Player " << catan.getPlayer(cp).getName() << ", please insert the location of the road:" << endl;
        cout << "hexagon: ";
        cin >> hexagon;
        cout << "vertex: ";
        cin >> vertex;
        catan.placeRoad(cp, hexagon, vertex); // Place the road in the location that the player inserted

        // Ask the player to insert the location (hexagon and vertex) of the second settlement
        cout << "Player " << catan.getPlayer(cp).getName() << ", please insert the location of the second settlement: " << endl;
        cout << "hexagon: ";
        cin >> hexagon;
        cout << "vertex: ";
        cin >> vertex;
        catan.placeSettlement(cp, hexagon, vertex); // Place the second settlement in the location that the player inserted

        // Ask the player to insert the location (hexagon and vertex) of the second road
        cout << "Player " << catan.getPlayer(cp).getName() << ", please insert the location of the second road: " << endl;
        cout << "hexagon: ";
        cin >> hexagon;
        cout << "vertex: ";
        cin >> vertex;
        catan.placeRoad(cp, hexagon, vertex); // Place the second road in the location that the player inserted

        // Ask the player to choose the resource that he wants to get from the settlement that he placed
        catan.chooseResorces(cp);

        // End the turn of the player
        catan.endPlayerTurn(cp);
    }

    // Start the game 
    
    int action = -1; // The action that the player will choose

    // The game will continue until there is a winner or the player will choose to exit
    while (catan.checkWinner(catan.getPlayerTurn())|| action!=0) 
    {
        int cp= catan.getPlayerTurn();// The current player

        // for design
        cout<<endl;

        // Ask the player to choose an action
        cout << catan.getPlayer(cp).getName() << ", please choose an action: " << endl
             << "1. Roll the dice" << endl
             << "2. Build a road" << endl
             << "3. Build a settlement" << endl
             << "4. Build a city" << endl
             << "5. Buy a development card" << endl
             << "6. Use a development card" << endl
             << "7. Trade resources or development cards with another player" << endl
             << "8. Print details" << endl
             << "9. End turn" << endl
             << "0. To exite the program"<<endl;

        cin >> action; // Get the action that the player chose

        switch (action)
        {
            case 1: // Roll the dice
                catan.rollDice(cp);
                break;

            case 2: // Build a road
            {
                int hexagon, vertex; // The location of the road that the player will insert

                cout << "Please insert the location of the road: " << endl;
                cout << "hexagon: ";
                cin >> hexagon;
                cout << "vertex: ";
                cin >> vertex;
                catan.placeRoad(cp, hexagon, vertex); // Place the road in the location that the player inserted
            }
            break;

            case 3: // Build a settlement
            {
                int hexagon, vertex; // The location of the settlement that the player will insert

                cout << "Please insert the location of the settlement: " << endl;
                cout << "hexagon: ";
                cin >> hexagon;
                cout << "vertex: ";
                cin >> vertex;
                catan.placeSettlement(cp, hexagon, vertex); // Place the settlement in the location that the player inserted
            }
            break;

            case 4: // Build a city
            {
                int hexagon, vertex; // The location of the city that the player will insert

                cout << "Please insert the location of the city: " << endl;
                cout << "hexagon: ";
                cin >> hexagon;
                cout << "vertex: ";
                cin >> vertex;
                catan.placeCity(cp, hexagon, vertex); // Place the city in the location that the player inserted
            }
            break;

            case 5: // Buy a development card
                catan.buyDevelopmentCard(cp);
                break;

            case 6: // Use a development card
            {
                catan.getPlayer(cp).printDevelopmentCards(); // Print the development cards of the player
                cout << "Please insert the index of the development card: ";
                int index;
                cin >> index;
                catan.useDevelopmentCard(cp, index); // Use the development card that the player chose
            }
            break;

            case 7: // Trade resources or development cards with another player 
            {
                cout<<"What do you want to trade?"<<endl;
                cout<<"1. Resources"<<endl;
                cout<<"2. Development cards"<<endl;

                int input;
                cin>>input;

                switch (input)
                {
                    case 1: // Trade resources
                    {
                        cout << "Please insert the number of the player you want to trade with (1,2,3): ";
                        int p2;
                        cin >> p2;

                        int res1, res2, amount1, amount2; // The resources that the player will trade

                        cout << "Please insert the resource you want to trade: " << endl
                            << "1. Wood" << endl
                            << "2. Brick" << endl
                            << "3. Wheat" << endl
                            << "4. Sheep" << endl
                            << "5. Ore" << endl;
                        cin >> res1;

                        cout << "Please insert the amount of the resource you want to trade: ";
                        cin >> amount1;

                        cout << "Please insert the resource you want to get: " << endl
                            << "1. Wood" << endl
                            << "2. Brick" << endl
                            << "3. Wheat" << endl
                            << "4. Sheep" << endl
                            << "5. Ore" << endl;
                        cin >> res2;

                        cout << "Please insert the amount of the resource you want to get: ";
                        cin >> amount2;

                        catan.tradeResorces(cp, p2, res1, res2, amount1, amount2); // Trade the resources
                    }
               
                    break;

                    case 2: // Trade development cards
                    {
                        cout << "Please insert the number of the player you want to trade with (1,2,3): ";
                        int p2;
                        cin >> p2;

                        cout<<"Your development cards are:"<<endl;
                        catan.printDevelopmentCards(cp);

                        cout<<"The other player's development cards are:"<<endl;
                        catan.printDevelopmentCards(p2);

                        cout << "Please insert the index of the development card you want to trade: ";
                        int index;
                        cin >> index;

                        cout << "Please insert the index of the development card you want to get: ";
                        int index2;
                        cin >> index2;

                        catan.tradeDevelopmentCard(cp, p2, index,index2); // Try to trade the development cards
                    }
                }
                break;
            }

            case 8: // Print details
            {
                int input = 0;
                cout << "Please choose what to print: " << endl
                    << "1. Points" << endl
                    << "2. Board" << endl
                    << "3. Development cards" << endl;
                cin >> input;

                switch (input)
                {
                case 1: // Print the points of the player
                    catan.printPoints();
                    break;

                case 2: // Print the board
                    catan.printBoard(false);
                    break;

                case 3: // Print the development cards of the player
                    catan.printDevelopmentCards(cp);
                    break;

                default:
                    cout << "Invalid input" << endl;
                    break;
                }
            }
            break;
            
            case 9: // End turn
                catan.endPlayerTurn(cp);
                break;

            case 0: // Exit
                cout << "Exiting program..." << endl;
                exit(0); // Exit the program 

            default:
                cout << "Invalid action" << endl;
                break;

        } // End of the switch statement

    } // End of the while loop

    return 0; // End of the program
      
}