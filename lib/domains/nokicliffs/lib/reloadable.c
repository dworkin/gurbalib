int max_charges;
int charges;

int is_reloadable() {
   return 1;
}

void after_reload_hook(int reload_amount) {
}

private int fix_charges(int i) {
   if (i > max_charges) {
      i = max_charges;
   }
   if (i < 0) {
      i = 0;
   }
   return i;
}

void reload(int i) {
   i = fix_charges(charges + i);
   charges = i;
   after_reload_hook(i);
}

int query_max_charges() {
   return max_charges;
}

void set_max_charges(int i) {
   max_charges = i;
}

int query_charges() {
   return charges;
}

void set_charges(int i) {
   reload(i);
}

int is_fully_charged() {
   return max_charges == charges;
}

void increment_charges() {
   charges++;
   if (charges > max_charges) {
      charges = max_charges;
   }
}

void decrement_charges() {
   charges--;
   if (charges < 0) {
      charges = 0;
   }
}
