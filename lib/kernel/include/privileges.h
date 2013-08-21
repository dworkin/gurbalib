#define KERNEL() (sscanf(previous_program(),"/kernel/%*s") == 1)
#define CALLOUT() ((previous_program()==AUTO) && (previous_function()=="_F_call_out2"))
