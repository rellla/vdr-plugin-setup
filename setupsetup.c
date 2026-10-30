/****************************************************************************
 * DESCRIPTION:
 *             Setup Dialog
 *
 * $Id: setupsetup.cpp,v 1.2 2005/10/12 13:44:14 ralf Exp $
 *
 * Contact:    ranga@vdrtools.de
 *
 * Copyright (C) 2005 by Ralf Dotzert
 ****************************************************************************/


#include <vdr/menu.h>
#include "submenu.h"
#include <string.h>

#include "setupsetup.h"
#include "util.h"
#include "debug.h"

//*****************************************************************************
// Setup Configuration
//*****************************************************************************

cSetupSetup::cSetupSetup()
{
  // Set Default Values
  strcpy(_menuSuffix, " ...");
  strcpy(_entryPrefix, "-");
  DirectMenu = 0;
  ReturnValue = 1;
}

bool cSetupSetup::SetupParse( const char *Name, const char *Value )
{
  if      (!strcasecmp(Name, "DirectMenu"))  DirectMenu = atoi(Value);
  else if (!strcasecmp(Name, "MenuSuffix"))  snprintf(_menuSuffix, sizeof(_menuSuffix), "%s", Value);
  else if (!strcasecmp(Name, "EntryPrefix")) snprintf(_entryPrefix, sizeof(_entryPrefix), "%s", Value);
  else if (!strcasecmp(Name, "ReturnValue")) ReturnValue = atoi(Value);
  else return false;

  return true;
}

//*****************************************************************************
// Setup Page
//*****************************************************************************
cSetupSetupPage::cSetupSetupPage( )
{
  ReturnValues[0]="true/false";
  ReturnValues[1]="on/off";
  ReturnValues[2]="yes/no";

  Add(new cMenuEditBoolItem(tr("setupSetup$Main menu entry"), &setupSetup.DirectMenu, tr("Setup"), tr("Menu Edit")));
  Add(new cMenuEditStrItem(tr("setupSetup$Menu suffix"),       setupSetup._menuSuffix, sizeof(setupSetup._menuSuffix),  trVDR(FileNameChars)));
  Add(new cMenuEditStrItem(tr("setupSetup$Entry prefix"),      setupSetup._entryPrefix, sizeof(setupSetup._entryPrefix), trVDR(FileNameChars)));
  Add(new cMenuEditStraItem(tr("setupSetup$Return value"),    &setupSetup.ReturnValue, 3, ReturnValues));
}


void cSetupSetupPage::Store( void )
{
  SetupStore("DirectMenu",      setupSetup.DirectMenu);
  SetupStore("MenuSuffix",      setupSetup._menuSuffix);
  SetupStore("EntryPrefix",     setupSetup._entryPrefix);
  SetupStore("ReturnValue",     setupSetup.ReturnValue);
}

eOSState cSetupSetupPage::ProcessKey( eKeys Key )
{
  cSubMenu vdrSubMenu;
  eOSState state = cOsdMenu::ProcessKey(Key);
  if (state == osUnknown) {
     switch (Key) {
        case kOk: { // Load Menu Configuration
                 cString menuXML = Util::ConfigFile("vdr-menu");
                 if (vdrSubMenu.LoadXml((char *)*menuXML)) {
                    isyslog("setup: saved setup to %s", *menuXML);
                    vdrSubMenu.SetMenuSuffix(setupSetup._menuSuffix);
                    vdrSubMenu.SaveXml();
                    }
                 }
                 Store();
                 return osBack;
        default: break;
        }
     state = osContinue;
     }
  return state;
}


