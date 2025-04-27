#pragma once
#include <SFML/Graphics.hpp>
#include "ResourceManager.h"
#include "FieldBase.h"
#include <iostream>
#include <sstream>
#include <string>

class BookingForm;

template <typename ValidatorT, typename TypeT>
class Field : public FieldBase
{
public:
	Field(int& yOffset, BookingForm* form);

	virtual std::string getString() const override;
	virtual bool validate() const override;
	virtual std::string getError() const override { return ValidatorT::error(); };

private:
	BookingForm* m_form;
};

//-----------------------------------------------------------------------------

template <typename ValidatorT, typename TypeT>
Field<ValidatorT, TypeT>::Field(int& yOffset, BookingForm* form)
	: m_form(form)
{
	m_rect.setPosition(sf::Vector2f(250, yOffset - 5));
	m_rect.setFillColor(sf::Color::White);
	m_rect.setOutlineThickness(2);
	m_rect.setOutlineColor(sf::Color(160, 160, 160));
	yOffset += 50;
}

//-----------------------------------------------------------------------------

template <typename ValidatorT, typename TypeT>
std::string Field<ValidatorT, TypeT>::getString() const
{
	std::string temp = m_label;
	return temp;
}

//-----------------------------------------------------------------------------

template <typename ValidatorT, typename TypeT>
bool Field<ValidatorT, TypeT>::validate() const
{
   std::istringstream iss(m_label);
   TypeT type;

   // check if string first
   if constexpr (std::is_same<TypeT, std::string>::value) std::getline(iss, type);
   else iss >> type;

   return ValidatorT::validate(type, m_form);
}