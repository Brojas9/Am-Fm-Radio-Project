#include "AmFmRadio.h"


/*  -- Constructor Header Comment
	Name    :   AmFmRadio-- CONSTRUCTOR
	Purpose :   Constructor for the AmFmRadio class.
	Inputs  :   isOn: Boolean indicating whether the radio is initially turned on or off.
	Outputs :   Initializes the AmFmRadio object with the default initial state.
	Returns :   None
*/
AmFmRadio::AmFmRadio(bool isOn) : on(isOn), displayOutput(false)
{
	for (int i = 0; i < kStations; ++i) {
		freq[i].AMFreq = 530;
		freq[i].FMFreq = 87.9;
	}
	// Default frequencies
	frequencies.AMFreq = 530;
	frequencies.FMFreq = 87.9;

	if (isOn)
	{
		// Default initialization
		volume = 0;
		current_station = 530;
		strcpy(band, "AM");
	}
	else
	{	//When radio is turned off
		volume = kMinVol;
		current_station = 0;
		strcpy(band, "");
	}
}


/*  -- Constructor Header Comment
	Name    :   AmFmRadio -- CONSTRUCTOR
	Purpose :   Constructor for the AmFmRadio class.
	Inputs  :   isOn: Boolean indicating whether the radio is initially turned on or off.
				presets: Array of Freqs representing the preset frequencies for the radio stations.
	Outputs :   Initializes the AmFmRadio object with the specified initial state and preset frequencies.
	Returns :   None
*/
AmFmRadio::AmFmRadio(bool isOn, Freqs presets[]) : displayOutput(false)
{
	for (int i = 0; i < kStations; ++i) {
		freq[i] = presets[i];
	}
}


/*  -- Destructor Header Comment
	Name    :   ~AmFmRadio -- DESTRUCTOR
	Purpose :   Destructor for the AmFmRadio class.
	Inputs  :   None
	Outputs :   Outputs a message indicating the destruction of the AmFmRadio object.
	Returns :   None
*/
AmFmRadio::~AmFmRadio()
{
	printf("Destroying AmFmRadio\n");
}


/*  -- Member Function Header Comment
	Name    :   PowerToggle
	Purpose :   Toggle the power state of the radio (on/off).
	Inputs  :   None
	Outputs :   Updates the on attribute to the toggled state (true/false).
				Updates the volume attribute to 0 when turning off the radio.
				Restores the previous volume level when turning on the radio.
				Updates the current_station attribute with the corresponding
				frequency when turning on the radio.
	Returns :   None
*/
void AmFmRadio::PowerToggle(void)
{
	if (!on)
	{
		on = true;
		if (volume <= 0)
		{
			volume = kMinVol;
		}

		if (strcmp(band, "AM") == 0)
		{
			current_station = frequencies.AMFreq;
		}
		else
		{
			current_station = frequencies.FMFreq;
		}
	}
	else
	{
		if (strcmp(band, "AM") == 0)
		{
			frequencies.AMFreq = current_station;
		}
		else
		{
			frequencies.FMFreq = current_station;
		}
		// Radio is being turned off
		int prevVolume = volume;
		volume = kMinVol;
		volume = prevVolume;
		on = false;
		current_station = 0;
	}
}


/*  -- Member Function Header Comment
	Name    :   ToggleBand
	Purpose :   Toggle the radio band between AM and FM.Store current AM/FM
				frequency and Restore previous FM/AM frequency
	Inputs  :   None
	Outputs :   Updates the band (AM or FM).
	Returns :   None
*/
void AmFmRadio::ToggleBand(void)
{
	if (strcmp(band, "AM") == 0)
	{
		frequencies.AMFreq = current_station;
		strcpy(band, "FM");
		current_station = frequencies.FMFreq;
	}
	else
	{
		frequencies.FMFreq = current_station;
		strcpy(band, "AM");
		current_station = frequencies.AMFreq;
	}
}


/*  -- Member Function Header Comment
	Name    :   SelectPresetFreq
	Purpose :   Set the current station to the preset frequency corresponding
				to the given frequency number.
	Inputs  :   int freq_num: The number corresponding to the preset frequency
				to be selected.
	Outputs :   Updates the current_station with the selected frequency.
	Returns :   int
*/
int AmFmRadio::SelectPresetFreq(int freq_num)
{
	if ((freq_num >= kMinFreqs) && (freq_num <= kMaxFreqs))
	{
		if (strcmp("AM", band) == 0)
		{
			current_station = freq[freq_num].AMFreq;
		}
		else
		{
			current_station = freq[freq_num].FMFreq;
		}
		return kSuccess;
	}
	return kFailure;
}


/*  -- Member Function Header Comment
	Name    :   ShowCurrentSettings
	Purpose :   Display the current settings of the radio, including the radio band, volume, and current station.
				Also displays the preset frequency settings for both AM and FM bands.
	Inputs  :   None
	Outputs :   Prints the current settings of the radio.
	Returns :   None
*/
void AmFmRadio::ShowCurrentSettings(void)
{
	int volCero = 0;

	if (on == true)
	{
		printf("\n\nRadio is on. \n");
	}
	else
	{
		printf("\n\nRadio is off. \n");
	}

	printf("\nRadio Band: %s\n", band);
	if (on == true)
	{
		printf("Volume: %d\n", volume);
	}
	else
	{
		printf("Volume: %d\n", volCero);
	}

	if (strcmp("AM", band) == 0)
	{
		printf("Current Station: %.f %s\n", current_station, band);
	}
	else
	{
		printf("Current Station: %.1f %s\n", current_station, band);
	}

	printf("AM Freq Settings:");
	for (int i = 0; i < kStations; ++i)
	{
		printf("%2d) %5d ", i + 1, freq[i].AMFreq);
	}

	printf("\nFM Freq Settings:");
	for (int j = 0; j < kStations; ++j)
	{
		printf("%2d) %5.1f ", j + 1, freq[j].FMFreq);
	}
}


/*  -- Member Function Header Comment
	Name    :   ScanUp
	Purpose :   Increase the current station frequency when tuning up the radio band.
				If current_station is 1700, the current_station becomes 530, if
				current_station is 107.9, the current_station becomes 87.9
	Inputs  :   None
	Outputs :   Updates the current station frequency.
	Returns :   None
*/
void AmFmRadio::ScanUp(void)
{
	if (strcmp("AM", band) == 0)
	{
		if (current_station == 1700)
		{
			current_station = 530;
		}
		else
		{
			current_station = current_station + 10;
		}
	}
	else
	{
		//FM band		
		if (current_station >= 107.9)
		{
			current_station = 87.9;
		}
		else
		{
			current_station = current_station + 0.2;
		}
	}
	if (displayOutput)
	{
		printf("\nCurrent station: %f %s\n", current_station, band);
	}
}


/*  -- Member Function Header Comment
	Name    :   ScanDown
	Purpose :   Decrease the current station frequency when tuning down the radio band.
	Inputs  :   None
	Outputs :   Updates the current station frequency.
	Returns :   None
*/
void AmFmRadio::ScanDown(void)
{
	if (strcmp("AM", band) == 0)
	{
		//if current_station is 530, the current_station becomes 1700
		if (current_station == 530)
		{
			current_station = 1700;
		}
		else
		{
			current_station = current_station -= 10;
		}
	}
	else
	{
		//if the current_station is 107.9, the current_station becomes 87.9
		//Note: car radios jump .2 for the FM. That's how it's modeled here.
		if (current_station <= 87.9)
		{
			current_station = 107.9;
		}
		else
		{
			current_station = current_station -= 0.2;
		}
	}
	if (displayOutput)
	{
		printf("\nCurrent station: %f %s\n", current_station, band);
	}
}


/*  -- Member Function Header Comment
	Name    :   PrintMenu
	Purpose :   Display the main menu and execute the selected menu option.
	Inputs  :   User input
	Outputs :   Prints the main menu.
	Returns :   None
*/
void AmFmRadio::PrintMenu(void)
{
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
	char		buf[kSize] = { 0 };
	bool		on = false;

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
			PowerToggle();
			break;
		case kMenuSetVolume:
			volStore = SetVolume();
			if (volStore == kMinVol)
			{
				printf("\nVolume was set to 0.");
			}
			else if (volStore == kSetToMax)
			{
				printf("\nVolume was set to 100.");
			}
			break;

		case kMenuToggleAMFM:
			on = IsRadioOn();
			if (on)
			{
				ToggleBand();
			}
			else
			{
				printf("\nThe radio must be turned on before the "
					"band can be toggled!");
			}
			break;
		case kMenuSetFreq:
			on = IsRadioOn();
			if (on)
			{
				printf("\nWhich frequency do you want to set?");
				fgets(buf, sizeof buf, stdin);
				freq_num = atoi(buf) kNull;
				freqStore = SetPresetFreq(freq_num);
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
			on = IsRadioOn();
			if (on)
			{
				printf("\nEnter the number of the preset frequency: ");
				fgets(buf, kSize, stdin);
				freq_num = atoi(buf) kNull;
				freqStore = SelectPresetFreq(freq_num);
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
			ShowCurrentSettings();
			break;
		case kMenuScanUp:
			on = IsRadioOn();
			if (on)
			{
				ScanUp();
			}
			else
			{
				printf("\nYou must turn the radio on before you can use the scan up frequency!\n");
			}
			break;
		case kScanDown:
			on = IsRadioOn();
			if (on)
			{
				ScanDown();
			}
			else
			{
				printf("\nYou must turn the radio on before you can use the scan down frequency!\n");
			}
			break;
		case kMenuQuit:
			printf("\nGoodbye!\n");
			AmFmRadio::~AmFmRadio();
			exit(kSuccess);
		default:
			printf("You have entered an invalid selection. Please make \n"
				"another selection.\n");
			break;
		}

		if ((choice != kMenuShowCurrentSettings) && (choice != kMenuQuit))
			ShowCurrentSettings();

	} while (choice != kMenuQuit);
}


/*  -- Accessor Method Header Comment
	Name    :   GetFreq
	Purpose :   Retrieve the array of frequency settings.
	Inputs  :   None
	Outputs :   None
	Returns :   Freqs* to the array of frequency settings.
*/
Freqs* AmFmRadio::GetFreq(void)
{
	return freq;
}


/*  -- Accessor Method Header Comment
	Name    :   GetCurrentFreqs
	Purpose :   Retrieve the current frequencies of the radio.
	Inputs  :   None
	Outputs :   None
	Returns :   Freqs - The current frequencies as an instance.
*/
Freqs AmFmRadio::GetCurrentFreqs(void)
{
	return frequencies;
}


/*  -- Accessor Method Header Comment
	Name    :   GetCurrentStation
	Purpose :   Retrieve the current station of the radio.
	Inputs  :   None
	Outputs :   None
	Returns :   double - The current station frequency.
*/
double AmFmRadio::GetCurrentStation(void)
{
	return current_station;
}


/*  -- Accessor Method Header Comment
	Name    :   GetBand
	Purpose :   Retrieve the current band of the radio.
	Inputs  :   None
	Outputs :   None
	Returns :   char* to an array representing the current band.
*/
char* AmFmRadio::GetBand(void)
{
	return band;
}


/*  -- Accessor Method Header Comment
	Name    :   GetVolume
	Purpose :   Retrieve the current volume level of the radio.
	Inputs  :   None
	Outputs :   None
	Returns :   int - the current volume level (0 - 100).
*/
int AmFmRadio::GetVolume(void)
{
	return volume;
}


/*  -- Accessor Method Header Comment
	Name    :   IsRadioOn
	Purpose :   Check if the radio is currently turned on.
	Inputs  :   None
	Outputs :   None
	Returns :   A boolean value indicating whether the radio is on (true) or off (false).
*/
bool AmFmRadio::IsRadioOn(void)
{
	return on;
}


/*  -- Accessor Method Header Comment
	Name    :   GetDisplayOutput
	Purpose :   Retrieve the current display output status.
	Inputs  :   None
	Outputs :   None
	Returns :   bool.
*/
bool AmFmRadio::GetDisplayOutput(void)
{
	return displayOutput;
}


/* -- Mutator Header Comment
	Name    :   SetPresetFreq
	Purpose :   Set the preset frequency for a specific preset number.
	Inputs  :   freq_num - the preset number of the frequency to be set.
	Outputs :   None
	Returns :   kSuccess if the preset frequency is set successfully within the valid range,
				kFailure if the preset number is out of range.
*/
int AmFmRadio::SetPresetFreq(int freq_num)
{
	if ((freq_num >= kMinFreqs) && (freq_num <= kMaxFreqs))
	{
		if (strcmp("AM", band) == 0)
		{
			freq[freq_num].AMFreq = current_station;
		}
		else
		{
			freq[freq_num].FMFreq = current_station;
		}
		return kSuccess;
	}
	return kFailure;
}


/*  -- Mutator Header Comment
	Name	:	SetVolume
	Purpose :	Set the volume level of the radio..
	Inputs	:	User input
	Outputs	:	NONE
	Returns	:	kMinVol if the volume is set to the minimum volume,
				kSetToMax if the volume is set to the maximum volume,
				kSuccess if the volume is set successfully within the valid range.
*/
int AmFmRadio::SetVolume(void)
{
	char buf[kSize] = "";

	printf("\nEnter the volume level (0 - 100) : ");
	fgets(buf, sizeof buf, stdin);
	volume = atoi(buf);

	if (volume < kMinVol)
	{
		volume = kMinVol;
		return kMinVol;
	}

	if (volume > kMaxVol)
	{
		volume = kMaxVol;
		return kSetToMax;
	}
	return kSuccess;
}


/*  -- Mutator Header Comment
	Name	:	SetVolume
	Purpose :	This us the second version of SetVolume.
	Inputs	:	secondVolume
	Outputs	:	NONE
	Returns	:	int
*/
int AmFmRadio::SetVolume(int secondVolume)
{
	volume = secondVolume;

	if (volume < kMinVol)
	{
		volume = kMinVol;
	}
	else if (volume > kMaxVol)
	{
		volume = kMaxVol;
	}
	return kSuccess;
}


/*  -- Mutator Header Comment
	Name	:	SetCurrentStation
	Purpose :	To modify the current_station attribute of the class,
				allowing the user to set the current station frequency
				of the radio.
	Inputs	:	station
	Outputs	:	NONE
	Returns	:	double
*/
void AmFmRadio::SetCurrentStation(double station)
{
	current_station = station;
}


/*  -- Mutator Header Comment
	Name	:	SetDisplayOutput
	Purpose :	To modify displayOutput attribute of the class, allowing
				the user to control whether the output should be displayed.
	Inputs	:	display
	Outputs	:	NONE
	Returns	:	bool
*/
void AmFmRadio::SetDisplayOutput(bool display)
{
	displayOutput = display;
}
