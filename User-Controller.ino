#include <Keypad.h>

const byte ROWS = 5;
const byte COLS = 4;

byte rowPins[ROWS] = {2,3,4,5,6};
byte colPins[COLS] = {10,9,8,7};

unsigned int antrianIndex = 0;

bool antrianStatus[500];

char specialKeysID[] = {'A',  'B', '#', '*','1',  '2', '3', 'C', '4', '5', '6', 'D', '7', '8', '9', 'E', 'F', '0', 'G', 'H'};
char keys[ROWS][COLS] = {
  {specialKeysID[0],  specialKeysID[1], specialKeysID[2], specialKeysID[3]},
  {specialKeysID[4],  specialKeysID[5], specialKeysID[6], specialKeysID[7]},
  {specialKeysID[8],  specialKeysID[9], specialKeysID[10], specialKeysID[11]},
  {specialKeysID[12],  specialKeysID[13], specialKeysID[14], specialKeysID[15]},
  {specialKeysID[16],  specialKeysID[17], specialKeysID[18], specialKeysID[19]}
};

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup() {
  Serial.begin(9600);
  for(unsigned int i = 0; i < 500; i++){
    antrianStatus[i] = false;
  }
  String tmp = String(antrianIndex);
  //Serial.print("Antrian No: ");
  Serial.write(tmp.c_str());
//  Serial.println("");
}

void loop(){
  char key = keypad.getKey();
  String command;
  if(key){
    if(key == specialKeysID[0]){
//      Serial.println("Masukkan No.");
      command = "";
      while(true){
        char key1 = keypad.getKey();
        if(key1){
          if(key1 != specialKeysID[0] && key1 != specialKeysID[1] && key1 != specialKeysID[2] && key1 != specialKeysID[3] && key1 != specialKeysID[7] && key1 != specialKeysID[11] && key1 != specialKeysID[15] && key1 != specialKeysID[16] && key1 != specialKeysID[18] && key1 != specialKeysID[19]){
            command += key1;
//          Serial.print("Command: ");
//          Serial.println(command);
          }else if(key1 == specialKeysID[19]){
            //Serial.print("Antrian No: ");
            antrianIndex = command.toInt();
            Serial.write(command.c_str());
//            Serial.println("");
            break;
          }
        }
      }
    }else if(key == specialKeysID[1]){
      antrianStatus[antrianIndex] = true;   //antrian selesai
      //Serial.print("Antrian No: ");
//      Serial.print(antrianIndex);
//      Serial.println(" Telah Selesai");
    }else if(key == specialKeysID[2]){      //reset
      for(unsigned int i = 0; i < 500; i++){
        antrianStatus[i] = false;
      }
      antrianIndex = 0;
      command = antrianIndex;
      Serial.write(command.c_str());
    }else if(key == specialKeysID[16]){     //recall antrian terdahulu
      unsigned int checker = 0;
      while(true){
        if(antrianStatus[checker] == false){
          antrianIndex = checker;
          command = String(antrianIndex);
          //Serial.print("Antrian No: ");
          Serial.write(command.c_str());
//          Serial.println("");
          break;
        }else{
          checker++;
        }
      }
    }else if(key == specialKeysID[18]){  // normal case
      while(true){
        antrianIndex++;
        if(antrianStatus[antrianIndex] == true){
          
        }else{
          command = antrianIndex;
          //Serial.print("Antrian No: ");
          Serial.write(command.c_str());
//          Serial.println("");
          break;
        }
      }
    }
  }
}
