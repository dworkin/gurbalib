#include "../../domain.h"

inherit "/std/sign";

private string get_sign_text(void) {
   return
      "       _______________________\n" +
      "     =(_______________________)=\n" +
      "       |                     |\n" +
      "       |      THANKS FOR     |\n" +
      "       |       VISITING      |\n" +
      "       |       NOKI TOWN     |\n" +
      "       |                     |\n" +
      "       |   Come again soon.  |\n" +
      "       |                     |\n" +
      "       |_____________________|\n" +
      "     =(______________________()=";
}

void setup(void) {
   set_short("A farewell sign");
   set_message(get_sign_text());
   set_long("It's a farewell sign. Perhaps you should read it.");
}
