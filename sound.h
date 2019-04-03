// constants definitions
#define RATE 16000
#define DUR 1
#define RCMD "arecord -r16000 -c1 -f S16_LE -d1 -q test.wav"
// data structures
struct WAVHDR{
	char ChunkID[4];		// must be "RIFF"
	int ChunkSize;
	char Format[4];			// must be "WAVE"

	char Subchunk1ID[4];	// must be "fmt"
	int Subchunk1Size;		// should be 16
	short AudioFormat;		// should be 1
	short NumChannels;		// should be 1
	int SampleRate;			// we will use 16000
	int ByteRate;			// calculated by SR, NS, B/S
	short BlockAlign;		// calculated
	short BitsPerSample;	// should be 16

	char Subchunk2ID[4];	// must be "data"
	int Subchunk2Size;		// calculated
};

// function declarations
void displayWAVHDR(struct WAVHDR);
void showID(char *, char *);
void displayWAVDATA(short []);
