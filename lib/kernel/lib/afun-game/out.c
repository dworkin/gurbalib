void out(string str) {
   argcheck(str, 1, "string");

   if (!this_user()) {
      return;
   }

   this_player()->message_orig(str);

   if (this_player()->is_snooped()) {
      this_player()->do_snoop(str);
   }
}
