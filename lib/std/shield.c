inherit ob "/std/object";
inherit wear M_WIELDABLE;
inherit ARMOR;

void setup(void);

void create(void) {
   ob::create();
   wear::create();
   add_ids("shield");
}
