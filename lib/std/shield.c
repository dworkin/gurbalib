inherit ob "/std/object";
inherit wield "/std/modules/m_wieldable";
inherit "/std/armor";

void setup(void);

void create(void) {
   ob::create();
   wield::create();
   set_id("shield");
}
