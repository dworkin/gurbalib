static object *linkdead;

void add_linkdead(object ob) {
   if (!linkdead) {
      linkdead = ({ });
   }
   linkdead += ({ ob });
}

void remove_linkdead(object ob) {
   if (!linkdead) {
      linkdead = ({ });
      return;
   }
   linkdead -= ({ ob });
}

object *query_linkdead(void) {
   return linkdead;
}

int is_linkdead(object ob) {
   if (!linkdead) {
      linkdead = ({ });
   }
   if (member_array(ob, linkdead) > -1 ) {
      return 1;
   }
   return 0;
}
