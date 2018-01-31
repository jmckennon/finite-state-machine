
#include <cctype>
#include <cstdlib>
#include <iostream>



#include <iostream>
using namespace std;


enum State {
   S0_STATE,
   S1_STATE,
   S2_STATE,
   S3_STATE,
   S4_STATE,
   S5_STATE,
   S6_STATE,
   S7_STATE,
   ACCEPT_STATE,
};

enum Event {
   END_OF_INPUT_EVENT,
   DIGIT_EVENT,
   EXPONENT_EVENT,
   DECIMAL_EVENT,
   SIGN_EVENT,
   INVALID_EVENT
};
const char * EVENT_NAMES[] = {
"END_OF_INPUT",
"DIGIT",
"EXPONENT",
"DECIMAL",
"SIGN",
};
Event get_next_event();
Event string_to_event(string event_string) {
   if(event_string == "END_OF_INPUT") {return END_OF_INPUT_EVENT;}
   if(event_string == "DIGIT") {return DIGIT_EVENT;}
   if(event_string == "EXPONENT") {return EXPONENT_EVENT;}
   if(event_string == "DECIMAL") {return DECIMAL_EVENT;}
   if(event_string == "SIGN") {return SIGN_EVENT;}
   return INVALID_EVENT;
}
int float_check(State initial_state) {
   State state = initial_state;
   Event event;
   while(true) {
      switch (state) {
         case S3_STATE:
            cerr << "state S3" << endl;

            event = get_next_event();
            cerr << "event " << EVENT_NAMES[event] << endl;
            switch(event) {
               case DIGIT_EVENT:

                  state = S3_STATE;
                  break;
               case DECIMAL_EVENT:

                  state = S4_STATE;
                  break;
               case EXPONENT_EVENT:

                  state = S5_STATE;
                  break;
               default:
                  cerr << "INVALID_EVENT" << event << "in state S3" << endl;
                  return -1;
            }
            break;
         case S2_STATE:
            cerr << "state S2" << endl;

            event = get_next_event();
            cerr << "event " << EVENT_NAMES[event] << endl;
            switch(event) {
               case DIGIT_EVENT:

                  state = S4_STATE;
                  break;
               default:
                  cerr << "INVALID_EVENT" << event << "in state S2" << endl;
                  return -1;
            }
            break;
         case S1_STATE:
            cerr << "state S1" << endl;

            event = get_next_event();
            cerr << "event " << EVENT_NAMES[event] << endl;
            switch(event) {
               case DECIMAL_EVENT:

                  state = S2_STATE;
                  break;
               case DIGIT_EVENT:

                  state = S3_STATE;
                  break;
               default:
                  cerr << "INVALID_EVENT" << event << "in state S1" << endl;
                  return -1;
            }
            break;
         case S0_STATE:
            cerr << "state S0" << endl;

            event = get_next_event();
            cerr << "event " << EVENT_NAMES[event] << endl;
            switch(event) {
               case DIGIT_EVENT:

                  state = S3_STATE;
                  break;
               case SIGN_EVENT:

                  state = S1_STATE;
                  break;
               case DECIMAL_EVENT:

                  state = S2_STATE;
                  break;
               default:
                  cerr << "INVALID_EVENT" << event << "in state S0" << endl;
                  return -1;
            }
            break;
         case S7_STATE:
            cerr << "state S7" << endl;

            event = get_next_event();
            cerr << "event " << EVENT_NAMES[event] << endl;
            switch(event) {
               case DIGIT_EVENT:

                  state = S6_STATE;
                  break;
               default:
                  cerr << "INVALID_EVENT" << event << "in state S7" << endl;
                  return -1;
            }
            break;
         case S6_STATE:
            cerr << "state S6" << endl;

            event = get_next_event();
            cerr << "event " << EVENT_NAMES[event] << endl;
            switch(event) {
               case DIGIT_EVENT:

                  state = S6_STATE;
                  break;
               case END_OF_INPUT_EVENT:

                  state = ACCEPT_STATE;
                  break;
               default:
                  cerr << "INVALID_EVENT" << event << "in state S6" << endl;
                  return -1;
            }
            break;
         case S5_STATE:
            cerr << "state S5" << endl;

            event = get_next_event();
            cerr << "event " << EVENT_NAMES[event] << endl;
            switch(event) {
               case DIGIT_EVENT:

                  state = S6_STATE;
                  break;
               case SIGN_EVENT:

                  state = S7_STATE;
                  break;
               default:
                  cerr << "INVALID_EVENT" << event << "in state S5" << endl;
                  return -1;
            }
            break;
         case S4_STATE:
            cerr << "state S4" << endl;

            event = get_next_event();
            cerr << "event " << EVENT_NAMES[event] << endl;
            switch(event) {
               case DIGIT_EVENT:

                  state = S4_STATE;
                  break;
               case EXPONENT_EVENT:

                  state = S5_STATE;
                  break;
               case END_OF_INPUT_EVENT:

                  state = ACCEPT_STATE;
                  break;
               default:
                  cerr << "INVALID_EVENT" << event << "in state S4" << endl;
                  return -1;
            }
            break;
         case ACCEPT_STATE:
            cerr << "state ACCEPT" << endl;

cout << "Input is valid float" << endl;
return 1;
            event = get_next_event();
            cerr << "event " << EVENT_NAMES[event] << endl;
            switch(event) {
               default:
                  cerr << "INVALID_EVENT" << event << "in state ACCEPT" << endl;
                  return -1;
            }
            break;
      }
   }
}

Event get_next_event() {
  int c;
  while (isspace(c = cin.get())) {
  }
  if (c < 0) {
     return END_OF_INPUT_EVENT;
  }
  if (isdigit(c)) {
    return DIGIT_EVENT;
  }
  if (c == '+' || c == '-') {
    return SIGN_EVENT;
  }
  if (c == '.') {
    return DECIMAL_EVENT;
  }
  if ((c == 'e') || (c == 'E')) {
    return EXPONENT_EVENT;
  }
  return INVALID_EVENT;
};


int main() {
  int result = float_check(S0_STATE);
  cout << "input is " << ((result > 0) ? "valid!" : "INvalid") << endl;
  return result > 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}

