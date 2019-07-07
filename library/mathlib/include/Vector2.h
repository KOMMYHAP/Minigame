#pragma once

template <typename T>
class Vector2
{
public:
	Vector2() = default;
	Vector2(const Vector2 &) = default;
	Vector2& operator=(const Vector2 &) = default;
	Vector2(Vector2 &&) noexcept = default;
	Vector2& operator=(Vector2 &&) noexcept = default;

	Vector2(T && x, T && y)
		: m_data(make_pair<T, T>(forward<T>(x), forward<T>(y))) {}
	
	const T & X() const { return m_data.first; }
	const T & Y() const { return m_data.second; }
	const pair<T, T> & XY() const { return m_data; }
	
	void SetX(T && x) { m_data.first = forward<T>(x); }
	void SetY(T && y) { m_data.second = forward<T>(y); }
	void SetXY(T && x, T && y) { swap(m_data, make_pair(x, y)); }
	
	Vector2 operator+(const Vector2 & rhs) const;
	Vector2 operator-(const Vector2 & rhs) const;
	Vector2 operator*(T && value) const;
	Vector2 operator/(T && value) const;
	
	void operator+=(const Vector2 & rhs);
	void operator-=(const Vector2 & rhs);
	void operator*=(T && value);
	void operator/=(T && value);
	
	bool operator<(const Vector2 &rhs) const;
	bool operator<=(const Vector2 &rhs) const;
	bool operator==(const Vector2 &rhs) const;
	bool operator>=(const Vector2 &rhs) const;
	bool operator>(const Vector2 &rhs) const;

private:
	pair<T, T>	m_data;
};

template <typename T>
T LengthSqr(const Vector2<T> & vector)
{
	return vector.X() * vector.X() + vector.Y() * vector.Y();	
}

template <typename T>
float Length(const Vector2<T> & vector)
{
	return std::sqrtf(static_cast<float>(LengthSqr(vector)));
}

template <typename T>
Vector2<T> Vector2<T>::operator+(const Vector2& rhs) const
{
	Vector2 temp(*this);
	temp += rhs;
	return temp;
}

template <typename T>
Vector2<T> Vector2<T>::operator-(const Vector2& rhs) const
{
	Vector2 temp(*this);
	temp -= rhs;
	return temp;
}

template <typename T>
Vector2<T> Vector2<T>::operator*(T&& value) const
{
	Vector2 temp(*this);
	temp *= forward<T>(value);
	return temp;
}

template <typename T>
Vector2<T> Vector2<T>::operator/(T&& value) const
{
	Vector2 temp(*this);
	temp /= forward<T>(value);
	return temp;
}

template <typename T>
void Vector2<T>::operator+=(const Vector2& rhs)
{
	SetXY(X() + rhs.X(), Y() + rhs.Y());
}

template <typename T>
void Vector2<T>::operator-=(const Vector2& rhs)
{
	SetXY(X() - rhs.X(), Y() - rhs.Y());
}

template <typename T>
void Vector2<T>::operator*=(T&& value)
{
	SetXY(X() * value, Y() * value);
}

template <typename T>
void Vector2<T>::operator/=(T&& value)
{
	SetXY(X() / value, Y() / value);
}

template <typename T>
bool Vector2<T>::operator<(const Vector2& rhs) const
{
	return X() < rhs.X() && Y() < rhs.Y();
}

template <typename T>
bool Vector2<T>::operator<=(const Vector2& rhs) const
{
	return *this < rhs || *this == rhs;
}

template <typename T>
bool Vector2<T>::operator==(const Vector2& rhs) const
{
	return X() == rhs.X() && Y() == rhs.Y();
}

template <typename T>
bool Vector2<T>::operator>=(const Vector2& rhs) const
{
	return *this > rhs || *this == rhs;
}

template <typename T>
bool Vector2<T>::operator>(const Vector2& rhs) const
{
	return X() > rhs.X() && Y() > rhs.Y();
}

using Vectro2i = Vector2<int>;
using Vectro2f = Vector2<float>;
