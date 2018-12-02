
// setup intial black  for all strips

//set an output for every layer

// set fading points



// Output
int strip1Food[3] = {9,10,11}
int strip2Living[3] 
int strip3Lifestyle[3] 
int strip4Transport[3] 

String strips[4] = {"strip1Food", "strip2Living", "strip3Lifestyle", "strip4Transport"}

// Color arrays
int sunrise[3]  = { 255, 184, 125 };
int dayligt[3]  = { 202, 218, 255 };
int cloudy[3]  = { 229, 243, 255 };
int noon[3]    = { 255, 242, 230 };
//int evening[3]  = { 0, 100, 0 };
int night[3]   = { 83, 84, 107 };

int off[3]   = { 20, 20, 20 };

// Set initial color
int redVal = black[0];
int grnVal = black[1]; 
int bluVal = black[2];

int hold = 0;       // Optional hold when a color is complete, before the next crossFade
int repeat = 0;     // How many times should we loop before stopping? (0 for no stop)
int j = 0;          // Loop counter for repeat


int fadeAmount = 5;
int brightness = 0;

// Initialize color variables
//int prevR = redVal;
//int prevG = grnVal;
//int prevB = bluVal;

// Set up the LED outputs
void setup()
{
  pinMode(strip1Food[0], OUTPUT);   // sets the pins as output
  pinMode(strip1Food[1], OUTPUT);   
  pinMode(strip1Food[2], OUTPUT); 

  if (DEBUG) {           // If we want to see values for debugging...
    Serial.begin(9600);  // ...set up the serial ouput 
  }
}

// Main program: list the order of crossfades
void loop()
{
  crossFade(night, sunrise, strip1Food, 10);
  crossFade(sunrise, cloudy, strip1Food, 10);
  crossFade(cloudy, noon, strip1Food, 10);
  crossFade(noon, night, strip1Food, 10);

  if (repeat) { // Do we loop a finite number of times?
    j += 1;
    if (j >= repeat) { // Are we there yet?
      exit(j);         // If so, stop.
    }
  }
}





int calculateStep(int prevValue, int endValue) {
  int step = endValue - prevValue; // What's the overall gap?
  if (step) {                      // If its non-zero, 
    step = 1020/step;              //   divide by 1020
  } 
  return step;
}

int calculateVal(int step, int val, int i) {

  if ((step) && i % step == 0) { // If step is non-zero and its time to change a value,
    if (step > 0) {              //   increment the value if step is positive...
      val += 1;           
    } 
    else if (step < 0) {         //   ...or decrement it if step is negative
      val -= 1;
    } 
  }
  // Defensive driving: make sure val stays in the range 0-255
  if (val > 255) {
    val = 255;
  } 
  else if (val < 0) {
    val = 0;
  }
  return val;
}

void crossFade(int prvColor[3],int color[3],int strips[4], int wait) {


  int stepR = calculateStep(prvColor[0], color[0]);
  int stepG = calculateStep(prvColor[1], color[1]); 
  int stepB = calculateStep(prvColor[2], color[2]);

  for (int i = 0; i <= 1020; i++) {
    redVal = calculateVal(stepR, redVal, i);
    grnVal = calculateVal(stepG, grnVal, i);
    bluVal = calculateVal(stepB, bluVal, i);

    for (int ii = 0; int ii < 4; iipp){
      analogWrite(strip[ii][0], redVal);   // Write current values to LED pins
      analogWrite(strip[ii][1], grnVal);      
      analogWrite(strip[ii][2], bluVal);
    }
     

    delay(wait); // Pause for 'wait' milliseconds before resuming the loop

  }
  
  delay(hold); // Pause for optional 'wait' milliseconds before resuming the loop
}


void brightnessfade(int speed, int strip[3]) { //the higher the speed the slower
  crossfade(cloudy, off, strip, 10)
  crossfade(off, cloudy, strip, 10)
}
