# EGP-410
Template projects for base code for EGP 410 assignments.

# This repository contains three major directories:
 * DeanLib - Base utility library provided by Dean Lawson. Memory tracking and basic vector mathematics utilities.
 * External Libs - Allegro 5.0.10 support libraries.
 * Game AI - Base source code for EGP 410 Assignments
   * pathfinding
   * state machine
   * steering

Link to commit on Github: 
https://github.com/Kellers176/EGP-410

How to compile/link project: 
1- Open up Folder EGP-410.
2- Open up the GameAI folder.
3- Open up the component steering SDL folder.
4- Scroll and open the steering.sln file.
5- Run the Local Windows Debugger at the top of the screen.

Keyboard Inputs:
Left Mouse Button - Moves the player character on the screen to the location of the mouse.
Enter Key - Adds an arrow Unit to the screen that uses the Wander and Chase behavior.
Escape - Exits the running application.
D Key - Deletes a random arrow Unit from the screen (Not the player).
Left Mouse Button - Moves the player character on the screen to the location of the mouse.
Enter Key - Adds an arrow Unit to the screen that uses the Flock behavior.
Escape - Exits the running application.
D Key - Deletes a random arrow Unit from the screen.
A Key - Adds ten arrow Units in a random location that uses the Flock behavior.
1 Key - Makes the current Weight change assigned to the GroupAlignmentWeight enum.
2 Key - Makes the current Weight change assigned to the CohesionWeight enum.
3 key - Makes the current weight change assigned to the SeperatonWeight enum.
Minus Key - Subtracts 0.1 from the current weight change variable.
Equals(=) Key - Adds 0.1 to the current weight change variable.
S Key - Saves the updated weight data to Data.txt file.
