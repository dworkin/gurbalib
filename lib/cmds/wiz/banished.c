void main(string name) {
  string info;

  if(BANISH_D->is_banished(name)) {
    info = unguarded("read_file", "/data/banished/" + name);
    write("The name '"+name+"' was banished:\n"+"\t"+info+"\n");
  } else {
    write("The name: "+name+" is NOT a banished name.\n");
  }
}
