void out_unmod(string str) {
   argcheck(str, 1, "string");

   if (!this_user()) {
      return;
   }

   this_user()->put_original(str);

   if (this_player()->is_snooped()) {
      this_player()->do_snoop(str);
   }
}
