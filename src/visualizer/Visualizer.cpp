#include <WiFiNINA.h>
#include <PDM.h>
#include "Parameters.h"
#include "Visualizer.h"

#define COLOR_CHANNELS 3 
#define MAX_CURSORS 5
#define CENTER_X 0
#define CENTER_Y 0

// Cursor properties
int cursorPos[MAX_CURSORS];
int cursorEnd[MAX_CURSORS];
int cursorSpeed[MAX_CURSORS];
int cursorSize[MAX_CURSORS];
short cursorColor[MAX_CURSORS];
int cursorCount = 0; 

unsigned long cursorLastSpawnTime[MAX_CURSORS] = {0};
const unsigned long cursorTimeToSpawn[MAX_CURSORS] = {0, 2000, 3000};

void getAverageColor(int x1, int y1, int x2, int y2, int* averageColor) {
  long colorSum[COLOR_CHANNELS] = {0, 0, 0};
  int totalPixels = 0;
  
  for(int x=x1; x<=x2; x++){
    for(int y=y1; y<=y2; y++){
      int distX = abs(CENTER_X - x);
      int distY = abs(CENTER_Y - y);
      int radialDistance = sqrt(distX * distX + distY * distY);

      radialDistance = min(radialDistance, VECTOR_SIZE-1);

      int* color = params.predefinedColors[params.colorVector[radialDistance]];

      for(int i=0; i<COLOR_CHANNELS; i++){
        colorSum[i] += color[i];
      }
      totalPixels++;
    }
  }
  
  for(int i=0; i<COLOR_CHANNELS; i++){
    averageColor[i] = colorSum[i] / totalPixels;
  }
}

void addCursor(int type) {
  if(type >= MAX_CURSORS || type <= 0) return;

  if (millis() - cursorLastSpawnTime[type] < cursorTimeToSpawn[type]) return;

  cursorLastSpawnTime[type] = millis();

  if(cursorCount >= MAX_CURSORS) return;

  cursorColor[cursorCount] = type;
  
  if(type == 1) {
    cursorSize[cursorCount] = 3;
    cursorPos[cursorCount] = 0 - cursorSize[cursorCount];
    cursorEnd[cursorCount] = VECTOR_SIZE - 1 + cursorSize[cursorCount];
    cursorSpeed[cursorCount] = 1;
  } else if(type == 2) {
    cursorSize[cursorCount] = 8;
    cursorPos[cursorCount] = VECTOR_SIZE - 1 + cursorSize[cursorCount];
    cursorEnd[cursorCount] = 0 - cursorSize[cursorCount];
    cursorSpeed[cursorCount] = -2;
  }
  cursorCount++;
}

void removeCursor(int index) {
  for(int i=index+1; i<cursorCount; i++) {
    cursorPos[i-1] = cursorPos[i];
    cursorEnd[i-1] = cursorEnd[i];
    cursorSpeed[i-1] = cursorSpeed[i];
    cursorSize[i-1] = cursorSize[i];
    cursorColor[i-1] = cursorColor[i];
  }
  cursorCount--;
}

void updateColors(bool bassDropDetected, bool peakDetected) {
  for(int i=0; i<VECTOR_SIZE; i++) {
    params.colorVector[i] = 0;
  }

  if(peakDetected) addCursor(1);
  if(bassDropDetected) addCursor(2);

  // Update each cursor
  for(int c=0; c<cursorCount; c++) {
    cursorPos[c] += cursorSpeed[c];
    if ((cursorSpeed[c] < 0 && cursorPos[c] <= cursorEnd[c]) ||
    (cursorSpeed[c] > 0 && cursorPos[c] >= cursorEnd[c])) {
        removeCursor(c);
        c--;
        continue;
    }

    // Update colors at cursor positions
    for(int i=0; i<cursorSize[c]; i++) {
      int pos = cursorPos[c] + cursorSpeed[c] + i;
      if(pos<VECTOR_SIZE && pos >= 0)params.colorVector[pos] = cursorColor[c];
    }
  }
}

void visualizersetup() {
  for(int i=0; i<VECTOR_SIZE; i++) {
    params.colorVector[i] = 0;
  }
}

void printColorVector() {
  Serial.print("(");
  for(int i=0; i<VECTOR_SIZE-1; i++) {
    Serial.print(params.colorVector[i]);
    Serial.print(",");
  }
  Serial.print(params.colorVector[VECTOR_SIZE-1]);
  Serial.print(")");
  Serial.println(cursorCount);
}