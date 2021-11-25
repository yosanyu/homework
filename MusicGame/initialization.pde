void initialization() {
  minim = new Minim(this);
  button = loadImage("button.png");
  background = loadImage("background.png");
  choice = loadImage("choice.png");
  for(int i=0;i<3;i++)
    Bang[i] = loadImage(Bang_name[i] + ".png");
  for(int i=0;i<6;i++) {
    Song[i] = loadImage(Song_name[i] + ".png");
    player[i] = minim.loadFile(Song_name[i] + ".mp3");
    lines[i] = loadStrings(Song_name[i] + ".txt");
    //println("ok");
  }
}
