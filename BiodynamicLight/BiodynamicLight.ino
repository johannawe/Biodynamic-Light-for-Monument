#include <Adafruit_NeoPixel.h>

/*
TODO 

fix color scheme
fix color timing interpolation
make at least on section functional
  fade mode
  fade speed (maybe some steps)

*/


#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif


#define PIN 5
#define secPIN 6



Adafruit_NeoPixel strip = Adafruit_NeoPixel(30, PIN , NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel secStrip = Adafruit_NeoPixel(30, secPIN, NEO_GRB + NEO_KHZ800);

uint8_t sec_1 = 15;
uint8_t sec_2 = 30;

uint8_t sec_3 = 15;
uint8_t sec_4 = 30;

char* serial = 'n'; 

//COLORS
uint32_t morning_2[] = {201,200, 1};
uint32_t meh[] = {0,0, 0};


uint32_t early_morning[] = {72,75, 100};
uint32_t morning[] = {219,159, 128};
uint32_t day[] = {204,210, 221};
uint32_t day2[] = {227,230, 238};
uint32_t afternoon[] = {211,154, 128};
uint32_t evening[] = {167,145, 108};
uint32_t lateevening[] = {49,49, 22};





uint32_t curr_1[] = {1,1,1};
uint32_t curr_2[] = {1,1,1};
uint32_t curr_3[] = {1,1,1};
uint32_t curr_4[] = {1,1,1};


int serialval;
int shit = 0;
char* serialString()
{
  static char str[21]; // For strings of max length=20
  if (!Serial.available()) return NULL;

  delay(64); // wait for all characters to arrive
  memset(str,0,sizeof(str)); // clear str
  byte count=0;
  while (Serial.available())
  {
   /* 
     serialval = Serial.parseInt(); //read int or parseFloat for ..float...
      Serial.println(serialval);
   
   
    */
    char c=Serial.read();
    if (c>=32 && count<sizeof(str)-1)
    {
      str[count]=c;
      count++;
    }
  }
  str[count]='\0'; // make it a zero terminated string
  return str;
}





void setup() {

  Serial.begin(9600);
  // put your setup code here, to run once:
   #if defined (__AVR_ATtiny85__)
      if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
   #endif

  
  strip.begin();
  secStrip.begin();
  for(uint8_t i = 0; i<60; i++){
    if (i < sec_4){
      strip.setPixelColor(i, morning[0], morning[1],morning[2]);
       secStrip.setPixelColor(i, morning[0], morning[1],morning[2]);
    }
  }
  
  strip.show();
  secStrip.show();// Initialize all pixels to 'off'
}


int time_of_day = 0;
int interval = 720;


void loop() {


  static boolean needPrompt=true;
  char* userInput;
  
  userInput= serialString();
  if (userInput!=NULL)
  {
    Serial.println(userInput);
    Serial.println();
    serial = userInput;
  }

 


  
  if(time_of_day < interval){
    fadeShit();
    //setCurrentColor();
    time_of_day = time_of_day + 1;
  
  }else{
    time_of_day = 0;
    if (shit < 5){
      shit = shit + 1;  
    }else{
      shit = 0;
    }
    
  }
  
  for(uint8_t i = 0; i<30; i++){
   if (i < sec_1){
      strip.setPixelColor(i, curr_1[0],curr_1[1],curr_1[2]);
      secStrip.setPixelColor(i,  curr_2[0],curr_2[1],curr_2[2]);
    }else if (i < sec_2){
      strip.setPixelColor(i,  curr_3[0],curr_3[1],curr_3[2]);
      secStrip.setPixelColor(i,  curr_4[0],curr_4[1],curr_4[2]);
    }
    if (i < sec_3){
      
    }else if (i < sec_4){
    
    }
    //strip2.setPixelColor(i,  0,0,255);
  }
  
  strip.show();
  secStrip.show();
  
  delay(1);
}



// onchange (serial != old serial )
  // fade from CURR color to SET color 
    //(if SERAIL == VAR" -> SET == Col)
  // else 
  // do nothing

// if critical 
   // flackern
// else 
  // dont 

/*

void setColor(oldCol, newCol){
  if(strcmp(serial[0], oldserial[0]) == 0){
      if (strcmp(serial[0], 'earlymorning') == 0){
        fadeTo();
      }else if(strcmp(serial[0], 'morning') == 0){
    
      }  //…
   
  }
}

*/


void fadeShit(){
     
    if (shit == 0){
       fade(curr_1, time_of_day, early_morning, morning);
       flackern(curr_2, time_of_day, early_morning, meh);
       fade(curr_3, time_of_day, early_morning, morning);
       fade(curr_4, time_of_day, early_morning, morning);
    }else if(shit == 1){
      fade(curr_1, time_of_day, morning, day);
      flackern(curr_2, time_of_day, early_morning, meh);
      fade(curr_3, time_of_day, morning, day);
      fade(curr_4, time_of_day, morning, day);
    }else if(shit == 2){
      fade(curr_1, time_of_day, day, afternoon);
      flackern(curr_2, time_of_day, early_morning, meh);
      fade(curr_3, time_of_day, day, afternoon);
      fade(curr_4, time_of_day, day, afternoon);
    }else if(shit == 3){
      fade(curr_1, time_of_day, afternoon, evening);
      flackern(curr_2, time_of_day, early_morning, meh);
      fade(curr_3, time_of_day, afternoon, evening);
      fade(curr_4, time_of_day, afternoon, evening);
    }else if(shit == 4){
      fade(curr_1, time_of_day, evening, lateevening);
      flackern(curr_2, time_of_day, early_morning, meh);
      fade(curr_3, time_of_day, evening, lateevening);
      fade(curr_4, time_of_day, evening, lateevening);
    }else if(shit == 5){
      fade(curr_1, time_of_day, lateevening, early_morning);
      flackern(curr_2, time_of_day, early_morning, meh);
      fade(curr_3, time_of_day, lateevening, early_morning);
      fade(curr_4, time_of_day, lateevening, early_morning);
    }
}

void fade(uint32_t curr[3], int val, uint32_t from[3], uint32_t to[3]){
    curr[0] = map(val, 0, interval, from[0], to[0]);
    curr[1] = map(val, 0, interval, from[1], to[1]);
    curr[2] = map(val, 0, interval, from[2], to[2]);
}

/*
void flackern(uint32_t curr[3], int val, uint32_t from[3], uint32_t to[3]){
    curr[0] = sin(4.7+0.0087*map(val, 0, 1440,  from[0], to[0]))*720 +720;
    curr[1] = sin(4.7+0.0087*map(val, 0, 1440,  from[1], to[1]))*720+720;
    curr[2] = sin(4.7+0.0087*map(val, 0, 1440,  from[2], to[2]))*720+720;
}*/

void flackern(uint32_t curr[3], int val, uint32_t from[3], uint32_t to[3]){
    curr[0] = map(sin((0.0625)*val)*720 +720, 0, interval,  from[0], to[0]);
    curr[1] = map(sin((0.0625)*val)*720 +720, 0, interval,  from[1], to[1]);
    curr[2] = map(sin((0.0625)*val)*720 +720, 0, interval,  from[2], to[2]);
}

int fuckyou = 0.02;
void flackern2(uint32_t curr[3], int val, uint32_t from[3], uint32_t to[3]){
    curr[0] = map(sin(0.03125*val)*720 +720, 0, interval,  from[0], to[0]);
    curr[1] = map(sin(0.03125*val)*720 +720, 0, interval,  from[1], to[1]);
    curr[2] = map(sin(0.03125*val)*720 +720, 0, interval,  from[2], to[2]);
}

void flackern3(uint32_t curr[3], int val, uint32_t from[3], uint32_t to[3]){
    curr[0] = map(sin(0.0078125*val)*720 +720, 0, interval,  from[0], to[0]);
    curr[1] = map(sin(0.0078125*val)*720 +720, 0, interval,  from[1], to[1]);
    curr[2] = map(sin(0.0078125*val)*720 +720, 0, interval,  from[2], to[2]);
}





/*

void setCurrentColor(){
  //get current color
  //Serial.println(serial);
  // get end Color
  if(time_of_day >= 0 && time_of_day <= 720){
    if (strcmp(serial[0], 'n') == 0 && strlen(serial) == 1){
      fade(curr_1, time_of_day, morning_2, day);
    }else if(strcmp(serial[0], 'a') == 0 && strlen(serial) == 1){
      flackern(curr_1, time_of_day, morning_2, day);
    }else if(strcmp(serial[0], 'b') == 0 && strlen(serial) == 1){
      flackern2(curr_1, time_of_day, morning_2, day);
    }else if(strcmp(serial[0], 'c') == 0 && strlen(serial) == 1){
      flackern3(curr_1, time_of_day, morning_2, day);
    }
    //flackern2(curr_1, time_of_day, morning_2, day);
    //fade(curr_1, time_of_day, morning_2, day);
    fade(curr_2, time_of_day, morning_2, day);
    //fade(curr_3, time_of_day, morning_2, day);


    
    
    fade(curr_3, time_of_day, morning_2, morning_2);
    
    if (strcmp(serial[0], 'n') == 0 && strlen(serial) == 1){
      fade(curr_4, time_of_day, day, morning_2);
    }else if(strcmp(serial[0], 'a') == 0 && strlen(serial) == 1){
      flackern(curr_4, time_of_day, day, morning_2);
    }else if(strcmp(serial[0], 'b') == 0 && strlen(serial) == 1){
      flackern2(curr_4, time_of_day, day, morning_2);
    }else if(strcmp(serial[0], 'c') == 0 && strlen(serial) == 1){
      flackern3(curr_4, time_of_day, day, morning_2);
    }
    
  }else if(time_of_day > 720 && time_of_day < 1440)  {
    
    if (strcmp(serial[0], 'n') == 0 && strlen(serial) == 1){
      fade(curr_1, (1440-time_of_day), morning_2, day);
    }else if(strcmp(serial[0], 'a') == 0 && strlen(serial) == 1){
      flackern(curr_1, (1440-time_of_day), morning_2, day);
    }else if(strcmp(serial[0], 'b') == 0 && strlen(serial) == 1){
      flackern2(curr_1, (1440-time_of_day), morning_2, day);
    }else if(strcmp(serial[0], 'c') == 0 && strlen(serial) == 1){
      flackern3(curr_1, (1440-time_of_day), morning_2, day);
    }
    //flackern2(curr_1, (1440-time_of_day), morning_2, day);
    //fade(curr_1, (1440-time_of_day), morning_2, day);
    fade(curr_2, (1440-time_of_day), morning_2, day);
     fade(curr_3, time_of_day, morning_2, morning_2);
    //fade(curr_3, (1440-time_of_day), morning_2, day);
        if (strcmp(serial[0], 'n') == 0 && strlen(serial) == 1){
      fade(curr_4, (1440-time_of_day), day, morning_2);
    }else if(strcmp(serial[0], 'a') == 0 && strlen(serial) == 1){
      flackern(curr_4, (1440-time_of_day), day, morning_2);
    }else if(strcmp(serial[0], 'b') == 0 && strlen(serial) == 1){
      flackern2(curr_4, (1440-time_of_day), day, morning_2);
    }else if(strcmp(serial[0], 'c') == 0 && strlen(serial) == 1){
      flackern3(curr_4, (1440-time_of_day), day, morning_2);
    }
  }
  
}



*/



/*
void setup() {
  Serial.begin(9600);
}

void loop() 
{
  static boolean needPrompt=true;
  char* userInput;
  if (needPrompt)
  {
    Serial.print("Please enter inputs and press enter at the end:\n");
    needPrompt=false;
  }
  userInput= serialString();
  if (userInput!=NULL)
  {
    Serial.print("You entered: ");
    Serial.println(userInput);
    Serial.println();
    needPrompt=true;
  }
}
*/



//
//
//void fade(uint8_t start_sec,uint8_t end_sec, ){
//  uint32_t start_col =  strip.getPixelColor(start_sec); //get color
//  uint32_t new_col =  strip.getPixelColor(start_sec);
//  for(uint8_t i = start_sec; i<end_sec; i++){
//    strip.setPixelColor(i, morning);
//  }
//
//}


//strip.show() -> push data to leds
// strip.setPixelColor(ledID, r, g, b) — or (ledID,r,g,b,w) – or (led, col) -> set the data (is not pushing yet)
//uint32_t col = strip.Color(0,0,0) -> set a color to variable, can be passed instead of r,g,b
// uint32_t col = strip.getPixelColor(ledID) -> get set color from data 
// strop.setBrightness(val) -> 0-255 set brightness data only
// uint16_t n = strip.numPixels() -> get Number of declared Pixels in LED strip
