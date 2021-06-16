// Закоментувати це, якщо використовується Arduino IDE
#include <Arduino.h>

#include<GameBoy.h>
#include"Blocks.h"

GameBoy gb;
int rot = 1;
int x = 2,y=-1;
int speed = 200;
int acc = 1;
int score = 0;
int level = 0;




bool loss(){
  if (gb.checkBlockCollision(gb.block[rot], x, 0))
    return true;
  else
  return false;
}

void drawBlock(byte arr[4][4],int x,int y){ //Функція яка малює блок
  for(int i = 0;i < 4;i++){ 
    for(int j = 0;j < 4;j++){
      if(arr[j][i]==1){
        gb.drawPoint(x+i,y+j);
      }
    }
  } 
}



  void createBlock(int num){  //Створення блоків
    x = 2; y = -1;   //Координати появлення блоку
    rot = random(0, 4);  //Випадкове число для повороту блоків
    if (num == 0) gb.generateBlock(gb.block, I_Block_1, I_Block_2, I_Block_3, I_Block_4);
    if (num == 1) gb.generateBlock(gb.block, Z_Block_1, Z_Block_2, Z_Block_3, Z_Block_4);
    if (num == 2) gb.generateBlock(gb.block, S_Block_1, S_Block_2, S_Block_3, S_Block_4);
    if (num == 3) gb.generateBlock(gb.block, L_Block_1, L_Block_2, L_Block_3, L_Block_4);
    if (num == 4) gb.generateBlock(gb.block, J_Block_1, J_Block_2, J_Block_3, J_Block_4);
    if (num == 5) gb.generateBlock(gb.block, T_Block_1, T_Block_2, T_Block_3, T_Block_4);
    if (num == 6) gb.generateBlock(gb.block, O_Block_1, O_Block_2, O_Block_3, O_Block_4);
  }


void setup() {
  randomSeed(analogRead(0) + analogRead(5));
  gb.begin(0);
  createBlock(random(0,7));
  Serial.begin(9600);
  Serial.println(rot);
  Serial.println("test");
  //tone(4, 247, 1000);
}


void makeMove(){
  
  if(gb.getKey() == 4){
   if(!gb.checkBlockCollision(gb.block[rot], x - 1, y)){
    x--;
   }
  }

  if(gb.getKey() == 5){
   if(!gb.checkBlockCollision(gb.block[rot], x + 1, y)){
    x++;
   }
  }
  
  if (gb.getKey() == 1){
    if (!gb.checkBlockCollision(gb.block[rot + 1], x + 1, y))
    {
      if (rot == 3) rot = 0;
      else rot++;
    }
  }
  if(gb.getKey()==6){
    acc = 4;
  }
  else {
    acc = 1;
  }


}



void loop(){

  if (loss()){
    for (int i = 0; i < 8; i++){
      for (int i = 0; i < 16; i++){
        gb.wipePoint(i,j);
      }
    }
  }
  

  makeMove();

  /**
   * Перевірка на перешкоди внизу
   * чи блок може рухатись вниз
  */
  if(gb.checkBlockCollision(gb.block[rot], x, y+1)){
    Serial.println(rot);  
    gb.memBlock(gb.block[rot],x,y);

    int lines = gb.fullLine();
    if (lines != 0)
    {
      score += lines;
      level += lines;

    }
    if(level == 5){
    level = 0;
    acc++;
    gb.sound(SCORE);
    }
   

    createBlock(random(0,7));
    Serial.println(rot); 
  }
  else{
    y++;
  }



  gb.drawDisplay();   // Очистити дисплей
  drawBlock(gb.block[rot],x,y);
  delay(speed / acc);
}


