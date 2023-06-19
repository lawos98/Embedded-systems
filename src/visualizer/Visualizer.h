#ifndef _VIZUALIZER_H
#define _VIZUALIZER_H

void printColorVector();
void visualizersetup();
void updateColors(bool bassDropDetected, bool peakDetected);
void getAverageColor(int x1, int y1, int x2, int y2, int* averageColor);

#endif