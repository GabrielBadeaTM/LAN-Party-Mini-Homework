# LAN Party Tournament Manager 🎮

**Author:** Cătălin Gabriel Badea  

---

## 📌 Overview

This project implements a tournament manager for a LAN Party event organized by the Faculty of Automation and Computers.  
The program reads team data and simulates a knockout tournament using linked lists, queues, stacks, and binary search trees, all implemented with manual dynamic memory management in C.  
Not a flashy project, but a valuable learning experience during university that helped me practice core data structures and algorithmic thinking in my first year.

---

## 🎯 Assignment Requirements

- Load teams from input file into a singly linked list (inserting at the head for O(1) insertion).  
- Remove teams with the lowest team score until the number of teams is the largest power of two less than or equal to the original count.  
- Organize matches as pairs of teams in a queue; after each round, distribute winners and losers into separate stacks.  
- Winners gain experience points, updating their team score accordingly.  
- Continue tournament rounds until the top 8 teams are determined and stored separately.  
- Build and display a Binary Search Tree (BST) with the top 8 teams ordered by descending score and, if tied, by name descending.  
- Build an AVL tree from the BST and display teams at level 2.  

---

## 🛠️ Implementation Details

- **Data Structures:** Implemented singly linked lists, queues, stacks, BST, and AVL trees using pointers and dynamic memory allocation (no static arrays).  
- **List Management:**  
  - Insert teams at list head during input.  
  - Remove lowest scoring teams using a function that finds and deletes nodes by pointer manipulation, restarting traversal after each removal.  
- **Match Simulation:**  
  - Create matches in pairs from the list, enqueue them for each round.  
  - Simulate matches by comparing scores; winners pushed to winners stack, losers to losers stack.  
  - Winners receive +1 experience point for each player; team scores updated accordingly.  
  - Losers stack is cleared after each round.  
  - Winners stack dequeued in pairs to form next round’s matches.  
- **Top 8 Extraction:**  
  - When 8 teams remain, they are saved into a new list for final ranking.  
- **Trees:**  
  - Insert top 8 teams into a BST ordered by score descending, and by name descending if tied.  
  - Traverse and print BST in descending order.  
  - Insert BST elements into an AVL tree with same ordering and print all teams on level 2.  
- **Memory Management:**  
  - All allocated memory is freed after use; program is leak-free.  
  - Careful copying of data on stack pop to avoid dangling pointers.  
- **Code Modularity:**  
  - Each operation (insertion, deletion, traversal) encapsulated in small, manageable functions.  

---

## ⚠️ Notes

- The program uses dynamic memory management exclusively — no static or global arrays for storing data.
- All inputs and outputs strictly follow the specification for automated checker compatibility.  
- Indentation, naming, and modularization were carefully maintained for readability and maintainability.  
- The code compiles cleanly and runs without memory leaks.  

---

## 💬 Acknowledgments

Thank you for reviewing my implementation!  
Please feel free to reach out for any clarifications or feedback.

---

*— Cătălin Gabriel Badea*
