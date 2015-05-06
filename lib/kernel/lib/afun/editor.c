static nomask string editor(string cmd) {
   if (KERNEL() || owner_file(previous_program()) == "system") {
      return ::editor( cmd );
   }
}
