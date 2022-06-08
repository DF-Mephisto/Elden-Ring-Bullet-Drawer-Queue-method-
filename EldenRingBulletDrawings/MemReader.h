#pragma once

#include <Windows.h>
#include <TlHelp32.h>
#include <string>
#include <sstream>
#include <stdexcept>
#include <vector>
#include <iomanip>

#include "Constants.h"
#include "VectorTransformer.h"
#include "POINT3D.h"
#include "Logger.h"

using namespace std;

extern "C"
{
	void spawnBulletProc();
}

class MemReader {
public:
	MemReader();
	~MemReader();

	bool initialize();
	bool getProcessStatus();
	void closeProc();
	float getCharAngle();
	POINT3D getCharPos();
	void spawnBullet(int bulletId, float x, float y, float z, float vectorX, float vectorY, float vectorZ);
	void lockSpawning();
	void unlockSpawning();

private:
	vector<wstring>   processNames;
	wstring chosenProcessName;
	HANDLE    pHandle;
	DWORD	  pID;
	DWORD     moduleSize;
	DWORD64   baseAddress;
	DWORD64	  scriptMemory;
	DWORD64   dataMemory;
	DWORD	  scriptSize;
	DWORD64	  worldChrManAddr;
	DWORD64   instructionAddr;

	DWORD getProcess();
	DWORD64 getModule();
	HANDLE openProc();
	bool readMemory(LPVOID source, LPVOID destination, int size);
	bool writeMemory(LPVOID destination, LPVOID source, int size);
	DWORD64 findSignature(DWORD64 base, DWORD64 searchSize, wstring wsign);
	bool dataCompare(const BYTE* data, const BYTE* sign, const char* mask, int size);
	void getSignBytes(BYTE* aob, vector<wstring>& parsedSign);
	void getMask(char* mask, vector<wstring>& parsedSign);
	DWORD64	alloc(int size);
	void hookMemory();
	void free();
	DWORD getScriptSize(LPVOID script);
	vector<wstring> parseHexString(wstring aob);
	bool validateProcessName(const wchar_t* processName);
};

