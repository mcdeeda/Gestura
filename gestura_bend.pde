import processing.sound.*;
import processing.serial.*;

int counter = 0;
Serial currentPort;
String val;
String val2;
String valBend;
int[] prevVals = new int[10];
SqrOsc wave;
TriOsc wave2;
float valFloat = 0;
float valFloat2 = 0;
float valFloatBend = 0;
float[] valFloatBends = new float[10];
float currentAmps = 0;

void setup(){
  String portName = Serial.list()[3];
  currentPort = new Serial(this, portName, 9600);
  currentPort.bufferUntil('\n');
  wave = new SqrOsc(this);
  wave2 = new TriOsc(this);
  wave.amp(1);
  wave2.amp(1);
  val = "1";
  val2 = "1";
  valBend = "1";
  wave.play();
  wave2.play();
  for(int i = 0; i < 10; i++){
    valFloatBends[i] = 1000;
  }
}
void serialEvent(Serial cPort){
  try{
    if(counter == 0){
      valBend = cPort.readStringUntil('\n');
      if(valBend != null){
          valBend = trim(valBend);
      }
      valFloatBend = float(valBend);
      counter++;
      
      
    }
    else if(counter >= 1){
      val = cPort.readStringUntil('\n');
       if(val != null){
          val = trim(val);
        }
      valFloat = float(val);
      counter = 0;
    }
  }
  catch(RuntimeException e){
  
  }
  
}
void draw(){
   if(valFloatBend < 950){
       wave.freq(50 * (floor(valFloat / 200)));
       wave2.freq(100 * (floor(valFloat / 200)));
      
      currentAmps = Math.abs(1000 - valFloatBend);
      wave.amp(currentAmps);
      wave2.amp(currentAmps);
   }
   else{
     if(currentAmps <= 0.1){
       currentAmps = 0;
     }
     else{
       wave.amp(currentAmps - 0.1);
     }
     
   }
      
    
  
  
  println(valFloat);
  
}