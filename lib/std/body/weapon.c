/* Created by Fudge on Mon Mar  2 19:41:42 1998 */

static object *wielding;

void do_wield(object ob) {
   if (ob->query_wielded()) {
      return;
   }
   if (ob->query_wield_type() == "single") {
      if (sizeof(wielding) == 2) {
         return;
      } else {
         wielding += ( { ob } );
         ob->set_wielded(1);
      }
   } else {
      if (sizeof(wielding) != 0) {
         return;
      } else {
         wielding += ( { ob } );
         ob->set_wielded(1);
      }
   }
}

void do_unwield(object ob) {
   int i;

   for (i = 0; i < sizeof(wielding); i++) {
      if (wielding[i] == ob) {
         wielding -= ( { ob } );
         ob->set_wielded(0);
      }
   }
}

object *query_wielding(void) {
   return wielding;
}

object *query_wielded(void) {
   return wielding;
}

