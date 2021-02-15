// CodeExperiment.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <chrono>
#include <utility>
#include <algorithm>
#include <random>
#include "Windows.h"

class iTime {
public:
	///Time it took to render previous frame
	float DeltaTime;

	iTime() {
		DeltaTime = 1;
		timeScale = 1000000000;
	}

	void SetTimeScale(float t) {
		timeScale = 1000000000 / t;
	}

	void Start() {
		t1 = std::chrono::steady_clock::now();
	}
	void End() {
		t2 = std::chrono::steady_clock::now();
		DeltaTime = std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
		DeltaTime /= timeScale;
	}
private:
	std::chrono::time_point<std::chrono::steady_clock> t1, t2;
	int timeScale;
};

using namespace std;
int main()
{
	
	
	
	iTime time;

	time.Start();
	vector<int> testData;
	testData.reserve(100000000);
	time.End();
	cout << "vector allocation time: " << time.DeltaTime << "\n";

	time.Start();
	Sleep(100);
	time.End();
	
	time.Start();
	int* testData2;
	testData2 = (int*)malloc(sizeof(int) * 100000000);
	
	cout << "array allocation time: " << time.DeltaTime << "\n";
	time.End();

	time.Start();
	Sleep(100);
	time.End();
	
	time.Start();
    for(int i = 0; i < 100000000; ++i)
    {
		testData.push_back(rand());
    }
	cout << "vector insertion time: " << time.DeltaTime << "\n";
	time.End();

	time.Start();
	Sleep(100);
	time.End();
	
	time.Start();
	for (int i = 0; i < 100000000; ++i)
	{
		*(testData2+i) = rand();
	}
	cout << "array insertion time: " << time.DeltaTime << "\n";
	time.End();

	free(testData2);
}