# Settler's of War
Kathryn Osborn

CSCI 3010 Final Project

A Qt Project

# Build
1. Import project in Qt: Select File > New File or Project > Import Project > Import Existing Project

# Game Instructions
To begin the game input the total number of players and number of human players in the first window. Note: This is a pass-and-play game. Once the game screen pops up, feel free to enter names for the players on the left-hand side bar. You can even change the name of the computer-controlled players if you like! The color behind the player's name indicates the color of your buidings on the game. 
## Initial Build Phase:
For everyone's first turn you should build 2 outposts and 2 walls. The walls don't have to be attached to each of the outposts but they must be attached to at least one. The other may be attached to the first wall.

### How To Build an Outpost
An outpost requires 1 of each of the resources. To build, select Outpost in the Build Options dropdown. Then click on the circular intersection you would like to build on. If the build button becomes enabled, then your choice is valid and you may click the build button to build the outpost. Note, on your first turn you may build an outpost anywhere you'd like. However, on subsequent turns, an outpost can only be place on an intersection that does not contain another building and that you have a wall coming into. 

### How To Build a Wall
A wall requires 1 Oil and 1 Steel. To build, select Wall in the build Options dropdown. Then right-click on two intersections in turn. If the build button becomes enabled, then your choice is valid and you may click the build button to build the wall. Walls must be connected on one end to an intersection in which you have an outpost or base, or an intersection that you have another wall coming into. Furthermore, you cannot build a wall through another player's base or outpost. 

## Regular Game Play

After your initial turn you will be awarded one resource for every tile that your outpost touches. You can now build, trade, and attack as you see fit. 

### Building

#### Outposts
Outposts can only be placed on an intersection that does not contain another building and that you have a wall coming into. Refer to How To Buid an Outpost for details. Outposts are worth 1 victory point and collect 1 resource for every dice roll that corresponds to a tile touching the outpost. 

#### Walls
Walls must be connected on one end to an intersection in which you have an outpost or base, or an intersection that you have another wall coming into. Furthermore, you cannot build a wall through another player's base or outpost. Refer to How to Build a Wall for details. Walls are worth no victory points and do not help you collect resources. However, walls are vital to game strategy as you cannot build more outposts without walls!

#### Bases
Bases can only be built on intersections in which you have already built outposts. They are built in a similar manner as outposts, just select Base from the build drop down and click on a vaild interection. Bases are worth 2 victory points and bring in 2 resources for every dice roll that corresponds to a tile touching the base. 

### Trading
You may trade with the bank at any point during your turn. The trade ratio is 3-1. To trade select the resource you'd like to trade for and the resource you'd like to trade away using the drop downs. If the trade is valid the trade button will be enabled. 

### Attacking
Every time you roll a 7 (the most likely roll) you earn a troop! Once you have 3 troops you can attack another player's buildings. You can only attack bases and outposts. To launch a successful attack you must have enough resources to purchase the building that you are attacking. Upon success you will be the new owner of the building you attacked!

### Winning the Game
The first player to 8 victory points wins! 

# Testing 
In a testing implementation I would focus on how my objects interact with eachother. The game is responsible for maintaining most of the state of the game, however objects such as the nodes, players and player dashboard play a large role in keeping the game functioning. I will discuss how I would test these interactions separately in turn. 
* Nodes: 
  * Every node object contains a vector of tiles that represents the tiles that surround it. This is essential to game play and although is only created once during the game should be tested.
  * Nodes primary responsibility is keeping track of who owns the node. That is, a node must know which player has a building on it, what type of building it is and which players have walls coming into the node. I would test each aspect of this as I continue to change the owners and the building types. 
  * Nodes emit signals to the game object when they are clicked. These signals must be handeled correctly in order for players to build where they would like to build. 
