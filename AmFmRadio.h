#ifndef AmFmRadio_H
#define AmFmRadio_H
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#pragma warning(disable: 4996) // required by Visual Studio


//Constants
#define STATIONS 5
#define BANDS 3
#define MAX 4
#define MIN 0
#define SUCCESS 1
#define MAX_VOLUME 100
#define BUF_SIZE 20
#define VOLUME_SET 2
#define kFailure 0


/* -- This is a Strut Comment --
	NAME	:	Freqs
	PURPOSE :	The purpose of this structure is to represent
				the frequency of the radio.
*/
struct Freqs
{
	double AMFreq;
	double FMFreq;
};
/* -- This is a CLASS comment --
	NAME	:	AmFmRadio
	PURPOSE :	The AmFmRadio class models an AM/FM radio with
	preset frequencies, allowing users to toggle power, switch
	between AM and FM bands, select preset frequencies and
	control volume. It encapsulates the radio's state, including
	current station, band, volume level, and power status, while
	providing methods to access and modify these attributes.
*/
class AmFmRadio
{
	/* ====================================== */
	/*              PRIVATE                   */
	/* ====================================== */
private:

	/* -------------- CONSTANTS ------------- */
	/* -------------- ATTRIBUTES ------------ */
	Freqs	freq[STATIONS];
	Freqs frequencies;
	double	current_station;
	char	band[BANDS];
	int		volume;
	bool	on;
	bool displayOutput;

	/* ====================================== */
	/*              PUBLIC                    */
	/* ====================================== */
public:
	/* -------------- ATTRIBUTES ------------ */
	/* - MEMBER FUNCTIONS/METHOD PROTOTYPES - */
	void PowerToggle(void);
	void ToggleBand(void);
	int SelectPresetFreq(int freq_num);
	void ShowCurrentSettings(void);
	void ScanUp(void);
	void ScanDown(void);
	


	AmFmRadio(bool isOn = false);										//Constructor
	AmFmRadio(bool isOn, Freqs presets[5]);								//Constructor
	~AmFmRadio();														//Destructor


	/* ---------- ACCESSOR METHODS PROTOTYPES --------- */
	Freqs* GetFreq(void);
	Freqs GetCurrentFreqs(void);
	double GetCurrentStation(void);
	char* GetBand(void);
	int GetVolume(void);
	bool IsRadioOn(void);
	bool GetDisplayOutput(void);


	/* ---------- MUTATOR PROTOTYPES --------- */
	int SetPresetFreq(int freq_num);
	int SetVolume(void);
	int SetVolume(int secondVolume);
	void SetCurrentStation(double station);
	void SetDisplayOutput(bool display);

};
#endif