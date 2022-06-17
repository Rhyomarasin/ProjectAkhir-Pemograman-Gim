#include "Demo.h"

using namespace Engine;

Demo::Demo(Setting* setting) :Game(setting)
{

}


Demo::~Demo()
{
	delete backgroundTexture;
	delete rock1Texture;
	delete rock3Texture;
	delete landTexture;
	delete scoreTexture;
	delete ballTexture;
	delete monsterTexture;
	delete dotTexture;
	delete backgroundSprite;
	delete rock1Sprite;
	delete rock3Sprite;
	delete landSprite;
	delete scoreSprite;
	delete ballSprite;
	delete ballSprite1;
	delete ballSprite2;
	delete monsterSprite;
	delete dotSprite1;
	delete dotSprite2;
	delete dotSprite3;
	delete dotSprite4;
	delete music;
	delete sound;
	delete sscore;
	delete text;
	delete tscore;
}

void Demo::Init()
{
	backgroundTexture = new Texture("back 4x3.png");
	backgroundSprite = new Sprite(backgroundTexture, defaultSpriteShader, defaultQuad);
	backgroundSprite->SetRotation(0);
	backgroundSprite->SetPosition((setting->screenWidth * 0.5f) - (backgroundSprite->GetScaleWidth() * 0.5f),
		(setting->screenHeight * 0.5f) - (backgroundSprite->GetScaleHeight() * 0.5f));
	backgroundSprite->SetScale(1);

	landTexture = new Texture("land.png");
	landSprite = new Sprite(landTexture, defaultSpriteShader, defaultQuad);
	landSprite->SetRotation(0);
	landSprite->SetPosition(-80,-13);
	landSprite->SetScale(1);
	landSprite->SetBoundingBoxSize(landSprite->GetScaleWidth() - (100 * landSprite->GetScale()),
		landSprite->GetScaleHeight() - (18 * landSprite->GetScale()));

	rock1Texture = new Texture("rock1.png");
	rock1Sprite = new Sprite(rock1Texture, defaultSpriteShader, defaultQuad);
	rock1Sprite->SetRotation(0);
	rock1Sprite->SetPosition(645, 213);
	rock1Sprite->SetScale(1);
	rock1Sprite->SetBoundingBoxSize(rock1Sprite->GetScaleWidth() - (50 * rock1Sprite->GetScale()),
		rock1Sprite->GetScaleHeight() - (15 * rock1Sprite->GetScale()));

	rock3Texture = new Texture("rock3.png");
	rock3Sprite = new Sprite(rock3Texture, defaultSpriteShader, defaultQuad);
	rock3Sprite->SetRotation(0);
	rock3Sprite->SetPosition(232, 297);
	rock3Sprite->SetScale(1);
	rock3Sprite->SetBoundingBoxSize(rock3Sprite->GetScaleWidth() - (50 * rock3Sprite->GetScale()),
		rock3Sprite->GetScaleHeight() - (11 * rock3Sprite->GetScale()));

	scoreTexture = new Texture("btn.png");
	scoreSprite = new Sprite(scoreTexture, defaultSpriteShader, defaultQuad);
	scoreSprite->SetRotation(0);
	scoreSprite->SetScale(0.5);
	scoreSprite->SetPosition((setting->screenWidth * 0.5f) - (scoreSprite->GetScaleWidth() * 0.5f), 
		setting->screenHeight - scoreSprite->GetScaleHeight() - 10);

	ballTexture = new Texture("ball.png");
	ballSprite = new Sprite(ballTexture, defaultSpriteShader, defaultQuad);
	ballSprite->SetPosition( 350 , 547);
	ballSprite->SetRotation(0);
	ballSprite->SetScale(1);

	ballSprite1 = new Sprite(ballTexture, defaultSpriteShader, defaultQuad);
	ballSprite1->SetPosition(460, 190);
	ballSprite1->SetRotation(0);
	ballSprite1->SetScale(1);

	ballSprite2 = new Sprite(ballTexture, defaultSpriteShader, defaultQuad);
	ballSprite2->SetPosition(300, 410);
	ballSprite2->SetRotation(0);
	ballSprite2->SetScale(1);


	// a monster spritesheet has 8 cols and 2 rows (total frames = 8x2 = 16 frames)
	monsterTexture = new Texture("fox.png");
	monsterSprite = new Sprite(monsterTexture, defaultSpriteShader, defaultQuad);
	// Set monster sprite position 
	// 0,0 is at bottom left of the screen and width, height is at top right
	monsterSprite->SetPosition(50, 140);
	// set num cols in spritesheet
	monsterSprite->SetNumXFrames(8);
	// set num rows in spritesheet
	monsterSprite->SetNumYFrames(2);
	// Set animation speed more duration the speed will become slower
	monsterSprite->SetAnimationDuration(85);
	monsterSprite->SetScale(0.2f);
	// Add Animation name, start frame index, end frame index
	monsterSprite->AddAnimation("idle", 0, 7);
	monsterSprite->AddAnimation("walk", 8, 15);
	// If frame size / sprite size is contain blank space or padding then you must resize the bounding box
	// or collision shape to improve collision detection accuracy
	monsterSprite->SetBoundingBoxSize(monsterSprite->GetScaleWidth() - (250 * monsterSprite->GetScale()),
		monsterSprite->GetScaleHeight() - (4 * monsterSprite->GetScale()));

	// This dot sprite is for visual debugging (to see the actual bounding box) 
	dotTexture = new Texture("dot.png");
	dotSprite1 = new Sprite(dotTexture, defaultSpriteShader, defaultQuad);
	dotSprite2 = new Sprite(dotTexture, defaultSpriteShader, defaultQuad);
	dotSprite3 = new Sprite(dotTexture, defaultSpriteShader, defaultQuad);
	dotSprite4 = new Sprite(dotTexture, defaultSpriteShader, defaultQuad);

	// Add input mapping 
	inputManager->AddInputMapping("Move Up", SDLK_w);
	inputManager->AddInputMapping("Move Down", SDLK_s);
	inputManager->AddInputMapping("Move Right", SDLK_d);
	inputManager->AddInputMapping("Move Left", SDLK_a);
	inputManager->AddInputMapping("Quit", SDLK_ESCAPE);

	// Playing music
	music = new Music("Lost-Jungle.ogg");
	music->SetVolume(30);
	music->Play(true);

	sound = new Sound("Running-on-Gravel.wav");
	sound->SetVolume(80);

	sscore = new Sound("Ting.wav");
	sscore->SetVolume(100);

	text = new Text("KBCloudyDay.ttf", 16, defaultTextShader);
	text->SetScale(1.0f);
	text->SetColor(255, 255, 255);
	text->SetPosition(((setting->screenWidth * 0.5f) - (text->GetFontSize() * text->GetScale())), 
		(text->GetFontSize() * text->GetScale()));

	tscore = new Text("KBCloudyDay.ttf", 32 , defaultTextShader);
	tscore->SetScale(1.0f);
	tscore->SetColor(255, 255, 255);
	tscore->SetPosition(400 , 555);

	//Set the background color
	SetBackgroundColor(23, 23, 23);

}

void Demo::Update()
{
	// If user press "Quit" key then exit
	if (inputManager->IsKeyReleased("Quit")) {
		state = State::EXIT;
		return;
	}

	// Move monster sprite using keyboard
	monsterSprite->PlayAnim("idle");
	float xspeed = 0, yspeed = 0;
	vec2 oldMonsterPos = monsterSprite->GetPosition();
	
	if (inputManager->IsKeyPressed("Move Up")) {
		yspeed = 0.075f;
		monsterSprite->PlayAnim("walk");
		monsterSprite->SetPosition(oldMonsterPos.x,
			oldMonsterPos.y + yspeed * GetGameTime());
		if (!sound->IsPlaying())
			sound->Play(false);
	}

	if (inputManager->IsKeyPressed("Move Down")) {
		yspeed = -0.075f;
		monsterSprite->PlayAnim("walk");
		monsterSprite->SetPosition(oldMonsterPos.x,
			oldMonsterPos.y + yspeed * GetGameTime());
		if (!sound->IsPlaying())
			sound->Play(false);
	}

	if (inputManager->IsKeyPressed("Move Right")) {
		xspeed = 0.075f;
		monsterSprite->PlayAnim("walk");
		monsterSprite->SetPosition(oldMonsterPos.x + xspeed * GetGameTime(),
			oldMonsterPos.y);
		monsterSprite->SetFlipHorizontal(false);
		if (!sound->IsPlaying())
			sound->Play(false);
	}

	if (inputManager->IsKeyPressed("Move Left")) {
		xspeed = -0.075f;
		monsterSprite->PlayAnim("walk");
		monsterSprite->SetPosition(oldMonsterPos.x + xspeed * GetGameTime(),
			oldMonsterPos.y);
		monsterSprite->SetFlipHorizontal(true);
		if (!sound->IsPlaying())
			sound->Play(false);
	}

	// Update monster sprite animation
	monsterSprite->Update(GetGameTime());
	
	BoundingBox* bb = monsterSprite->GetBoundingBox();
	if (ballSprite1->GetBoundingBox()->CollideWith(bb)) {
		//revert position if collided
		score = score +1; 
		sscore->Play(false);
		ballSprite1->SetPosition(1000, 1000);
	}
	if (ballSprite2->GetBoundingBox()->CollideWith(bb)) {
		//revert position if collided
		score = score +1;
		sscore->Play(false);
		ballSprite2->SetPosition(1000, 1000);
	}

	//bool isCollided = ballSprite->GetBoundingBox()->CollideWith(bb);
	//text->SetText((isCollided ? "[Collision = Yes]" : "[Collision = No]") +
	//	("[FPS = " + to_string(currentFrameRate)) +
	//	"] Press W-A-S-D-Q-E to Move & Rotate Crate and Right-Left to Move Monster");

	text->SetText(("[FPS = " + to_string(currentFrameRate)) + "]");
	tscore->SetText("= " + to_string(score));


	
	if (landSprite->GetBoundingBox()->CollideWith(bb)) {
		//revert position if collided
		monsterSprite->SetPosition(oldMonsterPos.x,
			oldMonsterPos.y);
	}
	if (rock1Sprite->GetBoundingBox()->CollideWith(bb)) {
		//revert position if collided
		monsterSprite->SetPosition(oldMonsterPos.x,
			oldMonsterPos.y);
	}
	if (rock3Sprite->GetBoundingBox()->CollideWith(bb)) {
		//revert position if collided
		monsterSprite->SetPosition(oldMonsterPos.x,
			oldMonsterPos.y);
	}


	if (oldMonsterPos.x + monsterSprite->GetScaleWidth() > setting->screenWidth) {
		monsterSprite->SetPosition(oldMonsterPos.x - 1 ,
			oldMonsterPos.y);
	}
	if (oldMonsterPos.x < 0 ) {
		monsterSprite->SetPosition(oldMonsterPos.x + 1,
			oldMonsterPos.y);
	}
	if (oldMonsterPos.y + monsterSprite->GetScaleHeight() > setting->screenHeight) {
		monsterSprite->SetPosition(oldMonsterPos.x,
			oldMonsterPos.y - 1);
	}
	if (oldMonsterPos.y < 0) {
		monsterSprite->SetPosition(oldMonsterPos.x,
			oldMonsterPos.y + 1);
	}

	
	//Render shape for debug
	dotSprite1->SetPosition(bb->GetVertices()[0].x - (0.5f * dotSprite1->GetScaleWidth()), 
		bb->GetVertices()[0].y - (0.5f * dotSprite1->GetScaleHeight()));
	dotSprite2->SetPosition(bb->GetVertices()[1].x - (0.5f * dotSprite2->GetScaleWidth()), 
		bb->GetVertices()[1].y - (0.5f * dotSprite2->GetScaleHeight()));
	dotSprite3->SetPosition(bb->GetVertices()[2].x - (0.5f * dotSprite3->GetScaleWidth()), 
		bb->GetVertices()[2].y - (0.5f * dotSprite3->GetScaleHeight()));
	dotSprite4->SetPosition(bb->GetVertices()[3].x - (0.5f * dotSprite4->GetScaleWidth()), 
		bb->GetVertices()[3].y - (0.5f * dotSprite3->GetScaleHeight()));



}

void Demo::Render()
{
	backgroundSprite->Draw();
	landSprite->Draw();
	rock1Sprite->Draw();
	rock3Sprite->Draw();
	ballSprite1->Draw();
	ballSprite2->Draw();
	ballSprite->Draw();
	monsterSprite->Draw();
	//dotSprite1->Draw();
	//dotSprite2->Draw();
	//dotSprite3->Draw();
	//dotSprite4->Draw();
	scoreSprite->Draw();
	ballSprite->Draw();
	text->Draw();
	tscore->Draw();
}


int main(int argc, char** argv) {
	Setting* setting = new Setting();
	setting->windowTitle = "The Fox Game";
	setting->screenWidth = 800;
	setting->screenHeight = 600;
	setting->windowFlag = WindowFlag::WINDOWED;
	Game* game = new Demo(setting);
	game->Run();
	delete setting;
	delete game;

	return 0;
}
