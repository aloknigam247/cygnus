#ifndef _CMDLINE_H
#define _CMDLINE_H

#include <list>
#include <string>

using namespace std;

class Cmdline {
  public:

    class Option {
      private:
        char _shortName;
        string _longName;
        string _value;
        string _default;
        string _help;
      public:
        Option(char sName, string lName, string dValue, string help):
          _shortName(sName),
          _longName(lName),
          _default(dValue),
          _help(help)
        {}
    };

    const int _argc;
    const char **_argv;
    list<Option*> _options;

  public:
    Cmdline(const int argc, const char *argv[]);
    void add_option(char sName, string lName, string dValue, string help) {
      _options.push_back(new Option(sName, lName, dValue, help));
    }
};

#endif
