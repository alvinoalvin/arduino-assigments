import controlP5.*; 
import processing.serial.*;

Serial port; 

ControlP5 cp5; 
PFont font;

void setup(){ 

  size(300, 450);    
  
  printArray(Serial.list());   //prints all available serial ports
  
  port = new Serial(this, "COM3", 9600);  //i have connected arduino to com3, it would be different in linux and mac os
  
  
  
  cp5 = new ControlP5(this);
  font = createFont("calibri light bold", 20);   
  
  // Red Btn
  cp5.addButton("red")     
    .setPosition(100, 50)  //x and y coordinates of upper left corner of button
    .setSize(120, 70)      
    .setFont(font)
  ;   

  // Yellow Btn
  cp5.addButton("yellow")    
    .setPosition(100, 150) 
    .setSize(120, 70)     
    .setFont(font)
  ;

  // Green Btn
  cp5.addButton("Green")     
    .setPosition(100, 250) 
    .setSize(120, 70)      
    .setFont(font)
  ;
  
  
  // Off Btn
  cp5.addButton("alloff")     
    .setPosition(100, 350) 
    .setSize(120, 70)     
    .setFont(font)
  ;
}

void draw(){  

  background(150, 0 , 150);
  
  // Title
  fill(0, 255, 0);               
  textFont(font);
  text("LED CONTROL", 80, 30);  // ("text", x coordinate, y coordinat)
}




void red(){
  port.write('r');
}

void yellow(){
  port.write('y');
}

void green(){
  port.write('g');
}

void alloff(){
  port.write('o');
}
