A project built for the CS32 class at UCLA

The following description of the game is sourced from the project specifications written by Professor Smallberg:

A simple action-adventure game called Doom. In Doom, the player navigates through a multi-level temple in search of a golden idol. Upon locating the idol, the player is instantly transported out of the temple and wins the game.

Upon starting a new game, you the player are placed on the top level of the temple. From here, you must work your way through the rooms on that level, battling monsters, finding treasures, and using staircases to descend ever deeper into the temple's depths. When you reach the bottom level of the temple, you must reach the golden idol in order to win the game.

As you move through a level, you will encounter a number of different types of monsters that you will have to battle, including:

Bogeymen (shown on screen as a B)
Dragons (shown on screen as a D)
Goblins (shown on screen as a G)
Snakewomen (shown on screen as an S)
Each of these monsters has a different behavior and reacts differently to the player (who is shown on screen as an @). More details about the monsters are below.

In addition to monsters, you'll find many different objects during your adventure:

Impenetrable walls (shown on screen as #)
Stairways down to the next level (shown on screen as >)
The golden idol (shown on screen as &)
Weapons (all weapons are shown on screen as a ) character)
Maces
Short swords
Long swords
Magic fangs of sleep (that put an opponent to sleep)
Magic axes (that hit an opponent more often than regular weapons)
Scrolls (all scrolls are shown on screen as ?)
A scroll of teleportation (when read, randomly moves the player)
A scroll of improve armor (when read, makes it harder for monsters to hit the player)
A scroll of raise strength (when read, makes a player's blows more effective)
A scroll of enhance health (when read, raises maximum hit points)
A scroll of enhance dexterity (when read, makes it more likely the player will hit an opponent)
Here is an example of what the game display might look like:

####################################################################
######################             ##           ####################
######################          B  ##           ##              ####
######################             ##     G                  )  ####
######################             ##           ##       S      ####
#####             ####           ?D        #######    G         ####
##### >           ####      B      ###### ########              ####
#####        D    ####             ##         ########### ##########
#####              S           )   ##         ########### ##########
#####     G       ###################         ########### ##########
#####             ################### D@      ########### ##########
#####################################       S ########### ##########
#####################################         ########          ####
######################################################   ?      ###
######################################################          ###
###################################################################
###################################################################
###################################################################
Level: 3, Hit points: 10, Armor: 3, Strength: 2, Dexterity: 2

Player slashes short sword at the Dragon and misses.
the Dragon swings long sword at Player and misses.
To control the player in the game, you issue commands from the keyboard. Use the getCharacter function we will supply you to read characters from the keyboard in a way that does not require the user to hit Enter after each command. (Also, getCharacter does not echo the character onto the screen.) Doom is not a "real-time" game; the game progresses only when the player issues a command. After each player command, the monsters each make a move and then the screen is updated to reflect the current state of the game. The player commands are:

Move one space using the arrow keys or alternative movement letters:
h to move left
l to move right
k to move up
j to move down

Attack a monster next to you by moving in its direction.
Pick up an object by standing on it and typing g.
Wield a weapon by typing w and then selecting a weapon from your inventory.
Read a scroll by typing r and then selecting a scroll from your inventory.
See an inventory of your items by typing i.
When standing on a stairway, descend deeper into the temple by typing >.
Quit the game by typing q.

