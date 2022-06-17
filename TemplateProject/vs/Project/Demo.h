#ifndef DEMO_H
#define DEMO_H

#include "Game.h"
#include "Setting.h"
#include "Texture.h"
#include "Sprite.h"
#include "Music.h"
#include "Sound.h"
#include "Text.h"

namespace Engine {
	class Demo :
		public Engine::Game
	{
	public:
		Demo(Setting* setting);
		~Demo();
		virtual void Init();
		virtual void Update();
		virtual void Render();
	private:
		Texture* ballTexture = NULL;
		Texture* monsterTexture = NULL;
		Texture* dotTexture = NULL;
		Texture* backgroundTexture = NULL;
		Texture* landTexture = NULL;
		Texture* rock1Texture = NULL;
		Texture* rock3Texture = NULL;
		Texture* scoreTexture = NULL;

		Sprite* ballSprite = NULL;
		Sprite* ballSprite1 = NULL;
		Sprite* ballSprite2 = NULL;
		Sprite* monsterSprite = NULL;
		Sprite* dotSprite1 = NULL;
		Sprite* dotSprite2 = NULL;
		Sprite* dotSprite3 = NULL;
		Sprite* dotSprite4 = NULL;
		Sprite* backgroundSprite = NULL;
		Sprite* landSprite = NULL;
		Sprite* rock1Sprite = NULL;
		Sprite* rock3Sprite = NULL;
		Sprite* scoreSprite = NULL;

		Music* music = NULL;;
		Sound* sound = NULL;
		Sound* sscore = NULL;
		Text* text = NULL;
		Text* tscore = NULL;

		unsigned int score = 0.0f;

	};
}
#endif

