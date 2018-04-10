
#include <Adafruit_NeoPixel.h>

#define PIN 13 //LED strip
#define NUM_LEDS 30
#define COLUMNS 6
#define ROWS 5

int led_array[ROWS][COLUMNS];
bool cont = true;
int currPlayer = 0;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(9600);
  
  strip.begin();
  strip.show();
  
  randomSeed(analogRead(0)); //seed rand with pin 0(random)
  
  //initialize matrix to 0s
  for(int i = 0; i < ROWS; ++i){
    for(int j = 0; j < COLUMNS; ++j){
      led_array[i][j] = 0;
    }
  }
  
}
void printBoard(){//For debugging
  Serial.println();
  Serial.print("---------------------------------------------------");
  Serial.println();
  for(int i = ROWS-1; i >= 0; --i){
      Serial.print(" |   ");
      for(int j = 0; j < COLUMNS; ++j){
       Serial.print(led_array[i][j]);
       Serial.print(" |   ");
      }
  Serial.println();
  Serial.print("---------------------------------------------------");
  Serial.println();
  }
}

void winHoriz(int r, int c, int p){
  if(c == 0){
    flashWin(0+r, 9-r, 10+r, 19-r, p);
  }
  else if(c == 1){
    flashWin(9-r, 10+r, 19-r, 20+r, p);
  }
  else if(c == 2){
    flashWin(10+r, 19-r, 20+r, 29-r, p);
  }
}

void winVert(int r, int c, int p){
  if(c == 0){
    flashWin(0+r, 1+r, 2+r, 3+r, p);
  }
  else if(c == 1){
    flashWin(9-r, 8-r, 7-r, 6-r, p);
  }
  else if(c == 2){
    flashWin(10+r, 11+r, 12+r, 13+r, p);
  }
  else if(c == 3){
    flashWin(19-r, 18-r, 17-r, 16-r, p);
  }
  else if(c == 4){
    flashWin(20+r, 21+r, 22+r, 23+r, p);
  }
  else if(c == 5){
    flashWin(29-r, 28-r, 27-r, 26-r, p);
  }
}

void winDiagNE(int r, int c, int p){
    if(c == 0){
      flashWin(0+r, 8-r, 12+r, 16-r, p);
    }
    else if(c == 1){
      flashWin(9-r, 11+r, 17-r, 23+r, p);
    }
    else if(c == 2){
      flashWin(10+r, 18-r, 22+r, 26-r, p);
    }
}

void winDiagNW(int r, int c, int p){
    if(c == 3){
      flashWin(19-r, 11+r, 7-r, 3+r, p);
    }
    else if(c == 4){
      flashWin(20+r, 18-r, 12+r, 6-r, p);
    }
    else if(c == 5){
      flashWin(29-r, 21+r, 17-r, 13+r, p);
    }
}

void setPlayerMove(int playerNum, int column){//Sets move in the matrix
  if(playerNum == 1){
    for(int i = 0; i < ROWS; ++i){//Sets a 1 in the array if position is not taken
      if(led_array[i][column] == 0){
        led_array[i][column] = 1;
        break;
      }
    }
  }
  else if(playerNum == 2){//Sets a 2 in the array if position is not taken
    for(int i = 0; i < ROWS; ++i){
      if(led_array[i][column] == 0){
        led_array[i][column] = 2;
        break;
      }
    }
  }
  else{
    
  }
}
int checkNE(int c_row, int c_col){
  int countP1 = 0;
  int countP2 = 0;
  
  for(int i = 0; i < 4; ++i){
    if(led_array[c_row+i][c_col+i] == 1){
      countP1 = countP1 + 1;
    }
    else if(led_array[c_row+i][c_col+i] == 2){
      countP2 = countP2 + 1;
    }
  }
  
  if(countP1 == 4){
    return 1;
  }
  else if(countP2 == 4){
    return 2;
  }
  
  return 0;
}

int checkNW(int c_row, int c_col){
  int countP1 = 0;
  int countP2 = 0;
  
  for(int i = 0; i < 4; ++i){
    if(led_array[c_row+i][c_col-i] == 1){
      countP1 = countP1 + 1;
    }
    else if(led_array[c_row+i][c_col-i] == 2){
      countP2 = countP2 + 1;
    }
  }
  
  if(countP1 == 4){
    return 1;
  }
  else if(countP2 == 4){
    return 2;
  }
  
  
  return 0;
}

bool checkWin(int p_num){//Checks board for a win
    //check horizontal
    for(int i = 0; i < ROWS; ++i){
      for(int j = 0; j < 3; ++j){
        if(led_array[i][0+j] == led_array[i][1+j] && led_array[i][1+j] == led_array[i][2+j] && led_array[i][2+j] == led_array[i][3+j]){
          if(led_array[i][0+j] != 0){
              winHoriz(i, 0+j, p_num);
              return true;
          }
        }
      }
    }
    
    //check vertical
    for(int i = 0; i < COLUMNS; ++i){
      for(int j = 0; j < 2; ++j){
        if(led_array[j+0][i] == led_array[j+1][i] && led_array[j+1][i] == led_array[j+2][i] && led_array[j+2][i] == led_array[j+3][i]){
          if(led_array[j+0][i] != 0){
              winVert(j+0, i, p_num);
              return true;
          }
        }
      }
    }
    
    //check diagonal
    for(int i = 0; i < 2; ++i){
      for(int j = 0; j < COLUMNS; ++j){
        if(j < 3){//check NE
          int check = checkNE(i, j);
          if(check != 0){
              winDiagNE(i, j, p_num);
              return true;
          }
        }
        else{//check NW
          int check = checkNW(i, j);
          if(check != 0){
              winDiagNW(i, j, p_num);
              return true;
          }
        }
      }
    }
    return false;
}

int getUpper(int column){
  switch(column){
    case 0:
      return 4;
    case 1:
      return 5;
    case 2:
      return 14;
    case 3:
      return 15;
    case 4:
      return 24;
    case 5:
      return 25;
    default:
      break; 
  }
  return -1;
}

int getLower(int column){
  switch(column){
    case 0:
      return 0;
    case 1:
      return 9;
    case 2:
      return 10;
    case 3:
      return 19;
    case 4:
      return 20;
    case 5:
      return 29;
    default:
      break; 
  }
  return -1;
}

void placeMarker(int player, int col){
  int r;
  int g;
  int b;
  
  if(player == 1){
    r = 255;
    g = 0;
    b = 0;
  }else{
    r = 0;
    g = 0;
    b = 255;
  }

  for(int i = 0; i < ROWS; ++i){
    if(led_array[i][col] == 0){
      led_array[i][col] = player;
      break;
    }
  }

  for(int j = ROWS-1; j >= 0; --j){
    if(!led_array[j][col] == 1 || !led_array[j][col] == 2){
      if(col == 1 || col == 3 || col == 5){//Increasing 
        strip.setPixelColor((col*ROWS + ROWS-1) - j, r, g, b);
        strip.show();
        delay(300);
        strip.setPixelColor((col*ROWS + ROWS-1) - j, 0, 0, 0);
        strip.show();
      }
      else{//decreasing, 0 2 4
        strip.setPixelColor((col*ROWS) + j, r, g, b);
        strip.show();
        delay(300);
        strip.setPixelColor((col*ROWS) + j, 0, 0, 0);
        strip.show();
      }
      
    }
    else if(led_array[j][col] == player){
      if(col == 1 || col == 3 || col == 5){//Increasing 
        strip.setPixelColor((col*ROWS + ROWS-1) - j, r, g, b);
        strip.show();
      }
      else{
        strip.setPixelColor((col*ROWS) + j, r, g, b);
        strip.show();
      }
    }
  }
}
void resetStrip(){//Sets strip to off
  for(int i = 0; i < NUM_LEDS; ++i){
    strip.setPixelColor(i, 0, 0, 0);
    strip.show();
  }
}

int randPos(){//for testing purposes
  return random(0, 6);
}

int randPlayer(){//for testing purposes
  return random(1, 3);
}

void flashWin(int one, int two, int three, int four, int player){
  int r;
  int g;
  int b;
  if(player == 1){
    r = 255;
    g = 0;
    b = 0;
  }
  else{
    r = 0;
    g = 0;
    b = 255;
  }
  
  for(int i = 0; i < 6; ++i){
    strip.setPixelColor(one, r, g, b);
    strip.setPixelColor(two, r, g, b);
    strip.setPixelColor(three, r, g, b);
    strip.setPixelColor(four, r, g, b);
    strip.show();
    delay(500);
    strip.setPixelColor(one, 0, 0, 0);
    strip.setPixelColor(two, 0, 0, 0);
    strip.setPixelColor(three, 0, 0, 0);
    strip.setPixelColor(four, 0, 0, 0);
    strip.show();
    delay(500);
    
    
  }
  resetStrip();
}

void loop() {
  if(cont){
    bool win = checkWin(currPlayer);
    printBoard();
    if(win == true){
      //flashWin();
      delay(5000);
      cont = false;
    }
    else{
      Serial.print("Player: ");
      Serial.println();
      Serial.print("Column: ");
      Serial.println();
      //if(Serial.read() >= 0){
        char inputPlayer = Serial.read();
        
        char inputPosition = Serial.read();
        
        delay(3000);
        currPlayer = randPlayer();
        placeMarker(currPlayer, randPos());
        //placeMarker(inputPlayer - '0', inputPosition - '0');
        delay(1000);
      //}
      
    }
    
  }
  else if(!cont){//Only way to stop program with win condition
    resetStrip();
    while(1){ 
      //button hold down = cont => true
      }
  }
  
}


//Function for win flash

