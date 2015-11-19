# 3050_final_project
Final project repository for CS 3050 - Advanced Algorithm Design

The purpose of this project is to utilize and build upon knowledge of graph searching 
algorithms. In robotics, it is common to traverse through rooms or buildings and gather
data. To do this the robot traverses through, using graph searching, until it finds the way
out. In this project we implement a motion planning algorithm which coordinates the motion
of two robots in a room. The first robot starts at starting point S and has to travel to
exit location E. The second robot starts at starting location F and has to travel to exit
location L. In the room, a robot can only move one spot per movement, which could be up, 
down, left, and right. This means that a robot can't teleport to other parts of the room.
Furthermore, for coordination purposes:

	-Only one robot moves in one time instant. The two robots may alternate their
		movements, but they never move simultaneously.
	-In order to maintain their coordination, they are not allowed to come closer than 
		an interference parameter R. In other words, the two robots should always 
		maintain a horizontal and vertical distance greater than R.

Dimensions of the rooms cannot be assumed as each line of the room may be sized differently
than other lines. An example expected input will be similar to the sample input file that
is included in the repository as example.txt.

The most natural way to implement the project is to view the room as a graph with each
square representing a vertex (what are the edges?). I developed a graph traversal 
algorithm which finds a path for the first robot from (S) to (E) and a path for the second
robot from (F) to (L), using backtracking when going to previous spaces ensuring that the
two robots are never closer than R.

General constraints include:

	-The program is written in either C or C++. (Other languages may be allowed but
		must be cleared for use)
	-Either use a netbeans project or use a Makefile to compile and run the program.
		Do not use Visual Studio.
	-Include a README file to tell the TA's how to run the program and how to interpret
		the output.
	-Include a project report in which efforts, algorithms, and contributions are 
		detailed. This report is primarily used to give partial credit if the 
		program does not work properly.
	-Any graph theory libraries are not allowed.
	-All graphing algorithms should be implemented.
	-A moderate amount of error checking and resource management is required. The 
		application should check that each line from the input file is properly
		formatted, that the file is successfully opened, the file is successfully
		closed upon reading of the file, and that all allocated space is 
		de-allocated at program exit. If the input is not properly formatted, an
		error is reported on stdout and the program is killed.
	-Libraries for statdard i/o, arrays, vectors, stacks, heaps, lists, and queues
		are allowed.
	-A moderate amount of formatting and documentation is required. Comments should be
		descriptive and used to illustrate the purpose and inner workings of an
		algorithm or function. Do not use comments to annotate each line or 
		self-evident logic.

The program takes at least two arguments on the command line. One of these arguments is the
input file to the program. The second is the interference parameter R. The input file is
the floor plan of the room and is formatted as follows:

	-'#' indicates a wall or obstacle.
	-End of line character and start of line character also indicate walls.
	-'<space>' indicate emply spots that robots can move to.
	-'S' starting position of robot one.
	-'E' exit position of robot one.
	-'F' starting position of robot two.
	-'L' exit position of robot two.