#define COST 10

void usage() {
  write("Usage: cast missle [-h] TARGET\n");
  write("Casts a magic missle at TARGET\n");
  write("This spell requires " + COST + " mana.\n");
  write("This spell does 1-5 damage to TARGET.\n");
  write("Options:\n");
  write("\t-h\tHelp, this usage message.\n");
}


