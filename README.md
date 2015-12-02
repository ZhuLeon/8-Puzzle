# 8-Puzzle
8-Puzzle solver using A* algorithm with a choice of 3 Heuristics  
1. Uniform Cost Search  
2. Manhattan Distance  
3. Misplaced Tile

## How to use
To compile, use the makefile by typing `make` into the terminal window.
The user will be prompted with directions.  
8 puzzles solution will be in the form of  
number|number|number  
number|number|number  
number|number|blank  

##notes
This was done for a Aritifical Intelligence course studying machine learning.
Uniform Cost search is the most memory and time costly heuristic.
Manhattan is a relatively fast and has low memory cost for puzzles with solution depths of 20 or less.
Misplaced Tile is fast on puzzles with shallow solution depths and exponentially increases in time and memory cost as solution depth increases.

## Other
This does not detect for unsolvable puzzles.


