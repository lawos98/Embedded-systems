#ifndef main_h
#define main_h

#define NUM_COLORS 3
#define NUM_CHANNELS 3
#define NUM_DEVICES 3
#define NUM_COORD_PARAMS 4
#define VECTOR_SIZE 30

struct Parameters {
  float bassDropThreshold;
  float peakThreshold;
  float onsetThreshold;
  float silenceThreshold;
  int predefinedColors[NUM_COLORS][NUM_CHANNELS];
  String deviceIPs[NUM_DEVICES];
  int deviceLeds[NUM_DEVICES];
  int coordinates[NUM_DEVICES][NUM_COORD_PARAMS];
  short colorVector[VECTOR_SIZE]; 
};

extern Parameters params;

extern const char ssid[];
extern const char pass[];

#endif