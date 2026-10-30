/*********************************************************
 * DESCRIPTION: 
 *             Header File
 *
 * $Id: util.h,v 1.7 2006/03/06 19:16:41 ralf Exp $
 *
 * Contact:    ranga@vdrtools.de
 *
 * Copyright (C) 2004 by Ralf Dotzert 
 *********************************************************/

#ifndef UTIL_H
#define UTIL_H
#include <vdr/tools.h>
#include <vdr/timers.h>


/**
@author Ralf Dotzert
*/
class Util{
public:
    Util();
    ~Util();
    enum Type { UNDEFINED,TEXT, NUMBER_TEXT, HEX, IP, BOOL, NUMBER, SELECTION};
    static char * Strdupnew(const char  *str);
    static char * Strdupnew(const char  *prefix, const char  *str);
    static char * Strdupnew( const char  *str, int size );
    static bool isBool(const char *string, bool &flag);
    static bool isBool(const char *string, int  &flag);
    static bool isType( const char * string, Util::Type & typ );
    static bool isNumber( const char * string, int &number );
    static const char * typeToStr(Type type);
    static const char * boolToStr( bool val );
    static void SwitchChannelList(const char  *selectedChannelList);
    static cString ConfigFile(const char *name);
};

class TimerString : public cListObject
{
  private:
    cString  _timer;
    cString  _remote;
    int      _id;
  public:
    TimerString (cString timer, const char *remote = NULL, int id = 0) {_timer=timer; _remote=remote; _id=id; }
    cString      GetTimerString() {return (_timer);}
    const char  *GetRemote()      {return (*_remote);}
    int          GetId()          {return (_id);}
};

class TimerList
{
  private:
    cList<TimerString>  myTimers;
  public:
    TimerList()  {};
    ~TimerList() {};
    bool SaveTimer();
    void RestoreTimer();
};

#endif
