#include <LedControl.h>
#include<LiquidCrystal.h>

//LCD pins
const int RS = 9;
const int E = 8;
const int D4 = 4;
const int D5 = 5;
const int D6 = 6;
const int D7 = 7;

int lineCursor = 0;

bool joyMoved = false;
int minThreshold = 450;
int maxThreshold = 550;
int buttonState = 0;
int valueSW;
int valueX = 0;
int valueY = 0;

unsigned long lastButtonTime = 0;
unsigned long currentTimeLCD = 0;
const int periodSW = 20;

int PartHscore = 0;
int Hscore = 0;
int lives = 3;
int level = 1;
int prevHscore;

LiquidCrystal lcd(RS, E, D4, D5, D6, D7);

//Joystick pins
const int pinX = A0;
const int pinY = A1;
const int pinSW = 3;

//Driver pins
const int clk = 11;
const int load = 10;
const int din = 12;

#define SIZE 8
const int advanceDelay = 20;

int snake[SIZE*SIZE][2];
int length;
int food[2], v[2];
bool gameOver = false;
unsigned long currentTime;
unsigned long prevAdvance;
int blinkCount;
const short messageSpeed = 2;
int score;

LedControl lc = LedControl(din, clk, load, 1);

//LCD portion of the code
void Menu() {

  lcd.setCursor(1, 0);
  lcd.print("Start ");
  lcd.setCursor(8, 0);
  lcd.print("HScore  ");
  lcd.setCursor(1, 1);
  lcd.print("Settings       ");
  lcd.setCursor(11, 1);
  lcd.print("Info");
}

void cursor() {
  
  lcd.setCursor(0, 0);
  lcd.print(" ");
  lcd.setCursor(7, 0);
  lcd.print(" ");
  lcd.setCursor(0, 1);
  lcd.print(" ");
  lcd.setCursor(10, 1);
  lcd.print(" ");


  if (lineCursor < 0) lineCursor = 3;
  if (lineCursor > 3) lineCursor = 0;
  if (lineCursor == 0) lcd.setCursor(0, 0);
  else if (lineCursor == 1) lcd.setCursor(7, 0);
  else if (lineCursor == 2) lcd.setCursor(0, 1);
  else if (lineCursor == 3) lcd.setCursor(10, 1);
  lcd.print(">");

}

void verPushButton() {
  
  if (valueSW == 0 && currentTimeLCD - lastButtonTime >= periodSW) 
  {
    if (buttonState == 0) {
      buttonState = 1;
    }
    else 
    {
      buttonState = 0;
    }
    lastButtonTime = currentTimeLCD;
  }
}

//Game portion of the code
void startGame() {
  prevAdvance = currentTime = 0;
  blinkCount = 3;
  int half = SIZE / 2;
  length = SIZE / 3;

  for (int i = 0; i < length; i++) {
    snake[i][0] = half - 1;
    snake[i][1] = half + 1;
  }
  
  food[0] = half + 1;
  food[1] = half - 1;

  v[0] = 0;
  v[1] = -1;
   
}


//function that renders the food the snake must eat
void render() {
  for (int i = 0; i < length; i++) {
    lc.setLed(0, snake[i][0], snake[i][1], 1);
  }
  lc.setLed(0, food[0], food[1], 1);
}

void clearMatrix() {
  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
      lc.setLed(0, i, j, 0);
    }
  }
}

bool moveForward() {
  int headSnake[2] = {snake[0][0] + v[0], snake[0][1] + v[1]};

  if (headSnake[0] < 0 || headSnake[0] >= SIZE) {
    //this delay has the scope of freezing the game so the player will know the game is 
    //over
    delay(1000);

    showGameOverMessage();
    return true;
  }

  if (headSnake[1] < 0 || headSnake[1] >= SIZE) {

    //same purpose as before
    delay(1000);
    showGameOverMessage();
    return true;
  }
  
  for (int i = 0; i < length; i++) {
    if (snake[i][0] == headSnake[0] && snake[i][1] == headSnake[1]){
      //delay has the same purpose as above
      delay(1000);
      
      showGameOverMessage();
      return true;
    }
  }

  bool increaseSize = (headSnake[0] == food[0] && headSnake[1] == food[1]);
  if (increaseSize) {
    length++;
    randomSeed(currentTime);
    food[0] = random(SIZE);
    food[1] = random(SIZE);
  }

  for (int i = length - 1; i >= 0; i--) {
    snake[i + 1][0] = snake[i][0];
    snake[i + 1][1] = snake[i][1];
    //this dealy is used for setting the speed of the snake
    delay(500/(10 * level)); 
  }

  snake[0][0] += v[0];
  snake[0][1] += v[1];
  return false;
}

void restart() {
  startGame();
  gameOver = false;
}


void readControls() {
  int x = map(analogRead(pinX), 0, 906, 2, -2);
  int y = map(analogRead(pinY), 0, 906, -2, 2);
  if (x != 0) {
    x = x / abs(x);
  }
  if (y != 0) {
    y = y / abs(y);
  }
  
  if (y != 0 && v[0] != 0) {
    v[0] = 0;
    v[1] = y;
  }

  if (x != 0 && v[1] != 0) {
    v[0] = x;
    v[1] = 0;
  }
  
}

//the matrix used for the game over message on the led matrix
const PROGMEM bool gameOverMessage[8][90] = {
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,1,1,0,0,0,1,1,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,1,1,1,1,0,0,0,1,1,0,0,1,1,0,0,1,1,1,1,1,1,0,0,1,1,1,1,1,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,1,0,1,1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,0,0,0,0,1,1,0,0,1,1,0,0,1,1,1,1,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,1,1,0,0,1,1,1,1,1,1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,0,0,0,0,1,1,0,0,1,1,0,0,1,1,1,1,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,1,1,1,1,0,0,1,1,0,1,0,1,1,0,0,1,1,1,1,1,0,0,0,0,0,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,1,1,1,0,0,0,1,1,1,1,1,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,1,1,0,1,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,0,1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,0,1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,1,1,0,0,0,1,1,1,1,0,0,0,1,1,0,0,0,0,0,0,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,1,1,0,0,1,1,0,0,1,1,0,0,0,1,1,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,1,1,0,0,0,0,1,1,1,1,1,1,0,0,1,1,0,0,1,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0}
};

void showGameOverMessage() {
  for (int d = 0; d < sizeof(gameOverMessage[0]) - 7; d++) {
    for (int col = 0; col < 8; col++) {
      delay(messageSpeed); // this sets te speed of the message
      for (int row = 0; row < 8; row++) {
        lc.setLed(0, row, col, pgm_read_byte(&(gameOverMessage[row][col + d])));
      }
    }
  }
}


void setup() {
  pinMode(pinSW, INPUT_PULLUP);
  pinMode(pinX, INPUT);
  pinMode(pinY, INPUT);
  attachInterrupt(digitalPinToInterrupt(pinSW), restart, RISING);

  lcd.begin(16, 2);
  Serial.begin(9600);

  lc.shutdown(0, false);
  lc.setIntensity(0, 8);

  startGame();
  render();
}

void loop() {

  currentTimeLCD = millis();
  valueSW = digitalRead(pinSW);
  verPushButton();

  if (buttonState == 0) 
  {
    Menu();
    valueY = analogRead(pinY);
    if (valueY < minThreshold && joyMoved == true) 
    {
      lineCursor++;
      cursor();
      joyMoved = false;
    }

    if (valueY > maxThreshold && joyMoved == true) 
    {
      lineCursor--;
      cursor();
      joyMoved = false;
    }
    if (valueY >= minThreshold && valueY <= maxThreshold) 
    {
      joyMoved = true;
      cursor();
    }
  }
  else {
    if (lineCursor == 0) {
      if (!gameOver) {
        
        clearMatrix();
        render();
        if (currentTime - prevAdvance > advanceDelay) {
        gameOver = moveForward();
        prevAdvance = currentTime;
        }
        lcd.setCursor(0, 0);
        lcd.print("Lives:");
        lcd.print(lives);
        lcd.print(" Level:");
        lcd.print(level);
        lcd.setCursor(0, 1);
        lcd.print("Score: ");
        score = (length + level) * 3 - (6 + level * 3);
        lcd.print(score + PartHscore);
        lcd.print("       ");
        prevHscore = score + PartHscore;

        if (gameOver && lives != 0) {
          lives = lives - 1;

          PartHscore = PartHscore + score;
          restart();
        }
        if (lives == 0) {

          buttonState = 0;
          lives = 3;
          PartHscore = 0;
          Menu();
        }
      
        if (Hscore <= prevHscore) {
          
          Hscore = prevHscore;
          
        }
        
        if (prevHscore >= (48 + level * 2)) {
          
          lcd.setCursor(0, 0);
          lcd.print(" Good job, you  ");
          lcd.setCursor(0, 1);
          lcd.print("finished the lvl");
          
        }
      }
      else {
        // this while is used as a signal that the game is not running; however, it was usefulwhen the game didn't have a menu on the lcd
        while (blinkCount > 0) {
          clearMatrix();
          //delays used for the blinking effect
          delay(300);
          render();
          delay(300);
          blinkCount--;
        }
      }
      readControls();
      currentTime++;
    }
    else if (lineCursor == 1) 
    {
      lcd.setCursor(0, 1);
      lcd.print("                ");
      lcd.setCursor(0, 0);
      lcd.print("High Score: ");
      lcd.print(Hscore);
      lcd.print("  ");
    }
    else if (lineCursor == 2)
    {
      lcd.setCursor(0, 1);
      valueY = analogRead(pinY);
      if (valueY < minThreshold && joyMoved == true) 
      {
        level--;
        joyMoved = false;
      }

      if (valueY > maxThreshold && joyMoved == true) 
      {
        level++;
        joyMoved = false;
      }
      if (valueY >= minThreshold && valueY <= maxThreshold) 
      {
        joyMoved = true;
      }
      if (level < 1) level = 3;
      if (level > 3) level = 1;

      lcd.setCursor(0, 0);
      lcd.print("Start level: ");
      lcd.print(level);
      lcd.print("");
      lcd.setCursor(0, 1);
      lcd.print("Contrast:use POT");      
    }
    else {
      
      lcd.setCursor(0, 0);
      lcd.print("Snake. Creator  ");
      lcd.setCursor(0, 1);
      lcd.print("Andrei Costea   ");
      delay(2000); // delay used for printing multiple screens on the lcd
      lcd.setCursor(0, 0);
      lcd.print("Github:         ");
      lcd.setCursor(0, 1);
      lcd.print("github.com/cos99");
      delay(2000);
      buttonState = 0;
    }
  }

// thecode for snake is not 100% my creation, i used the almighty google to get some help :)
    
/*  
  original game; 
  if (!gameOver) {
    clearMatrix();
    render();

    if (currentTime - prevAdvance > advanceDelay) {
      gameOver = moveForward();
      prevAdvance = currentTime;

    }
  }
  
  else {
    while (blinkCount > 0) {
      clearMatrix();
      delay(300);
      render();
      delay(300);
      blinkCount--;
      
    }
  }

  
    readControls();
    currentTime++;
  */
}
