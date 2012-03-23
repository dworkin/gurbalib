static int cursed;
inherit "/std/modules/m_undroppable";

int is_cursed(void) {
   return cursed;
}

void set_cursed(int curse) {
   cursed = curse;
   if (curse == 1) {
      set_undroppable(1);
   } else {
      set_undroppable(0);
   }
}
