#define ZOOM   5

#define YEAR    17
#define MONTH   20
#define DAY     24
#define WEEK    4
#define HOUR    60

static string *months;
static string *days;

int time;

static void restore_me(void);

void create(void) {
   unguarded("restore_me");

   months = ({
      "Calninque", "Ben'ka", "Belegaer", "Mosiana", "Amaros",
      "Zalbus", "Sisyana", "Rhom", "Paknos", "Alachir", "Fuindell",
      "Helethia", "Jaran", "Bethel", "Ilkira", "Yavanna", "Mosisis"
   });

   days = ({ 
      "Earth", "Wind", "Fire", "Water"
   });

   call_out("update_time", ZOOM);
}

static void save_me(void) {
   save_object("/daemons/data/time_d.o");
}

static void restore_me(void) {
   restore_object("/daemons/data/time_d.o");
}

void update_time(void) {
   time++;
   if (!(time % 60)) {
      unguarded("save_me");
   }
   call_out("update_time", ZOOM);
}

int query_minute(void) {
   return (time % HOUR);
}

int query_hour() {
   return ((time / HOUR) % DAY);
}

int query_day(void) {
   return (((time / (HOUR * DAY)) % MONTH));
}

int query_weekday(void) {
   return (query_day() % WEEK);
}

string query_weekday_name(void) {
   return (days[query_weekday()]);
}

int query_month(void) {
   return ((time / (HOUR * DAY * MONTH)) % YEAR);
}

string query_month_name(void) {
   return (months[query_month()]);
}

int query_year(void) {
   return (time / (HOUR * DAY * MONTH * YEAR));
}

string query_time(void) {
   string str, hour, minute;

   hour = "00" + query_hour();
   minute = "00" + query_minute();

   hour = hour[strlen(hour) - 2..];
   minute = minute[strlen(minute) - 2..];

   str = query_weekday_name() + " " + query_month_name() + " " +
      (query_day() + 1) + " " + hour + ":" + minute + " " + query_year();
   return str;
}
