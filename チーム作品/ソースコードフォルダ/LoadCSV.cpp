#include<stdio.h>			
#define _USE_MATH_DEFINES
#include<math.h>
#include<stdlib.h>

#define MAX_NUM 100	//最大ブロックマス数

FILE*fpCSV;

//int main(void) {
//
//	int LoadCSV[MAX_NUM] = { 0 };
//
//	int i;
//
//	fopen_s(&fpCSV, "StageCSV/MacroTest.csv", "r");
//
//	i = 0;
//
//
//	while (fscanf_s(fpCSV, "%d,", &LoadCSV[i]) != EOF) {
//		i++;
//	}
//
//	fclose(fpCSV);
//
//	return (0);
//
//}

void StorageCSV(const char* FileName)
{
	int LoadCSV[MAX_NUM] = { 0 };

	int i;

	fopen_s(&fpCSV, FileName, "r");

	i = 0;


	while (fscanf_s(fpCSV, "%d,", &LoadCSV[i]) != EOF) {
		i++;
	}

	fclose(fpCSV);

}