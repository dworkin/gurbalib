#include "../domain.h"

inherit "/std/object";
inherit "/std/test";

string *p;

void setup() {
   string cmd;
   int experror;
   mixed expresult;
   mixed *args;

   set_id("testobject");
   set_adj("small");
   set_short("A testobject");

   cmd = "nilp;";
   expresult = 1;
   experror = 0;
   args = ({});
   args += ({p});
   do_verbose_test(expresult, experror, cmd, args);
}
