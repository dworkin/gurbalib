#include "../domain.h"

inherit "/std/object";

int is_disabled;
string *affix_names;

int can_receive_affix(string affix_name) {
   return NOKICLIFFS_AFFIXES_OK;
}

int has_affixes(void) {
   if (!affix_names) {
      affix_names = ({ });
   }

   return sizeof(affix_names) > 0;
}

int has_affix(string affix_name) {
   return has_affixes() && member_array(affix_name, affix_names) > - 1;
}

void enable_affixes(void) {
   is_disabled = FALSE;
}

void disable_affixes(void) {
   is_disabled = TRUE;
}

int affix_effect(string affix_name) {
   return 1;
}

string query_long(void) {
   string str;
   int i, sz;

   if (is_disabled) {
      return "";
   }

   str = ::query_long();
   sz = sizeof(affix_names);
   if (sz) {
      str += "\nAffixed item" + (sz != 1 ? "s" : "") + ":";
      for (i = 0; i < sz; i++) {
         str += " '" + affix_names[i] + "'";
      }
   }

   return str;
}

void add_affix_side_effect(string affix_name) {

}

void remove_affix_side_effect(string affix_name) {

}

void remove_affix(string affix_name) {
   affix_names -= ({ affix_name });
   remove_affix_side_effect(affix_name);
}

void add_affix(string affix_name) {
   if (nilp(affix_names)) {
      affix_names = ({ });
   }
   affix_names += ({ affix_name });
   affix_names = uniq_array(affix_names);
   add_affix_side_effect(affix_name);
}

int affix_cmd(string str) {
   string what, on_what;

   if (is_disabled || empty_str(str) ||
         sscanf(str, "%s on %s", what, on_what) != 2) {
      return 0;
   }

   if (member_array(what, affix_names) > -1 &&
         this_object()->is_id(on_what) &&
         this_player()->present(on_what) == this_object()) {
      return affix_effect(what);
   }

   return 0;
}

void create(void) {
   ::create();

   affix_names = ({ });
   is_disabled = TRUE;

   add_action("affix_cmd", "touch");
}