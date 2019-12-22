# Game name: Snake

## How to play?

The good old snake game is back! All you have to do is to catch with the snake the dots and grow in size. The bigger you are in size, the bigger the score will be! Watch out for wall colissions and be carefull not to eat yourself, because you may lose one life and you only have three. If you want a greater challange, select a higher level from the settings option, where you can also change the contrast. Your highscore from last game will be saved in the Hscore option, so you can brag to your friends afterwards.

If you want to find out more about the creator, select the Info option and access the link provided there.

Video demo: 

Below you can see the technical details:
 1. Hardware: 
    - 8x8 led matrix
    - LCD
    - joystick
    - MAX7219 Driver
    - Potentiometer

 2. Game Specifications: 
    - Score: 
      - it depends on the size of the snake and difficulty: its formula is based on the length of the snake
                                                                which is added to the level and the sum is multiplied by 3;
                                                                from this result it is subtracted the value of the sum
                                                                between the initial length of the snake and the level, so the 
                                                                score can start at 0;
      - the score is calculated for each level; this means that the final score will be the combined score for each of
             the 3 lives the player had.

    - Difficulty: the speed at which the snake will move will increase with every level. Also, completing a level will be                                 made at a certain score. Levels provide a dfference in difficulty and it is the player's choice what level 
                        he wants to play

    - Lives: each game, a player will have 3 lives

 3. LCD:
    - Menu: 
      - Start game
      - High Score: updated every game.
      - Settings: Starting level: the player can choose between 1, 2 and 3;
                  LCD contrast: the player is instructed to use the potentiometer(POT) in order to change that;
      - Info: Creator name, Github link, Game name
     - Displayed info during the game: score, lives, level
     - Game over screens: 
     - "Congratulations, you finished the lvl"
     - "Game over" (on the matrix);
     - Switch to the start screen after

Hardware image: 

![Image description](https://raw.githubusercontent.com/cos99/Robotics/master/Matrix%20game/20191222_081253.jpg)

