## Defenders
###__*C++ version of defenders using Opengl and PSP development libraries*__

### Author - __*Dean Gaffney (20067423)*__
###Subject - __*Console Game Development 2*__
---


#### Features

##### Refactoring

   - Implement collision functions __*(completed)*__
   - Implement AI function __*(completed)*__

##### Pimping

   - Two types of AI __*(completed)*__
       - Simple : Enemies move up and down firing at the player
       - Tracking : The enemies navigate through the levels towards the player and fire at player. __*(completed)*__
   - Bomb Firing  __*(completed)*__
        - Pressing the 'E' key will fire a bomb in an arc motion from the player ship, which can destroy enemies.
   - Radar __*(completed)*__
        - A scaled preview of the level on the screen.
   - Health Bar __*(completed)*__
        - A health bar which shrinks dynamically with the current player health.
    - Level Switching __*(completed)*__
        - Pressing the number '2' on the key pad allows you to move through to the next level.
    - Animation __*(completed)*__
        - Slight animation on player ship and enemies of colour changes.
    - Collisions __*(completed)*__
        - Collisions with level
        - Player collision with enemies/enemy bullets
        - Enemy Collisions with player/player bullets/player bombs
        - Bounding box implemented for collision detections
    

#### Overview 
- Player navigates a ship and must destroy enemies using bullets or bombs.
- Enemies can navigate though the level or move up and down to block player.
- Player must reach end of level to complete game

        
