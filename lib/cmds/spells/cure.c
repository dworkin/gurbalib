#define COST 10

void usage() {
  write("Usage: cast cure [-h] TARGET\n");
  write("Casts cure light wounds on TARGET\n");
  write("This spell requires " + COST + " mana.\n");
  write("This spell heals 1-5 hit points on TARGET.\n");
  write("You need to have a certain skill level before " +
    "you can cast this spell on other players.\n");
  write("Options:\n");
  write("\t-h\tHelp, this usage message.\n");
}


