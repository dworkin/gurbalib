inherit ob OBJECT;
inherit wear M_WEARABLE;
inherit M_GETTABLE;
inherit M_VALUABLE;

int armor_class;

void setup(void);

void create(void) {
   ob::create();
   wear::create();
   add_ids("armor", "armour");
}

int is_armor(void) {
   return (1);
}

void set_ac(int ac) {
   armor_class = ac;
}

int query_ac(void) {
   return (armor_class);
}
