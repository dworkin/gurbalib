void main( string str )
{
 int max_hp;
 max_hp = this_player()->query_max_hp();
 this_player()->set_hp(max_hp);
 write("You are completely healed!\n");
}
