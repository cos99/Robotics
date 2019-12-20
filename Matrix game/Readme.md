Game name: Snake

Requirements:
           
            1.Hardware: 
              -8x8 led matrix
              -LCD
              -joystick
              -MAX7219 Driver
            
            2.Game Specifications: 
              -Score: it depands on the size of the snake and difficulty
              -Difficulty: the speed at which the snake will move will increase with every level and as levels
                           increase, there will be new terrain added in which the player can collide. Also, moving up
                           in levels will be made at a certain score.
              -Lives: each game, a player will have 2 lives
            
            3.LCD: 
              -Welcome message
              -Menu: 
               * Play game
               * High Score: saved in EEPROM, updated every game.
               * Settings: Starting level
                           Player name
               * Info: Creator name, Github link, Game name
              -Displayed info during the game: score, lives, level
              -Game over screens: 
               -"Congratulations, you finished the game"
               -"Level nth completed"
               -"Game over! Another round maybe?"
               -"New Highscore!"
               -Switch to the start screen after
                                       
