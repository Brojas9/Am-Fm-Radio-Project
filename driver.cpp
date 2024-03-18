/* -- FILEHEADER COMMENT --
   NAME    : AmFmRadio
   PURPOSE : This header file contains the declaration of the AmFmRadio
   class, which represents an AM/FM radio device. It provides functionalities
   to toggle power, adjust volume, select radio bands, set and select preset
   frequencies, scan through stations, and display current settings.
*/
#include "AmFmRadio.h"


int main(void)
{
    bool on = true;
    bool off = false;

    AmFmRadio radioAmFm(on); // Instantiate with default settings
    radioAmFm.PrintMenu();// Radio object   

    return 0;
}