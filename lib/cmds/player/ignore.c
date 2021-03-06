/* Add a user to your ignore list  -- Arron Cusimano (mordain) 20090321 */
void main( string arg ) {
    string out;
    int i, sz;
    string *list;

    if ( arg == "" ) {
        out = "Ignored list:\n";
        list = this_player()->query_ignored_all();
        for ( i = 0, sz = sizeof(list); i < sz; ++i ) 
            out += list[i] + "\n";
        write(out);
        /*write(dump_value(this_player()->query_ignored_all(), ([])));*/
        return;
    }
    if ( this_player()->query_ignored(arg) ) {
        write("Removing " + arg + "\n");
        this_player()->remove_ignore(arg);
        return;
    }
    write("Ignoring " + arg + "\n");
    this_player()->add_ignore(arg);
}
