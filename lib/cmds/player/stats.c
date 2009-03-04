void main( string arg )
{
   write("Strength    : "+this_player()->query_stat("str") );
   write("Intelligence: "+this_player()->query_stat("int") );
   write("Wisdom      : "+this_player()->query_stat("wis") );
   write("Dexterity   : "+this_player()->query_stat("dex") );
   write("Constitution: "+this_player()->query_stat("con") );
   write("Charisma    : "+this_player()->query_stat("cha") );

   write("Hit Points  : "+this_player()->query_hp()+"/"+this_player()->query_max_hp() );

}
