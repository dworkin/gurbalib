void clone_autoload_objects(string str) {
   string file, argument, rest;
   object ob;

   while (str && str != "*^!") {
      if (sscanf(str, "%s:%s^!%s", file, argument, rest) != 3) {
	 write("Autoload string corrupt.\n");
	 return;
      }
      str = rest;
      /*   ob = find_object(file);
         if (!ob)
         continue;  */
      ob = clone_object(file);
      if (argument) {
	 ob->initialize_autoload(argument);
      }
      ob->move(this_player());
   }
}
