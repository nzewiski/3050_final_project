# 3050_final_project
Final project repository for CS 3050 - Advanced Algorithm Design

The purpose of this project is to utilize and build upon knowledge of graph searching 
algorithms. In robotics, it is common to traverse through rooms or buildings and gather
data. To do this the robot traverses through, using graph searching, until it finds the way
out. In this project we implement a motion planning algorithm which coordinates the motion
of two robots in a room. The first robot starts at starting point S and has to travel to
exit location E. The second robot starts at starting location F and has to travel to exit
location L. In the room, a robot can only "move" one spot per movement, which could be up, 
down, left, and right. This means that a robot can't teleport to other parts of the room, 
traverse through walls, etc.
Furthermore, for coordination purposes:

	-Only one robot moves in one time instant. The two robots may alternate their
		movements, but they never move simultaneously.
	-In order to maintain their coordination, they are not allowed to come closer than 
		horizontal and vertical interference parameters Rx and Ry. In other words, 
		the two robots should always maintain a horizontal distance greater than Rx
		and a vertical distance greater than Ry.

Dimensions of the rooms cannot be assumed as each line of the room may be sized differently
than other lines, however the program depends on a maximum maze size that is set to 256 x 256 
by default but could be made larger if necessary. Several test mazes have been included in
the repository.

The most natural way to implement the project is to view the room as a graph with each
square representing a vertex. I utilized the Bellman-Ford algorithm and developed upon it 
to create a graph traversal algorithm which finds a path for the first robot from (S) to (E)
and a path for the second robot from (F) to (L) using the array returned by the Bellman-Ford
algorithm as a reference.

General project details include:

	-The program is written in C++.
	-The Code::Blocks IDE was used to compile and test the program. The program has also
		been tested using the Netbeans IDE
	-A project report has been included in which efforts, algorithms, and contributions are 
		detailed.
	-A moderate amount of error checking and resource management is done by the program.
		The application should checks that each line from the input file is properly
		formatted, that the file is successfully opened, the file is successfully
		closed upon reading of the file, and that all allocated space is 
		de-allocated at program exit. If the input is not properly formatted, an
		error is reported on stdout and the program is killed.
	-The program makes use of only standard input/output libraries and the string library.
	-A moderate amount of formatting and documentation has also been done. Comments 
		are descriptive and used to illustrate the purpose and inner workings of
		algorithms and functions.

The program does not require command line input. Instead, it prompts the user for a maze input 
file and the values of Rx and Ry. The input file is the floor plan of the room and is formatted 
as follows:

	-'#' indicates a wall or obstacle.
	-End of line character and start of line character also indicate walls.
	-'<space>' indicate emply spots that robots can move to.
	-'S' starting position of robot one.
	-'E' exit position of robot one.
	-'F' starting position of robot two.
	-'L' exit position of robot two.