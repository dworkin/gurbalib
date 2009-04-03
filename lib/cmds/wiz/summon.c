void main(string str) {
    object usr;
    object player;
    if (!str || str == "") {
        write("Get whom?");
        return;
    }
    usr = USER_D->find_user( lowercase( str ) );
    if (usr) {
        if (usr->query_player()->query_environment() != this_player()->query_environment()) {
            mixed desc;
            write( "We're summoning " + str + ", who is currently here: " + usr->query_player()->query_environment()->file_name() );
            player = usr->query_player();
            player->message( "%^RED%^" + capitalize(this_player()->query_name()) + " requests your presence.%^RESET%^" );
            player->query_environment()->tell_room(player, capitalize(player->query_name()) + " disappears in a flurry of fluff.\n");
            player->move(this_player()->query_environment());
            player->message( "You abruptly find yourself somewhere else.\n" );
            player->query_environment()->tell_room( player, capitalize(player->query_name()) + " appears in a cloud of fluff.\n" );
        } else {
            write(capitalize(str) + " is already here.\n");
        }
    } else {
        write( "Unable to find " + str + ".\n" );
    }
}
