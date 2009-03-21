void main(string str) {
  if(!str || str == "") {
    write("usage: unset <var name>");
    return;
  }

  this_player()->set_env(str,nil);
}
