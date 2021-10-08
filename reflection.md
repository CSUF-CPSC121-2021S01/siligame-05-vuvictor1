# Milestone 2

## Description
In this project I mostly reused my code from milestone 4 but instead made them use pointers. At this final stage my milestone is complete. I added the ability to fire player projectiles using mouse clicks and gave the opponents the projectiles to fire. I also now have a score tracker which adds points every time an opponent collides with player projectile. And Last I created a text that displays when the game ends. Which in this case is when the player collides with the opponent or projectile.

## Challenges encountered
This project was extremely tedious and hard to debug. There was a time where I was getting an undeclared identifier error. However the problem was because my OpponentProjectile class was below my opponent class. I fixed by moving the class up, which resolved my issue. However I'm not sure how this was the solution. There is also the issue of performance. Since adding the launch projectiles my game feels slower and laggier.

## Things I've learned
I've learned the importance keeping my code clean and writing better comments. I also learned to thoroughly test my program by running the game and compiling to catch bugs early before they become harder to fix later.
