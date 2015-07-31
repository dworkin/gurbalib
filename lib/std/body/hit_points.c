int cur_hp, max_hp, cur_mana, max_mana, cur_end, max_end, is_dead;
static int performance_enhancement;

void set_performance_enhancement(int i) {
   if (i < 0) {
      i = 0;
   }
   performance_enhancement = i;
}

int get_performance_enhancement() {
   if (performance_enhancement < 0) {
      set_performance_enhancement(0);
   }
   return performance_enhancement;
}

int has_performance_enhancement() {
   if (performance_enhancement < 0) {
      set_performance_enhancement(0);
   }
   return performance_enhancement != 0;
}

void increase_hp(int hp) {
   if (cur_hp < max_hp) {
      cur_hp += hp;
      if (cur_hp >= max_hp) {  
         cur_hp = max_hp;
         this_object()->message("%^BLUE%^You are fully healed.%^RESET%^");
      }
   }
}

void increase_mana(int mana) {
   if (cur_mana < max_mana) {
      cur_mana += mana;
      if (cur_mana >= max_mana) {  
         cur_mana = max_mana;
      }
   }
}

void increase_end(int end) {
   if (cur_end < max_end) {
      cur_end += end;
      if (cur_end >= max_end) {  
         cur_end = max_end;
      }
   }
}

void decrease_hp(int hp) {
   cur_hp -= hp;
   if (cur_hp < 0) {
      cur_hp = 0;
   }
}

void decrease_mana(int mana) {
   cur_mana -= mana;
   if (cur_mana < 0) {
      cur_mana = 0;
   }
}

void decrease_end(int end) {
   cur_end -= end;
   if (cur_end < 0) {
      cur_end = 0;
   }
}

void decrease_performance_enhancement(int i) {
   performance_enhancement -= i;
   if (performance_enhancement < 0) {
      performance_enhancement = 0;
   }
}

void set_max_hp(int hp) {
   max_hp = hp;
}

void set_max_mana(int mana) {
   max_mana = mana;
}

void set_max_end(int end) {
   max_end = end;
}

void set_hp(int hp) {
   if (hp > max_hp) {
      hp = max_hp;
   }
   cur_hp = hp;
}

void set_mana(int mana) {
   if (mana > max_mana) {
      mana = max_mana;
   }
   cur_mana = mana;
}

void set_end(int end) {
   if (end > max_end) {
      end = max_end;
   }
   cur_end = end;
}

int query_max_hp(void) {
   return max_hp;
}

int query_max_mana(void) {
   return max_mana;
}

int query_max_end(void) {
   return max_end;
}

int query_hp(void) {
   return cur_hp;
}

int query_mana(void) {
   return cur_mana;
}

int query_end(void) {
   return cur_end;
}

string query_status(void) {
   int x, max, t;

   max = this_object()->query_max_hp();
   x = this_object()->query_hp();

   if (x >= max) {
      return "in peak physical condition.";
   } else if (x == 0) {
      return "dead as a door nail.";
   } else if (max < 5) {
      if (x < (max / 2)) {
         return "knocking on deaths door.";
      }
      return "wounded.";
   } else {
      t = max / 5;
      x = x / t;

      switch (x) {
         case 5:
            return "in peak physical condition.";
            break;
         case 4:
            return "barely scratched.";
            break;
         case 3:
            return "lightly wounded.";
            break;
         case 2:
            return "wounded.";
            break;
         case 1:
            return "is in really bad shape.";
            break;
         default:
            return "knocking on deaths door.";
            break;
      }
   }
}

void set_dead(int x) {
   is_dead = x;
}

int is_dead(void) {
   if (is_dead == 0) {
      return 0;
   }
   return 1;
}

int is_alive(void) {
   if (is_dead()) {
      return 0;
   }
   return 1;
}

void create(void) {
   cur_hp = 1;
   max_hp = 1;
   cur_mana = 1;
   max_mana = 1;
   cur_end = 1;
   max_end = 1;
}

