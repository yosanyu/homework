import ddf.minim.*;
import processing.serial.*;
Minim minim;
AudioPlayer [] player = new AudioPlayer [6];
PImage button;
PImage background;
PImage choice;
PImage [] Bang = new PImage [3]; // load bang bg photo
PImage [] Song = new PImage [6]; // load song photo
String [][] lines = new String [6][]; // two dimension array to save song's music score
String [] Bang_name = {"Roselia", "Raise a suilen", "Pastel Palettes"};
String [] Song_name = {"BRAVE JEWEL", "R", "RIOT", "UNSTOPPABLE", "Shuwarin Drea min", "Yura Yura Ring-Dong-Dance"};
int speed = 10; // down speed
int index; // which note
int Combo; // combo
int Perfect;
int Miss;
int MaxCombo;
int Song_index = 0; // choice song
int Bpm [] = {192, 188, 140, 170, 176, 172};
int Time [] = {92, 111, 120, 102, 104, 105};
boolean flag = false; // check start
char [] keyboard = {'A', 'S', 'D', 'F'};
Note [][] note;


void setup() {
  size(1024, 768);
  frameRate(30);
  initialization();
}

void draw() {
  Gui();
}

void create_Note() {
  note = new Note[6][]; // two dimension array to save song's music score
  note[Song_index] = new Note [lines[Song_index].length+1]; // note[Song_index][lines[Song_index].length + 1]
  //println(lines[Song_index].length+1);
  //println(Song_index);
  for(int i=0;i<lines[Song_index].length;i++) {// new note 
  //  println(i);
    note[Song_index][i] = new Note(i);
  }
}

void keyPressed() {
  char [] check = {'A', 'S', 'D', 'F', 'a', 's', 'd', 'f'};
  for(int i=0;i<8;i++)
    if (key == check[i] && index < lines[Song_index].length)
      note[Song_index][index].press_check();
  //println("index = " + index);
}

void mousePressed() {
  if (flag == false && mouseButton == LEFT) {
    flag = true;
    music_stop();
  }
  else if (flag == true && mouseButton == RIGHT) {
    flag = false;
    music_stop();
  }
}

void mouseWheel(MouseEvent event) {
  player[Song_index].pause();
  player[Song_index].rewind();
  if(flag == false) {
    float e = event.getCount();
    if(e < 0) {
      if(Song_index != 0)
        Song_index--;
    }
    else {
      if (Song_index < 5)
        Song_index++;
    }
  }
}

void music_stop() {
  player[Song_index].pause();
  player[Song_index].rewind();
}
