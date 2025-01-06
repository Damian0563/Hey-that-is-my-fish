#ifndef FILE_HANDLING_H
#define FILE_HANDLING_H

#include "structs.h"


void ReadFile(Board* board,char* file_name, AutonomousPlayer **players, int* num_players);
void WriteFile(Board* board,char* filename, AutonomousPlayer players[], int num_players);
int interpretValueRead(char* token);
int interpretValueWrite(int value);

#endif