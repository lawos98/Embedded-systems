#ifndef _AUDIOANALYZER_H
#define _AUDIOANALYZER_H

void micSetup();
bool checkBassDropDetected();
bool checkPeakDetected();
int getOnsetDetected();

#endif
