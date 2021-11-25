void Gui() {
  background(255);
  
  if(flag == false) {
    set_bg();
    tint(255);
    image(Song[Song_index], 300, 150);
    //println(Song_index);
    image(choice, 100, 10);
    fill(0);
    textSize(100);
    text(Song_index + 1, 50, 100);
    text("BPM", 20, 200);
    text(Bpm[Song_index], 20, 300);
    text("Sec", 20, 400);
    text(Time[Song_index], 20, 500);
    thread("create_Note");
    index = 0; 
    Combo = 0;
    Perfect = 0;
    Miss = 0;
    MaxCombo = 0;
    player[Song_index].play();
    //println("Ok!");
  }
  else {
    if(player[Song_index].position() == player[Song_index].length()) {
      println("delay");
      delay(1000);
      set_bg();
      fill(0);
      textSize(50);
      text(Song_name[Song_index], 100, 100);
      text("MaxCombo", 200, 300);
      text(MaxCombo, 700, 300);
      text("Perfect", 200, 400);
      text(Perfect, 700, 400);
      text("Miss", 200, 500);
      text(Miss, 700, 500);
      text("Total", 200, 600);
      text(index, 700, 600);
      stop();
    }
    else {
    tint(255);
    image(Bang[Song_index / 2], 0, 0);
    tint(255, 50);
    image(background, 350, 0);
    music();
    if(Combo > MaxCombo)
        MaxCombo = Combo;
    }
  }
}

void set_bg() {
  if(Song_index < 2)
      background(160, 32, 240, 50);
    else if(Song_index < 4)
      background(3, 168, 158, 50);
    else if(Song_index < 6)
      background(255, 0, 255, 50);
}
