#pragma once

class BasicResource
{
public:
	virtual ~BasicResource() = default;
	
	virtual bool LoadFrom(const string& filename) = 0;
	virtual bool IsLoaded() const = 0;
	virtual void Unload() = 0;
};