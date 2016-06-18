#include "../domain.h"

inherit "/std/object";
inherit "/sys/lib/modules/m_properties";

void create(void) {
   ::create();
   set_id("ancient relic");
   add_adj("ancient");
   set_weight(1);
   set_gettable(1);
   set_value(5 + random(5));
   set_short("An ancient relic");
   set_long("An ancient relic of the Ancient One.");
   set_property(ANCIENT_RELIC_PROP, 1);
}
