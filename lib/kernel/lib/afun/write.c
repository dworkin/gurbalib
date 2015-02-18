void write(string str) {
   argcheck(str, 1, "string");

   if (!this_player()) {
      return;
   }

   this_player()->message(str);

   if (this_player()->is_snooped()) {
      this_player()->do_snoop(str);
   }
}
