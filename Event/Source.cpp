#include <iostream>
#include <Windows.h>
#include <thread>
#include <process.h>
#include <tchar.h>

const int size = 5;
int arr[size];
int sum = 0;

HANDLE ev;


void input(void*) {
	ResetEvent(ev);
	for (int i = 0; i < size; ++i) {
		std::cin >> arr[i];
	}
	PulseEvent(ev);
}

void calculate_sum(void*) {
	WaitForSingleObject(ev, INFINITE);
	for (int i = 0; i < size; ++i) {
		sum += arr[i];
	}
	std::cout << sum << std::endl;
	SetEvent(ev);
}




int _tmain() {

	ev = CreateEvent(NULL, false, false, L"event1");

	_beginthread(input, 0, NULL);
	_beginthread(calculate_sum, 0, NULL);
	Sleep(5000);


	return 0;
}