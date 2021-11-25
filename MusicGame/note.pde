class Note {
  int point_y;
  char dir;
  float time;
  
  Note(int i) {
    point_y = 0;
    String[] list = split(lines[Song_index][i], " ");
   // println(lines[Song_index].length);
    dir = list[0].charAt(0);
    time = float(list[1]) * 1000;
   // println("dir = " + dir);
   // println("time = " + time);
  }
  void down(int ms) {
    if(ms >= time) {
      tint(255);
      for(int i=0;i<4;i++)
        if(dir == keyboard[i] && point_y <= 680)
          image(button, 53 + (i + 3) * 100, point_y);
      point_y += speed;
      //miss();
    }
  }
  
  void press_check() {
    if(abs(int(point_y - 700)) <= 50) {
      for(int i=0;i<4;i++)
        if(dir == keyboard[i])
          text("Perfect", 51 + (i + 3) * 100 - 10, 740);
      point_y = 1000;
      Perfect++;
      index++;
      Combo++;
    }
  }
  
  void miss() {
    if(point_y > 700 && point_y < 1000 ) {
      for(int i=0;i<4;i++)
        if(dir == keyboard[i])
          text("Miss", 51 + (i + 3) * 100, 740);
      index++;
      Combo = 0;
      Miss++;
      point_y = 1000;
      println("index = " + index + " miss = " + Miss);
      }
    }
}
 
