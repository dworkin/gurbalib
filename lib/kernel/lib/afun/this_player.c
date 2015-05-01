static object this_player(void) {
   object ob;

   ob = DRIVER->get_tlvar(TLS_THIS_PLAYER);
   if (ob) {
      return ob;
   }

   if (this_user() && this_user()->query_player()) {
      if (this_user()->query_player()->is_possessing()) {
         return (this_user()->query_player()->query_possessing());
      }
      return this_user()->query_player();
   }
}
