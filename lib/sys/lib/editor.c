void edit(string cmd) {
   cmd = editor(cmd);
   if (cmd) {
      this_player()->write(cmd);
      this_player()->write_prompt();
   }
   if (!query_editor(this_object())) {
      this_player()->write("Left edit.");
      this_player()->write_prompt();
   }
}

int is_editing(void) {
   if (query_editor(this_object())) {
      return 1;
   }
   return 0;
}
