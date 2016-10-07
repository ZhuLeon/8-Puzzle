# 8-Puzzle
8-Puzzle solver using A* algorithm with a choice of 3 Heuristics  
1. Uniform Cost Search  
2. Manhattan Distance  
3. Misplaced Tile

## Synopsis
Goal: Provide a solution to the 8-puzzle in decent time

Problem: The 8-puzzle has `9!/2` many different possible states. Even for a computer,
a brute force approach at searching through all those possible states would take
an undesirable amount of time.

Solution: Instead of looking at all possible states of the game board, we determine
which move will bring us toward the solution using smart heursitcs. This thereby greatly reduces the 
amount of states to search through reducing compuation time.

## Installation
To install run the below code in your terminal
```
$ git clone  https://github.com/ZhuLeon/8-Puzzle.git
$ cd 8-Puzzle
$ make
```
After running the file The user will be prompted with directions. 

8 puzzles solution will be in the form of  
number|number|number  
number|number|number  
number|number|blank  

##Sample Traceback
[Coming Soon]

##notes
This was done for a Aritifical Intelligence course studying machine learning.
Uniform Cost search is the most memory and time costly heuristic.
Manhattan is a relatively fast and has low memory cost for puzzles with solution depths of 20 or less.
Misplaced Tile is fast on puzzles with shallow solution depths and exponentially increases in time and memory cost as solution depth increases.

## Other
This does not detect for unsolvable puzzles.
