/* 
Display the chat channels a player is subscribed to
Arron Cusimano (mordain) 20090314
*/
void main( string str ) {
    string *achannels, *schannels;
    string out;
    int i, sz;
    
    schannels = this_player()->query_channels();
    achannels = CHANNEL_D->query_channels();
    
    out = "%^BOLD%^%^CYAN%^Available channels: %^RESET%^\n";
    for( i=0, sz = sizeof( achannels ); i < sz; i++ ) {
        out += achannels[i] + "     \t"; /* very suss formatting */
        out += (member_array(achannels[i], schannels) == -1) ? 
            "%^RED%^OFF" : "%^GREEN%^ON";
        out += "%^RESET%^\n";
    }
    out += "\n";
    this_player()->message( out );
}
