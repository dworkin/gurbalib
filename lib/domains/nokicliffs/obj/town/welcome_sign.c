#include "../../domain.h"

inherit "/std/sign";

private string get_sign_text(void) {
   return
      "       _______________________\n" +
      "     =(_______________________)=\n" +
      "       |                     |\n" +
      "       |      WELCOME TO     |\n" +
      "       |      NOKI TOWN      |\n" +
      "       |                     |\n" +
      "       |                     |\n" +
      "       |   Embrace all hope  |\n" +
      "       |     ye who enter    |\n" +
      "       |                     |\n" +
      "       |_____________________|\n" +
      "     =(______________________()=";
}

void setup(void) {
   set_short("A welcome sign");
   set_message(get_sign_text());
   set_long("It's a welcome sign. Perhaps you should read it.");
}
