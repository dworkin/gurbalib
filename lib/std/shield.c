inherit ob "/std/object";
inherit wear "/std/modules/m_wieldable";
inherit "/std/armor";

void setup(void);

void create(void) {
   ob::create();
   wear::create();
   add_ids("shield");
}
