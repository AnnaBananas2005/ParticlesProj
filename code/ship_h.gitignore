#pragma once
//Space ship pack:
//https://foozlecc.itch.io/void-main-ship

#include <SFML/Graphics.hpp>
using namespace sf;

class Ship {
private:
	const float START_SPEED = 100;
	const float START_HEALTH = 100;

	Vector2f m_Position;
	Sprite m_Sprite;
	Texture m_Texture;
	Vector2f m_Resolution;
	IntRect m_Arena;
	bool m_UpPressed;
	bool m_DownPressed;
	bool m_LeftPressed;
	bool m_RightPressed;

	int m_Health;
	int m_MaxHealth;
	Time m_LastHit;
	float m_Speed;

public:
	Ship();
	void spawn(IntRect spaceArena, Vector2f resolution); //space arena might get removed
	FloatRect getPosition();
	Vector2f getCenter();
	float getRotation();
	Sprite getSprite();

	void update(float elapsedTime, Vector2i mousePosition);

};
