#pragma once
#include "Validator.h"
#include <string>

template<class T>
class MaxValidator : public Validator<T>
{
public:
	MaxValidator(int max);
	bool check(const T& data) ;

private:
	int m_max;
};

template<class T>
MaxValidator<T>::MaxValidator(int max)
	:Validator<T>("too long name"), m_max(max)
{
}


template<class T>
bool MaxValidator<T>::check(const T & data) 
{
	m_valid = stoi(data).size() <= max;
	return m_valid;
}
template<>
inline bool MaxValidator<std::string>::check(const std::string& data) 
{
	m_valid = data.size() <= m_max;
	return m_valid;
}


