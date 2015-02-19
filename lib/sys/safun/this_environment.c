object this_environment(void) {
   if (this_player()) {
      return this_player()->query_environment();
   } else {
      return nil;
   }
}
