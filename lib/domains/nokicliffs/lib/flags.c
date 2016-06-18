private int flags;

int test_flag(int which) {
   return flags & which;
}

void set_flag(int which) {
   flags |= which;
}

void unset_flag(int which) {
   flags &= ~which;
}

void toggle_flag(int which) {
   if (test_flag(which)) {
      unset_flag(which);
      return;
   }
   set_flag(which);
}

void create(void) {
   flags = 0;
}
