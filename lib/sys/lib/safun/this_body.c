static object this_body(void) {
   if (!this_user()) {
      if (!monster) {
         return previous_object();
      } else {
         return monster;
      }
   }

   if (this_user()->query_player()->is_possessing()) {
      return this_user()->query_player()->query_possessing();
   }

   return this_user()->query_player();
}
