#include "../domain.h"

inherit "/std/object";
inherit "/std/test";

string *p;

void setup() {
   string cmd;
   int experror;
   mixed expresult;

   set_id("testobject");
   set_adj("small");
   set_short("A testobject");

   cmd = "nilp(p);";
   expresult = 1;
   experror = 0;
   do_verbose_test(cmd,expresult, experror);
}
