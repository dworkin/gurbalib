inherit ob "/std/object";
inherit "/std/modules/m_wearable";

int armor_class;

void setup(void);

int is_armor(void) {
   return 1;
}

void set_ac(int ac) {
   armor_class = ac;
}

int query_ac(void) {
   return armor_class;
}

void create(void) {
   ob::create();
   add_ids("armor", "armour");
   set_gettable(1);
}
