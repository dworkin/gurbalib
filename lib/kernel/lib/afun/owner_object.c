static string owner_object(object ob) {
   argcheck(ob, 1, "object");

   return owner_file(ob->file_name());
}
