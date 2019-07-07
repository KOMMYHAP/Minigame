#pragma once

class SingletonBase
{
public:
	virtual ~SingletonBase() = default;
};

template <typename T>
class Singleton : public SingletonBase
{
public:
	static T * Instance();

private:
	static T*	 m_object;
};

template <typename T> T * Singleton<T>::m_object = nullptr;

template <typename T>
T* Singleton<T>::Instance()
{
	if (!m_object)
	{
		m_object = new T();
	}
	return m_object;
}