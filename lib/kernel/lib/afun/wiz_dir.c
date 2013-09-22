string wiz_dir(object ob) {
   argcheck(ob, 1, "object");

   return (WIZ_DIR + "/" + ob->query_name() + "/");
}
