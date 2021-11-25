void music() {
  player[Song_index].play();
   for(int i=index;i<lines[Song_index].length;i++) {
     note[Song_index][i].down(player[Song_index].position());
     note[Song_index][i].miss();
   }
  set();
}

void set() {
  fill(#FF3333);
  textSize(30);
  text("Combo", 10, 100);
  text(Combo, 200, 100);
  text("MaxCombo", 10, 200);
  text(MaxCombo, 200, 200);
  text("Miss", 10, 300);
  text(Miss, 200, 300);
  text("Index", 10, 400);
  text(index, 200, 400);
}
