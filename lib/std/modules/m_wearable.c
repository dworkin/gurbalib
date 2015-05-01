static string slot;
static int worn;
static string wear_message;
static string remove_message;

/* return 1 to allow this to be worn by player. */
int wear_hook(object player) {
   return 1;
}

void after_wear(object player) {
}

void after_unwear(object player, string cmd) {
}

void set_wear_message(string str) {
   wear_message = str;
}

string query_wear_message(void) {
   if (!wear_message) {
      return "$N $vwear $o.";
   }
   return wear_message;
}

void set_remove_message(string str) {
   remove_message = str;
}

string query_remove_message(void) {
   if (!remove_message) {
      return "$N $vremove $o.";
   }
   return remove_message;
}

int is_wearable(void) {
   return 1;
}

void set_worn(int state) {
   worn = state;
}

int query_worn(void) {
   return worn;
}

int is_worn(void) {
   return worn;
}

string query_slot(void) {
   if (!slot) {
      return "";
   }
   return slot;
}

int query_valid_slot(string str) {
   str = lowercase(str);

   switch (str) {
      case "torso":
      case "head":
      case "hands":
      case "feet":
      case "arm":
      case "neck":
      case "body":
      case "legs":
      case "waist":
      case "finger":
      case "apparel":
         return 1;
         break;
      default:
         break;
   }

   return 0;
}

void set_slot(string str) {
   str = lowercase(str);

   switch (str) {
      case "torso":
      case "head":
      case "hands":
      case "feet":
      case "arm":
      case "neck":
      case "body":
      case "legs":
      case "waist":
      case "finger":
      case "apparel":
         break;
      default:
         if (this_player()) {
            write("Illegal bodyslot.\n");
         }
         return;
         break;
   }
   slot = str;
}

string query_wear_position(void) {
   if (!slot) {
      return "somewhere";
   }

   switch (slot) {
      case "torso":
         return "on the upper body";
      case "head":
         return "on head";
      case "hands":
         return "on hands";
      case "finger":
         return "on one finger";
      case "feet":
         return "on feet";
      case "arm":
         return "on an arm";
      case "neck":
         return "about the neck";
      case "body":
         return "about the body";
      case "legs":
         return "on the lower body";
      case "waist":
         return "about the waist";
      default:
         return "somewhere";
   }
}
