# AI_miniproject1

Project for Artificial Intelligence course, Faculty of Electronics and Information Technology, Politechnika Warszawska.

## Authors
Isabel Carnoto and Ana Martínez


## Task

For a graph describing the street network of a given city, develop a route mapping method for
pizza delivery.
Input:
- File with a graph describing the city map
- The node in which the pizzeria is, vp
- List of edges to which the pizzas need to be delivered z(, … , z9 (we assume that the supplier of needs to visit each of these).
Output: the supplier's route in the form of a list of vertices to visit, which begins and ends at node vp

## To compile
Just use the comand make

## To execute (the example from the first project submission)

bin/./location data/dataImage outputFiles/outputImage

Introduce a list of edges using the following format: number-number-number... For example: 3-4-7-9
Introduce the origin using the following format: number number. For example: 0 100 
Remember the origins coordinates should be multiples of 100.

