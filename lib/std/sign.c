/* Created by Fudge */

inherit OBJECT;
inherit M_READABLE;

void create(void) {
   ::create();
   set_id("sign");
   set_long("Your average wooden sign.  It has some writing on it.");
   set_short("A wooden sign.");
   set_gettable(0);
}
