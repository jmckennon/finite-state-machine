#! /usr/bin/python
# ------------------------------------------------------------------------------
# Jake McKennon
# 5 December 2017
# ------------------------------------------------------------------------------

class State(object):
    def __init__(self, name, action, edges):
        self.name = name
        self.action = action
        self.edges = edges

class Edge(object):
    def __init__(self, name, new_state, action=None):
        self.name = name
        self.new_state = new_state
        if action is None:
            self.action = ''
        else:
            self.action = action

class Machine(object):
    def __init__(self, name):
        self.name = name
        self.header_ = ""
        self.footer_ = ""
        self.state_names = []
        self.states = {}
        self.events = set()

    def header(self, text):
        self.header_ = text

    def footer(self, text):
        self.footer_ = text

    def state(self, name, action="", edges=None):
        if edges is None:
            edges = []
        if name in self.states:
            raise ValueError("duplicate state " + name)
        self.state_names.append(name)
        self.states[name] = State(name, action, edges)

    def edge(self, name, new_state, action=""):
        self.events.add(name)
        return Edge(name, new_state, action)

    def gen_edge(self, edge):
        print "               case {}_EVENT:".format(edge.name)
        print edge.action
        print "                  state = {}_STATE;".format(edge.new_state)
        print "                  break;"

    def gen_state(self, state_name):
        print "         case {}_STATE:".format(state_name)
        print '            cerr << "state {}" << endl;'.format(state_name)
        print self.states[state_name].action
        print "            event = get_next_event();"
        print '            cerr << "event " << EVENT_NAMES[event] << endl;'
        print "            switch(event) {"

        if self.states[state_name].edges != None:
            for edge in self.states[state_name].edges:
                self.gen_edge(edge)

        print "               default:"
        print '                  cerr << "INVALID_EVENT" << event << "in state {}" << endl;'.format(state_name)
        print '                  return -1;'
        print "            }"
        print "            break;"

    def edges(self, *args_list):
        edge_list = []
        if args_list:
            for e in args_list:
                self.events.add(e[0])
                edge_list.append(Edge(e[0], e[1]))
        return edge_list

    def gen(self):
        print self.header_
        print """

#include <iostream>
using namespace std;

"""
        print "enum State {"
        for name in self.state_names:
            print "   {}_STATE,".format(name)
        print "};"

        print

        print "enum Event {"
        for name in self.events:
            print "   {}_EVENT,".format(name)
        print "   INVALID_EVENT"
        print "};"

        print "const char * EVENT_NAMES[] = {"
        for event in self.events:
            print '"{}",'.format(event)
        print "};"

        print "Event get_next_event();"

        print "Event string_to_event(string event_string) {"

        for event in self.events:
            print '   if(event_string == "{ev}") {{return {ev}_EVENT;}}'.format(ev=event)

        print "   return INVALID_EVENT;"
        print "}"

        print "int {}(State initial_state) {{".format(self.name)
        print "   State state = initial_state;"
        print "   Event event;"
        print "   while(true) {"
        print "      switch (state) {"

        for state in self.states.keys():
            self.gen_state(state)

        print "      }"
        print "   }"
        print "}"

        print self.footer_
