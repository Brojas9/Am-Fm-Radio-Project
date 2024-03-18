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

    AmFmRadio radioAmFm(true); // Instantiate with default settings
    //radioAmFm;  

	enum menuItems
	{
		kMenuNothing = 0,	// special constant for initialization only
		kMenuTogglePower = 1, kMenuSetVolume, kMenuToggleAMFM, kMenuSetFreq, kMenuSelectFreq,
		kMenuShowCurrentSettings, kMenuScanUp, kScanDown, kMenuQuit
	};

	menuItems	choice = kMenuNothing;

	int			volStore = 0;
	int			freqStore = 0;
	int			freq_num = 0;
	char		buf[BUF_SIZE] = { 0 };
	//bool		on = false;

	do
	{
		printf("\n\nMAIN MENU\n");
		printf("=========\n\n");
		printf("1.  Toggle Power\n");
		printf("2.  Set Volume\n");
		printf("3.  Toggle AM / FM Band\n");
		printf("4.  Set a Preset Freq \n");
		printf("5.  Select a Preset Freq \n");
		printf("6.  Show Current Settings\n");
		printf("7.  Scan Up \n");
		printf("8.  Scan Down\n");
		printf("9.  Quit the Program\n");
		printf("\nMake a selection from the menu : ");
		fgets(buf, sizeof buf, stdin);
		choice = (menuItems)atoi(buf);

		switch (choice)
		{
		case kMenuTogglePower:
			radioAmFm.PowerToggle();
			break;
		case kMenuSetVolume:
			volStore = radioAmFm.SetVolume();
			if (volStore == MIN)
			{
				printf("\nVolume was set to 0.");
			}
			else if (volStore == VOLUME_SET)
			{
				printf("\nVolume was set to 100.");
			}
			break;

		case kMenuToggleAMFM:
			on = radioAmFm.IsRadioOn();
			if (on)
			{
				radioAmFm.ToggleBand();
			}
			else
			{
				printf("\nThe radio must be turned on before the "
					"band can be toggled!");
			}
			break;
		case kMenuSetFreq:
			on = radioAmFm.IsRadioOn();
			if (on)
			{
				printf("\nWhich frequency do you want to set?");
				fgets(buf, sizeof buf, stdin);
				freq_num = atoi(buf) -1;
				freqStore = radioAmFm.SetPresetFreq(freq_num);
				if (freqStore == 0)
				{
					printf("\nYou entered an invalid frequency number!");
				}
			}
			else
			{
				printf("\nYou must turn the radio on before you set the frequency!\n");
			}
			break;
		case kMenuSelectFreq:
			on = radioAmFm.IsRadioOn();
			if (on)
			{
				printf("\nEnter the number of the preset frequency: ");
				fgets(buf, BUF_SIZE, stdin);
				freq_num = atoi(buf) -1;
				freqStore = radioAmFm.SelectPresetFreq(freq_num);
				if (freqStore == 0)
				{
					printf("\nYou entered an invalid frequency number!");
				}
			}
			else
			{
				printf("\nYou must turn the radio on before you set the frequency!\n");
			}
			break;
		case kMenuShowCurrentSettings:
			radioAmFm.ShowCurrentSettings();
			break;
		case kMenuScanUp:
			on = radioAmFm.IsRadioOn();
			if (on)
			{
				radioAmFm.ScanUp();
			}
			else
			{
				printf("\nYou must turn the radio on before you can use the scan up frequency!\n");
			}
			break;
		case kScanDown:
			on = radioAmFm.IsRadioOn();
			if (on)
			{
				radioAmFm.ScanDown();
			}
			else
			{
				printf("\nYou must turn the radio on before you can use the scan down frequency!\n");
			}
			break;
		case kMenuQuit:
			printf("\nGoodbye!\n");
			radioAmFm.~AmFmRadio();
			exit(SUCCESS);
		default:
			printf("You have entered an invalid selection. Please make \n"
				"another selection.\n");
			break;
		}

		if ((choice != kMenuShowCurrentSettings) && (choice != kMenuQuit))
			radioAmFm.ShowCurrentSettings();

	} while (choice != kMenuQuit);

    return 0;
}