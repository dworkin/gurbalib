static string gettable_fake_object;

string is_gettable_fake_object(void) {
   return gettable_fake_object;
}

void set_gettable_fake_object(string get) {
   gettable_fake_object = get;
}
