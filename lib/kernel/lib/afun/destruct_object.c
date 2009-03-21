void destruct_object(object ob) {
  argcheck( ob, 1, "object" );
  ob->_F_destruct();
}

