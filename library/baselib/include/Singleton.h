#pragma once

template <typename T>
class Singleton
{
public:
	static T * instance() { static T t; return &t; }
};