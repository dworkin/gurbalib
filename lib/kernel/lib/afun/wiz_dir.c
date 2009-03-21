string wiz_dir( object ob ) {
  argcheck( ob, 1, "object" );
  return( "/wiz/" + ob->query_name() + "/" );
}

