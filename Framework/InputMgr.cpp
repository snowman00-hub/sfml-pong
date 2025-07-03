#include "stdafx.h"
#include "InputMgr.h"

std::list<sf::Keyboard::Key> InputMgr::downKeys;
std::list<sf::Keyboard::Key> InputMgr::heldKeys;
std::list<sf::Keyboard::Key> InputMgr::upKeys;

std::vector<int> InputMgr::mouseButtons;

std::unordered_map<Axis, AxisInfo> InputMgr::axisInfoMap;

void InputMgr::Init()
{
	AxisInfo infoH;
	infoH.axis = Axis::Horizontal;
	infoH.positives.push_back(sf::Keyboard::D);
	infoH.positives.push_back(sf::Keyboard::Right);
	infoH.negatives.push_back(sf::Keyboard::A);
	infoH.negatives.push_back(sf::Keyboard::Left);
	axisInfoMap.insert({ Axis::Horizontal ,infoH });

	AxisInfo infoV;
	infoV.axis = Axis::Vertical;
	infoV.positives.push_back(sf::Keyboard::S);
	infoV.positives.push_back(sf::Keyboard::Down);
	infoV.negatives.push_back(sf::Keyboard::W);
	infoV.negatives.push_back(sf::Keyboard::Up);
	axisInfoMap.insert({ Axis::Vertical ,infoV });

	mouseButtons.resize((int)sf::Mouse::ButtonCount);
}

void InputMgr::Clear() 
{
	downKeys.clear();
	upKeys.clear();

	std::fill(mouseButtons.begin(), mouseButtons.end(), 0);
}

void InputMgr::UpdateEvent(const sf::Event& ev) 
{
	for (int i = 0; i < sf::Mouse::ButtonCount; i++)
	{
		if (sf::Mouse::isButtonPressed((sf::Mouse::Button)i))
		{
			mouseButtons[i] = 2;
		}
	}

	switch (ev.type)
	{
	case sf::Event::KeyPressed:
		if (!Contains(heldKeys, ev.key.code))
		{
			downKeys.push_back(ev.key.code);
			heldKeys.push_back(ev.key.code);
		}
		break;
	case sf::Event::KeyReleased:
		Remove(heldKeys, ev.key.code);
		upKeys.push_back(ev.key.code);
		break;
	case sf::Event::MouseButtonPressed:
		mouseButtons[(int)ev.mouseButton.button] = 1;
		break;
	case sf::Event::MouseButtonReleased:
		mouseButtons[(int)ev.mouseButton.button] = 3;
		break;
	}
}

void InputMgr::Update(float dt) 
{

}

bool InputMgr::GetKeyDown(sf::Keyboard::Key key)
{
	return Contains(downKeys, key);
}

bool InputMgr::GetKeyUp(sf::Keyboard::Key key)
{
	return Contains(upKeys, key);
}

bool InputMgr::GetKey(sf::Keyboard::Key key)
{
	return Contains(heldKeys, key);
}

bool InputMgr::Contains(const std::list<sf::Keyboard::Key>& list, sf::Keyboard::Key key)
{
	return std::find(list.begin(), list.end(), key) != list.end();
}

void InputMgr::Remove(std::list<sf::Keyboard::Key>& list, sf::Keyboard::Key key)
{
	list.remove(key);
}

float InputMgr::GetAxisRaw(Axis axis)
{
	auto findIt = axisInfoMap.find(axis);
	if (findIt == axisInfoMap.end())
		return 0.f;

	const AxisInfo& axisInfo = findIt->second;

	auto it = heldKeys.rbegin();
	while (it != heldKeys.rend())
	{
		sf::Keyboard::Key code = *it;
		if (Contains(axisInfo.positives, code))
		{
			return 1.f;
		}
		if (Contains(axisInfo.negatives, code))
		{
			return -1.f;
		}
		++it;
	}

	return 0.0f;
}

float InputMgr::GetAxis(Axis axis)
{
	return 0.0f;
}

bool InputMgr::GetMouseButtonDown(sf::Mouse::Button button)
{
	return mouseButtons[(int)button] == 1;
}

bool InputMgr::GetMouseButtonUp(sf::Mouse::Button button)
{
	return mouseButtons[(int)button] == 3;
}

bool InputMgr::GetMouseButton(sf::Mouse::Button button)
{
	return mouseButtons[(int)button] == 2;
}

sf::Vector2i InputMgr::GetMousePosition()
{
	return sf::Mouse::getPosition();
}

