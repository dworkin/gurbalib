static void set_this_player(object ob) {
   switch (owner_file(previous_program())) {
      case "kernel":
      case "system":
      case "game":
         DRIVER->set_tlvar(TLS_THIS_PLAYER, ob);
         break;
      default:
         error("Bad call to set_this_player");
         break;
   }
}
