# Catan Game Implementation

## Overview
This project implements a digital version of the popular board game "Settlers of Catan". Players engage in building settlements, cities, and roads, collecting resources, and trading to accumulate victory points. The goal is to achieve 10 victory points to win the game.

## Rules of the Game
- **Players**: Supports up to 3 players.
- **Turn Order**: Sequential turns; starting player chosen randomly.
- **Resources**: Wood, Brick, Sheep, Wheat, and Iron.
- **Development Cards**: Purchase, use, and trade cards for knights, victory points, road building, monopoly, and year of plenty.
- **Winning Condition**: First player to reach 10 victory points wins.

## Class Hierarchy
- **Catan Class**: Manages game flow, players, and board interactions.
  - Methods include setting up the game, handling turns, and determining the winner.
  
- **Board Class**: Represents the game board with hexagonal lands.
  - Methods include placing roads, settlements, and cities, distributing resources, and printing the board.
  
- **Player Class**: Represents a player with resources, development cards, and points.
  - Methods include managing resources, development cards, points, and interacting with the board.
  
- **Hexagon Class**: Represents a hexagonal land on the board.
  - Methods include managing properties of the hexagon, checking placement availability, and printing its state.
  
- **Vertex Class**: Represents a vertex where roads, settlements, and cities can be placed.
  - Methods include managing ownership, structure placement, collectability, and ownership checks.
  
- **DevelopmentCard Classes**:
  - **Base Class (DevelopmentCard)**: Common functionalities like type, usage status, and usage action.
  - **Derived Classes (KnightCard, MonopolyCard, RoadBuildingCard, VictoryPointCard, YearOfPlentyCard)**: Specific methods and functionalities based on the type of development card.

## Libraries Used
- Standard C++ Library: Basic functionalities such as input/output, strings, vectors, and memory management.
- Specific headers (`<iostream>`, `<vector>`, `<string>`, `<memory>`): Used for various functionalities in the game.

## Methods Description
### Catan Class
- **Catan(Player& p1, Player& p2, Player& p3, bool isTest=false)**: Constructor to initialize the game with three players.
- **~Catan()**: Destructor.
- Methods like `getBoard()`, `getPlayerTurn()`, `getPlayerByName()`, `placeSettlement()`, `placeRoad()`, `rollDice()`, `buyDevelopmentCard()`, `useDevelopmentCard()`, etc., managing game processes and interactions.

### Board Class
- **Board(bool isTest=false)**: Constructor to initialize the board.
- Methods like `placeRoad()`, `placeSettlement()`, `placeCity()`, `printBoard()`, `getHexagon()`, `getVertexNeighbors()`, `isRoadOnHexagonOnUse()`, `isSettlementOnHexagonOnUse()`, etc., managing board state and interactions.

### Player Class
- **Player(std::string name)**: Constructor to initialize a player with a name.
- Methods like `getName()`, `getPoints()`, `addResource()`, `removeResource()`, `buyDevelopmentCard()`, `useDevelopmentCard()`, `addPoints()`, `printResources()`, `printDevelopmentCards()`, etc., managing player state and interactions.

### Hexagon Class
- **Hexagon()**, **Hexagon(int idOfHexagon, int resource)**: Constructors to initialize a hexagon with an ID and resource type.
- Methods like `getIdOfHexagon()`, `getResource()`, `getResourceName()`, `getRoadVertex()`, `getSettlementVertex()`, `isRoadVertexOnUse()`, `isSettlementVertexOnUse()`, `canPlaceRoad()`, `placeRoad()`, `canPlaceSettlement()`, `placeSettlement()`, `placeCity()`, `printHexagon()`, `isSett()`, etc., managing hexagon properties and interactions.

### Vertex Class
- **Vertex()**: Default constructor.
- Methods like `getIDPlayerOwner()`, `getStructure()`, `setIDPlayerOwner()`, `setStructure()`, `isOnUseByStructure()`, `isOnUseByPlayer()`, `placeRoad()`, `placeSettlement()`, `placeCity()`, `isStructureOfPlayer()`, `collect()`, `isCollectable()`, etc., managing vertex properties and interactions.

### DevelopmentCard Classes
- **Base Class (DevelopmentCard)**: Methods like `getType()`, `getTypeName()`, `isUsed()`, `useDevelopmentCard()`, etc., common functionalities for all development cards.
- **Derived Classes (KnightCard, MonopolyCard, RoadBuildingCard, VictoryPointCard, YearOfPlentyCard)**: Specific methods and functionalities based on the type of development card.

## Running the Program
To compile and run the program, you can use the provided Makefile with the following commands in your terminal:

1. **make clean**: Clean up all the compiled files.
    ```sh
    make clean
    ```

2. **make**: Compile the entire program.
    ```sh
    make
    ```

3. **make catan**: Run a demo of the game live.
    ```sh
    make catan
    ```

4. **make test**: Run the tests for the program.
    ```sh
    make test
    ```
