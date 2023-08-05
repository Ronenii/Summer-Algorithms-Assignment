#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <string>
using namespace std;

class invalid_input_exception
{
	string message;

public:
	invalid_input_exception()
	{
		message = "invalid input";
	}

	char const* what()const
	{
		return message.c_str();
	}
};

