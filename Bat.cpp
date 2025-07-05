#include "stdafx.h"
#include "Bat.h"

Bat::Bat(const std::string& name)
	: GameObject(name)
{
}

void Bat::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	shape.setPosition(pos);
}

void Bat::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	shape.setRotation(rot);
}

void Bat::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	shape.setScale(s);
}

void Bat::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	shape.setOrigin(o);
}

void Bat::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	if (preset != Origins::Custom)
	{
		Utils::SetOrigin(shape, preset);
	}
}

void Bat::Init()
{
	if (soloMode)
	{
		shape.setSize({ 100.f,5.f });
		shape.setFillColor(sf::Color::White);
		SetOrigin(Origins::TC);
	}
	else if (Left)
	{
		shape.setSize({ 5.f,100.f });
		shape.setFillColor(sf::Color::White);
		SetOrigin(Origins::MR);
	}
	else
	{
		shape.setSize({ 5.f,100.f });
		shape.setFillColor(sf::Color::White);
		SetOrigin(Origins::ML);
	}
}

void Bat::Release()
{
}

void Bat::Reset()
{
	sf::FloatRect bounds = FRAMEWORK.GetWindowBounds();
	sf::Vector2f size = shape.getSize();

	if (soloMode)
	{
		SetPosition({ bounds.width * 0.5f, bounds.height - 20.f });
		minX = bounds.left + size.x * 0.5f;
		maxX = (bounds.left + bounds.width) - size.x * 0.5f;
	}
	else if (Left)
	{
		SetPosition({ 20.f, bounds.height * 0.5f });
		minY = bounds.top + size.y * 0.5f;
		maxY = (bounds.top + bounds.height) - size.y * 0.5f;
	}
	else
	{
		SetPosition({ bounds.width - 20.f, bounds.height * 0.5f });
		minY = bounds.top + size.y * 0.5f;
		maxY = (bounds.top + bounds.height) - size.y * 0.5f;
	}
}

void Bat::Update(float dt)
{
	if (soloMode)
	{
		direction.x = InputMgr::GetAxis(Axis::Horizontal);
		sf::Vector2f pos = GetPosition() + direction * speed * dt;
		pos.x = Utils::Clamp(pos.x, minX, maxX);
		SetPosition(pos);
	}
	else if (Left)
	{
		direction.y = InputMgr::GetAxis(Axis::WS);
		sf::Vector2f pos = GetPosition() + direction * speed * dt;
		pos.y = Utils::Clamp(pos.y, minY, maxY);
		SetPosition(pos);
	}
	else
	{
		direction.y = InputMgr::GetAxis(Axis::UpDownArrows);
		sf::Vector2f pos = GetPosition() + direction * speed * dt;
		pos.y = Utils::Clamp(pos.y, minY, maxY);
		SetPosition(pos);
	}
}

void Bat::Draw(sf::RenderWindow& window)
{
	window.draw(shape);
}