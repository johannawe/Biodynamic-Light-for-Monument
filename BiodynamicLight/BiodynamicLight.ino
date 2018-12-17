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

char* serial = "play"; 

//COLORS
uint32_t morning_2[] = {201,200, 1};

uint32_t meh[] = {0,0, 0};
uint32_t meh2[] = {200,200,200};


uint32_t early_morning[] = {72,75, 100};
uint32_t morning[] = {219,159, 128};
uint32_t day[] = {204,210, 221};
uint32_t day2[] = {227,230, 238};
//uint32_t afternoon[] = {211,154, 128};
uint32_t evening[] = {167,145, 108};
//uint32_t lateevening[] = {49,49, 22};
uint32_t lateevening[] = {249,0, 0};

uint32_t afternoon[] = {0,0, 228};



uint32_t curr_1[] = {1,1,1};
uint32_t curr_2[] = {1,1,1};
uint32_t curr_3[] = {1,1,1};
uint32_t curr_4[] = {1,1,1};


int vel = 1;

int time_of_day = 0;
int interval = 720;

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


void loop() {


  static boolean needPrompt=true;
  char* userInput;
  
  userInput= serialString();
  if (userInput!=NULL)
  {
    if(strcmp(userInput, "play") == 0 || strcmp(userInput, "stop") == 0){
      Serial.println(userInput);
      Serial.println();
      serial = userInput;
      Serial.println(serial);      
    }else{
      serial = "play";
      vel = atoi(userInput);
      Serial.println(vel);
       Serial.println(serial);
      }
  

  }

 

   if (strcmp(serial, "stop") == 0){

   
      
    }else if (strcmp(serial, "play") == 0){ 
     
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
  }
  
  
  
  for(uint8_t i = 0; i<30; i++){
   if (i < sec_1){
      strip.setPixelColor(i, curr_1[0],curr_1[1],curr_1[2]);
      secStrip.setPixelColor(i,  curr_2[0],curr_2[1],curr_2[2]);
    }else if (i < sec_2){
      strip.setPixelColor(i,  curr_3[0],curr_3[1],curr_3[2]);
      secStrip.setPixelColor(i,  curr_4[0],curr_4[1],curr_4[2]);
    }
    //strip2.setPixelColor(i,  0,0,255);
  }
  
  strip.show();
  secStrip.show();
  
  delay(1);
}


void fadeShit(){
     
    if (shit == 0){
       fade(curr_1, time_of_day, early_morning, morning);
       flackern(curr_2, time_of_day, meh,early_morning, morning, vel);
       fade(curr_3, time_of_day, early_morning, morning);
       fade(curr_4, time_of_day, early_morning, morning);
    }else if(shit == 1){
      fade(curr_1, time_of_day, morning, day);
      flackern(curr_2, time_of_day, meh,morning, day, vel);
      fade(curr_3, time_of_day, morning, day);
      fade(curr_4, time_of_day, morning, day);
    }else if(shit == 2){
      fade(curr_1, time_of_day, day, afternoon);
      flackern(curr_2, time_of_day, meh,day, afternoon, vel);
      fade(curr_3, time_of_day, day, afternoon);
      fade(curr_4, time_of_day, day, afternoon);
    }else if(shit == 3){
      fade(curr_1, time_of_day, afternoon, evening);
      flackern(curr_2, time_of_day, meh,afternoon, evening, vel);
      fade(curr_3, time_of_day, afternoon, evening);
      fade(curr_4, time_of_day, afternoon, evening);
    }else if(shit == 4){
      fade(curr_1, time_of_day, evening, lateevening);
      flackern(curr_2, time_of_day, meh,evening, lateevening, vel);
      fade(curr_3, time_of_day, evening, lateevening);
      fade(curr_4, time_of_day, evening, lateevening);
    }else if(shit == 5){
      fade(curr_1, time_of_day, lateevening, early_morning);
      flackern(curr_2, time_of_day, meh,lateevening, early_morning, vel);
      fade(curr_3, time_of_day, lateevening, early_morning);
      fade(curr_4, time_of_day, lateevening, early_morning);
    }
}

void fade(uint32_t curr[3], int val, uint32_t from[3], uint32_t to[3]){
    curr[0] = map(val, 0, interval, from[0], to[0]);
    curr[1] = map(val, 0, interval, from[1], to[1]);
    curr[2] = map(val, 0, interval, from[2], to[2]);
}

void flackern(uint32_t curr[3], int val, uint32_t darken[3], uint32_t from[3], uint32_t to[3],int velocity){
    curr[0] = map(sin((0.00869565217*velocity)*(val-180/velocity))*interval/2+interval/2, 0, interval,  darken[0], map(val, 0, interval, from[0], to[0]));
    curr[1] = map(sin((0.00869565217*velocity)*(val-180/velocity))*interval/2+interval/2, 0, interval,  darken[1], map(val, 0, interval, from[1], to[1]));
    curr[2] = map(sin((0.00869565217*velocity)*(val-180/velocity))*interval/2+interval/2, 0, interval,  darken[2], map(val, 0, interval, from[2], to[2]));
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
