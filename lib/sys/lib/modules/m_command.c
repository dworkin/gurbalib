/* inheritable for commands */

static void main( string arg );

static nomask string query_command() {
  return get_otlvar( "command" );
}

nomask void _main(string arg, string cmd) {
  if (previous_program() == COMMAND_D) {
    set_otlvar("command", cmd);
    main(arg);
  }
}
