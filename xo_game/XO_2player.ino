#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);

bool used[9] = {0};
char board[9] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};
char currentPlayer = 'X' ;

const int winPatterns [8][3] = {
  {0,1,2}, {3,4,5}, {6,7,8},
  {0,3,6}, {1,4,7}, {2,5,8},
  {0,4,8}, {2,4,6}
};

void drawBoard() {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("TIC TAC TOE");

  lcd.setCursor(0, 1);
  lcd.print(board[0]); lcd.print("|");
  lcd.print(board[1]); lcd.print("|");
  lcd.print(board[2]);

  lcd.setCursor(0, 2);
  lcd.print(board[3]); lcd.print("|");
  lcd.print(board[4]); lcd.print("|");
  lcd.print(board[5]);

  lcd.setCursor(0, 3);
  lcd.print(board[6]); lcd.print("|");
  lcd.print(board[7]); lcd.print("|");
  lcd.print(board[8]);
}

void blink(const char* msg, int n) {
  for (int i = 0; i < n; i++)
  {
    lcd.clear();
    lcd.setCursor(2,1);
    lcd.print(msg);
    delay(400);
    lcd.clear();
    delay(400);
  }
}

bool checkWin(char player) {
  for(int i = 0 ; i < 8; i++) {
    if (board[winPatterns[i][0]] == player &&
        board[winPatterns[i][1]] == player &&
        board[winPatterns[i][2]] == player)
      return true;
  }
  return false;
}

bool isDraw() {
  for(int i = 0; i < 9; i++)
    if(!used[i])  return false;
  return true;
}

void resetGame() {
  blink("NEW GAME", 2);

  for (int i = 0; i < 9; i++) {
    used[i] = false;
    board[i] = ' ';
  }

  currentPlayer = 'X';
  drawBoard();

  Serial.println("Game Reset!\nEnter move (0-8)");
}
void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();

  blink("Let's Play!" , 3);
  resetGame();
}

void loop() {

  if(Serial.available() > 0) {
    int place = Serial.parseInt();
    while (Serial.available()) Serial.read();

    if(place > 8 || place < 0) {
      Serial.println("Invalid placement");
      blink("INVALID MOVE" , 1);
      drawBoard();
      return;
    }

    if(used[place]) {
      Serial.println("Spot already used");
      blink("USED SPOT!" , 1);
      drawBoard();
      return;
    }

    used[place] = true;
    board[place] = currentPlayer;
    drawBoard();

    if(checkWin(currentPlayer)) {
      lcd.clear();
      lcd.setCursor(3, 1);
      lcd.print("PLAYER "); lcd.print(currentPlayer); lcd.print(" WINS!");

      Serial.print("Player ");  Serial.print(currentPlayer); Serial.println(" wins!");
      delay(2500);
      resetGame();
      return;
    }

    if(isDraw()) {
      lcd.clear();
      Serial.println("Draw game!");
      blink("DRAW!", 3);
      
      resetGame();
      return;
    }
    
    currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    drawBoard();

    Serial.print("Next player: ");
    Serial.println(currentPlayer);
  }
}
