nomask void destruct_object(object ob) {
   argcheck(ob, 1, "object");

   if (find_object(COMPILER_D) && COMPILER_D->allow_object(ob->base_name())) {
      ob->_F_destruct();
   } else {
      console_msg("WARNING: destruct_object() used on an inheritable: " +
         ob->base_name() + "\n");
      ::destruct_object(ob);
   }
}
