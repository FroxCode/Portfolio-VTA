#include "Game.h"
Game::Game()
{
	pause = false;
	quit = false;
	
	
}


Game::~Game()
{
	Mix_FreeMusic(music_Menu);
	Mix_FreeMusic(music_Boss);
	Mix_FreeMusic(music_Game);
}

bool Game::init() {

	gameState.currentState = gameStates::START;
	SDL_Init(SDL_INIT_EVERYTHING);
	//Initialises SDL Image to use PNGs
	if (!(IMG_Init(IMG_INIT_PNG)))
	{
		std::cout << "Error : PNG Did not load";
	}



	SDL_Init(TTF_Init());
	srand(time(NULL));
	SDL_Point winSize = { 1280,704 };
	b = std::make_shared<std::vector<std::shared_ptr<Bullet>>>(bullets);
	controller = new InputController();
	controller->Init();
	window = SDL_CreateWindow("Velvet Thunder: Arcade", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, winSize.x, winSize.y, 0);
	icon = IMG_Load("assets/icon.png");
	SDL_SetWindowIcon(window, icon);
	sdl_renderer = SDL_CreateRenderer(window, -1, 0);
	SDL_SetRenderDrawColor(sdl_renderer, 255, 255, 255, 255);

	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
	{
		std::cout << "Error : SDL_mixer Did not load";
	}




	music_Menu = Mix_LoadMUS("assets/music/VelvetThunder.wav");
	music_Game= Mix_LoadMUS("assets/music/Green.wav");
	music_Boss = Mix_LoadMUS("assets/music/Green_Amped.wav");





	reviveMe.setName("reviveMe", sdl_renderer);
	firstKill.setName("firstKill", sdl_renderer);
	newRoom.setName("newRoom", sdl_renderer);
	bossRoom.setName("bossRoom", sdl_renderer);
	useBoost.setName("useBoost", sdl_renderer);
	newWeapon.setName("newWeapon", sdl_renderer);
	noDrop.setName("noDrop", sdl_renderer);
	velvetThunder.setName("velvetThunder", sdl_renderer);
	deadEnd.setName("deadEnd", sdl_renderer);
	levelUp.setName("levelUp", sdl_renderer);

	achievementList.Attach(&reviveMe);
	achievementList.Attach(&firstKill);
	achievementList.Attach(&newRoom);
	achievementList.Attach(&bossRoom);
	achievementList.Attach(&useBoost);
	achievementList.Attach(&newWeapon);
	achievementList.Attach(&noDrop);
	achievementList.Attach(&velvetThunder);
	achievementList.Attach(&deadEnd);
	achievementList.Attach(&levelUp);



	map = new MapGeneration(100, 100, 4, 4);
	map->generate();
	world = new Grid(20, 11);
	world->initialise(map->room, sdl_renderer);

	/*Entities Setup*/
	player = new Entity("Player");
	ally = new Entity("Ally");
	boss = new Entity("Boss");


	enemyPath = "assets/enemy1.png";
	playerPath = "assets/player_deagle.png";
	allyPath = "assets/ally.png";
	bossPath = "assets/boss_p1.png";
	winScreen = IMG_LoadTexture(sdl_renderer, "assets/states/win.png");
	deathScreen = IMG_LoadTexture(sdl_renderer, "assets/states/dead.png");

	std::string onlinePlayerPath = "assets/player_deagle.png";
	player->addComponent(new HealthComponent());
	player->addComponent(new PositionComponent());
	player->addComponent(new ControlComponent());
	player->addComponent(new FiringComponent());
	player->addComponent(new GraphicsComponent(playerPath, sdl_renderer));
	player->addComponent(new StatsComponent());
	player->addComponent(new ExperienceComponent());
	//static_cast<HealthComponent*>(player->getComponents().at(0))->setHealth(10000);
	playerPositionComponent = static_cast<PositionComponent*>(player->getComponents().at(1));
	playerPositionComponent->setPosition(SDL_Point() = { 100,100 });
	
	onlineSystem.addEntity(*player);
	for (int i = 0; i < 3; i++)
	{
		onlinePlayers.push_back(new Entity("OnlinePlayer"));
		onlinePlayers.at(i)->addComponent(new PositionComponent());
		onlinePlayers.at(i)->addComponent(new HealthComponent());
		onlinePlayers.at(i)->addComponent(new FiringComponent());
		onlinePlayers.at(i)->addComponent(new OnlineComponent());
		onlinePlayers.at(i)->addComponent(new GraphicsComponent(onlinePlayerPath , sdl_renderer));
		onlineSystem.addEntity(*onlinePlayers.at(i));
	}



	ally->addComponent(new HealthComponent());
	ally->addComponent(new PositionComponent());
	ally->addComponent(new FiringComponent("shotgun"));
	ally->addComponent(new GraphicsComponent(allyPath, sdl_renderer));
	ally->addComponent(new StatsComponent());
	allyPositionComponent = static_cast<PositionComponent*>(ally->getComponents().at(1));
	allyPositionComponent->setPosition(SDL_Point() = { 200,100 });
	allyStatsComponent = static_cast<StatsComponent*>(ally->getComponents().at(4));

	boss->addComponent(new HealthComponent());
	boss->addComponent(new PositionComponent());
	boss->addComponent(new FiringComponent("ak"));
	boss->addComponent(new GraphicsComponent(bossPath, sdl_renderer));
	boss->addComponent(new StatsComponent());
	bossPositionComponent = static_cast<PositionComponent*>(boss->getComponents().at(1));
	bossPositionComponent->setPosition(SDL_Point() = { 800,350 });
	bossHealthComponent = static_cast<HealthComponent*>(boss->getComponents().at(0));
	bossHealthComponent->setMaxHealth(1000);
	bossHealthComponent->setHealth(1000);


	experienceComponent = static_cast<ExperienceComponent*>(player->getComponents().at(6));
	playerStatsComponent = static_cast<StatsComponent*>(player->getComponents().at(5));
	experienceComponent->loadExpTable();
	xp = experienceComponent->getExp();
	experienceComponent->setLevel(0);
	m_lvl = experienceComponent->getLevel();
	experienceComponent->setNextLevelCap();
	maxTemp = experienceComponent->getMaxExp();

	SDL_Point p;
	p.x = 800;
	p.y = 100;
	enemyPool = new	EnemyTypes();

	spawnPoints.push_back(position1);
	spawnPoints.push_back(position2);
	spawnPoints.push_back(position3);
	spawnPoints.push_back(position4);
	spawnPoints.push_back(position5);
	spawnPoints.push_back(position6);

	spawnEnemies();
	if (enemyEntities.size() == 0)
	{
		doorsLocked = false;
	}
	else
	{
		//oorsLocked = true;
	}

	/*Systems setup*/
	controlSystem.addEntity(*player);
	controlSystem.addBullets(b);

	onlineSystem.addBullets(b);
	controlSystem.onlineSystem = &onlineSystem;

	aiSystem.addEntity(*player);
	aiSystem.addEntity(*ally);
	aiSystem.addBullet(b);
	spawnEnemies();

	graphicsSystem.addEntity(*player);
	graphicsSystem.addEntity(*ally);
	for (int i = 0; i < 3; i++)
	{
		graphicsSystem.addEntity(*onlinePlayers.at(i));
	}

	m_hud = std::make_shared<HUD>(hud);
	m_hud->initialise(sdl_renderer, { 0, 0 });
	m_hud->updateHealthbarPosition(allyPositionComponent->getPosition().x, allyPositionComponent->getPosition().y);

	graphicsSystem.getHUD(m_hud);
	controlSystem.getHUD(m_hud);

	m_startScreen = std::make_shared<startScreen>(start);
	m_startScreen->intialise(sdl_renderer);

	m_optionsScreen = std::make_shared<optionsScreen>(options);
	m_optionsScreen->intialise(sdl_renderer);

	m_multiplayerScreen = std::make_shared<multiplayerScreen>(multiplayer);
	m_multiplayerScreen->intialise(sdl_renderer);

	m_statsScreen = std::make_shared<statScreen>(stats);
	m_statsScreen->intialise(sdl_renderer);

	controlSystem.getHUD(m_hud);
	controlSystem.getStartScreen(m_startScreen);
	controlSystem.getOptionsScreen(m_optionsScreen);
	controlSystem.getMultiplayerScreen(m_multiplayerScreen);
	controlSystem.getStatsScreen(m_statsScreen);
	fsm = new FSM();
	fsm->initialise( static_cast<GraphicsComponent*>( player->getComponents().at(4) ) );

	for (int k = 0; k < ally->getComponents().size(); k++)
	{
		if (ally->getComponents().at(k)->getID() == "Health")
		{
			static_cast<HealthComponent*>(ally->getComponents().at(k))->setHealth(0);
			static_cast<HealthComponent*>(ally->getComponents().at(k))->setAlive(false);
		}
	}

	for (int i = 0; i < 10; i++)
	{
		achievements.push_back(false);
	}

	a = std::make_shared<std::vector<bool>>(achievements);
	controlSystem.getAch(a);

	fpsTimer.start();
	return true;
}

void Game::destroy()
{
}

//** calls update on all game entities*/
void Game::update()
{
	if (gameState.currentState == gameStates::START)
	{
		controlSystem.update(e, sdl_renderer, gameState);
	}

	if (gameState.currentState == gameStates::OPTIONS)
	{
		controlSystem.update(e, sdl_renderer, gameState);
	}
	if (gameState.currentState == gameStates::MULTIPLAYER)
	{
		switch (gameState.mpState)
		{
		case gameStates::MP_LOBBY:
			if (firstTimeSetup)
			{
				firstTimeSetup = false;
				world = new Grid(20, 11);
				world->initialise(1, sdl_renderer);
			}
			if (!isOnline)
			{
				std::string tempIp;
				std::cout << "Enter IP Adress: ";
				std::cin >> tempIp;
				//tempIp = "149.153.106.163";
				int tempPort;
				std::cout << "Enter Port: ";
				std::cin >> tempPort;
				//tempPort = 5050;
				onlineSystem.init(tempIp, tempPort);
				isOnline = true;
			}
			onlineSystem.update(sdl_renderer, gameState);
			controlSystem.update(e, sdl_renderer, gameState);
			break;
		case gameStates::MP_PLAYING:
			onlineSystem.update(sdl_renderer, gameState);
			controlSystem.update(e, sdl_renderer, gameState);

			for (int i = 0; i < b->size(); i++)
			{
				if (b->at(i)->isAlive)
				{
					b->at(i)->update();
				}
				else
				{
					b->at(i) = nullptr;
					b->erase(b->begin() + i);
				}
			}

			checkCollision();
			break;
		case gameStates::MP_GAMEOVER:
			break;
		default:
			break;
		}
	}


	else if (gameState.currentState == gameStates::GAME)
	{
		aiSystem.update(sdl_renderer);
		controlSystem.update(e, sdl_renderer, gameState);
		if (experienceComponent->getExp() > experienceComponent->getMaxExp())
		{
			experienceComponent->incLevel();
			experienceComponent->setExp(experienceComponent->getExp() - experienceComponent->getMaxExp());
			experienceComponent->setNextLevelCap();
			m_hud->updateLevel(experienceComponent->getLevel());
			playerStatsComponent->levelUp();
			allyStatsComponent->levelUp();
			a->at(9) = true;
			std::cout << a->at(9);


		}
		m_hud->updateExperienceBar(experienceComponent->getExp(), experienceComponent->getMaxExp());
		m_hud->updateHealthbarPosition(allyPositionComponent->getPosition().x, allyPositionComponent->getPosition().y);
		checkCollision();
		
		for (int i = 0; i < b->size(); i++)
		{
			if (b->at(i)->isAlive)
			{
				b->at(i)->update();
			}
			else
			{
				b->at(i) = nullptr;
				b->erase(b->begin() + i);
			}
		}

		if (m_statsScreen->getDisplay())
		{
			m_statsScreen->updateStats(sdl_renderer, playerStatsComponent->getHealth() , playerStatsComponent->getAttack(), playerStatsComponent->getAgility(), playerStatsComponent->getDefense());
		}
	}
	else if (gameState.currentState == gameStates::GAMEOVER)
	{
		controlSystem.update(e, sdl_renderer, gameState);
	}

	if (gameState.currentState != gameState.lastState)
	{
		if (gameState.currentState == gameStates::START && gameState.lastState != gameStates::OPTIONS)
		{
			Mix_HaltMusic();
			Mix_PlayMusic(music_Menu, -1);
			if (gameState.lastState == gameStates::GAMEOVER)
			{
					//restart?
				
			}
		}
		if (gameState.currentState == gameStates::GAME && gameState.lastState == gameStates::START)
		{
			Mix_HaltMusic();
			Mix_PlayMusic(music_Game, -1);
		}
		else if (gameState.currentState == gameStates::GAME && m_hud->theBossIsHere)
		{
			if (startBossMusic)
			{
				startBossMusic = false;
				Mix_HaltMusic();
				Mix_PlayMusic(music_Game, -1);
			}
		}
	}
	gameState.lastState = gameState.currentState;
}

//** calls render on all game entities*/

void Game::render()
{

	SDL_SetRenderDrawColor(sdl_renderer, 0, 0, 0, 255);
	SDL_SetRenderDrawBlendMode(sdl_renderer, SDL_BLENDMODE_BLEND);
	SDL_RenderClear(sdl_renderer);
	if (gameState.currentState == gameStates::START)
	{
		m_startScreen->Render(sdl_renderer);
	}
	else if (gameState.currentState == gameStates::GAME)
	{
		world->render(sdl_renderer);
		for (int i = 0; i < b->size(); i++)
		{
			if (b->at(i)->isAlive)
			{
				b->at(i)->render(sdl_renderer);
			}
		}
		for (int i = 0; i < droppedItems.size(); i++)
		{
			droppedItems.at(i)->render(sdl_renderer);
		}
		graphicsSystem.update(sdl_renderer, gameState);

		m_statsScreen->Render(sdl_renderer);
		achievementList.setAchievement(a, sdl_renderer);
		m_statsScreen->Render(sdl_renderer);
	}

	else if (gameState.currentState == gameStates::OPTIONS)
	{
		m_optionsScreen->Render(sdl_renderer);
	}

	else if (gameState.currentState == gameStates::MULTIPLAYER)
	{
		switch (gameState.mpState)
		{
		case gameStates::MP_LOBBY:
			m_multiplayerScreen->setMyNumber(onlineSystem.getMyPlayerNumber());
			m_multiplayerScreen->setPlayerCount(onlineSystem.getPlayerCount());
			m_multiplayerScreen->Render(sdl_renderer);
			break;
		case gameStates::MP_PLAYING:
			world->render(sdl_renderer);
			for (int i = 0; i < b->size(); i++)
			{
				if (b->at(i)->isAlive)
				{
					b->at(i)->render(sdl_renderer);
				}
			}
			graphicsSystem.update(sdl_renderer, gameState);
			break;
		case gameStates::MP_GAMEOVER:
			break;
		default:
			break;
		}
		
		SDL_RenderPresent(sdl_renderer);
	}
	else if (gameState.currentState == gameStates::BOSS_DEFEATED)
	{
		SDL_RenderCopyEx(sdl_renderer, winScreen, nullptr, &winSize, 0, (0, 0), SDL_FLIP_NONE);
	}
	else if (gameState.currentState == gameStates::GAMEOVER)
	{
		SDL_RenderCopyEx(sdl_renderer, deathScreen, nullptr, &winSize, 0, (0, 0), SDL_FLIP_NONE); 
	}

	SDL_RenderPresent(sdl_renderer);

}

/** update and render game entities*/
void Game::loop()
{
	LTimer capTimer;//to cap framerate

	bool isRunning = true;
	while (isRunning) {
		capTimer.start();
		float avgFPS = countedFrames / (fpsTimer.getTicks() / 1000.f);
		if (avgFPS > 2000000)
		{
			avgFPS = 0;
		}
		if (!pause) //in pause mode don't bother updating
			update();
		render();
		//std::cout << ++countedFrames << std::endl;
		int frameTicks = capTimer.getTicks();
		if (frameTicks < SCREEN_TICKS_PER_FRAME)
		{
			SDL_Delay(SCREEN_TICKS_PER_FRAME - frameTicks);
		}
	}

}

void Game::checkCollision()
{
	for (int j = 0; j < droppedItems.size(); j++)
	{
		if (cManager.checkCollision(SDL_Rect() = { playerPositionComponent->getPosition().x, playerPositionComponent->getPosition().y, PLAYER_WIDTH, PLAYER_HEIGHT }, droppedItems.at(j)->bounds))
			/*ayy*/ {
			switch (droppedItems.at(j)->getLootType())
			{
			case Item::AK:
				for (int k = 0; k < player->getComponents().size(); k++)
				{
					if (player->getComponents().at(k)->getID() == "Firing")
					{
						fsm->setCurrent(2);
						static_cast<FiringComponent*>(player->getComponents().at(k))->setCurrentGun("ak");
						hud.updateBullets(0, 1);
						a->at(5) = true;
					}
				}
				break;
			case Item::SHOTGUN:
				for (int k = 0; k < player->getComponents().size(); k++)
				{
					if (player->getComponents().at(k)->getID() == "Firing")
					{
						fsm->setCurrent(3);


						static_cast<FiringComponent*>(player->getComponents().at(k))->setCurrentGun("shotgun");
						hud.updateBullets(0, 2);
						a->at(5) = true;
					}
				}
				break;
			case Item::GREEN:
				controlSystem.addBoost(1);
				for (int k = 0; k < player->getComponents().size(); k++) {
					if (player->getComponents().at(k)->getID() == "Stats")
						static_cast<StatsComponent*>(player->getComponents().at(k))->setBoost(1);
				}
				break;
			case Item::YELLOW_SUNSHINE:
				controlSystem.addBoost(2);
				for (int k = 0; k < player->getComponents().size(); k++) {
					if (player->getComponents().at(k)->getID() == "Stats")
						static_cast<StatsComponent*>(player->getComponents().at(k))->setBoost(2);
				}
				break;
			case Item::GYM_CANDY:
				controlSystem.addBoost(3);
				for (int k = 0; k < player->getComponents().size(); k++) {
					if (player->getComponents().at(k)->getID() == "Stats")
						static_cast<StatsComponent*>(player->getComponents().at(k))->setBoost(3);
				}
				break;
			case Item::ELECTRIC_ICE:
				controlSystem.addBoost(4);
				for (int k = 0; k < player->getComponents().size(); k++) {
					if (player->getComponents().at(k)->getID() == "Stats")
						static_cast<StatsComponent*>(player->getComponents().at(k))->setBoost(4);
				}
				break;
			case Item::VELVET_THUNDER:
				controlSystem.addBoost(5);
				for (int k = 0; k < player->getComponents().size(); k++) {
					if (player->getComponents().at(k)->getID() == "Stats")
						static_cast<StatsComponent*>(player->getComponents().at(k))->setBoost(5);
				}
				break;
			default:
				break;
			}
			droppedItems.at(j) = nullptr;
			droppedItems.erase(droppedItems.begin() + j);
		}
	}
	for (int i = 0; i < enemyEntities.size(); i++)
	{
		for (int j = 0; j < enemyEntities.at(i)->getComponents().size(); j++)
		{
			if (enemyEntities.at(i)->getComponents().at(j)->getID() == "Position")
			{
				if (static_cast<PositionComponent*>(enemyEntities.at(i)->getComponents().at(j))->getPosition().x < 64)
					static_cast<PositionComponent*>(enemyEntities.at(i)->getComponents().at(j))->setPosition(SDL_Point() = { 64, static_cast<PositionComponent*>(enemyEntities.at(i)->getComponents().at(j))->getPosition().y });
				if (static_cast<PositionComponent*>(enemyEntities.at(i)->getComponents().at(j))->getPosition().x >(1280 - 128))
					static_cast<PositionComponent*>(enemyEntities.at(i)->getComponents().at(j))->setPosition(SDL_Point() = { (1280 - 128
						), static_cast<PositionComponent*>(enemyEntities.at(i)->getComponents().at(j))->getPosition().y });
				if (static_cast<PositionComponent*>(enemyEntities.at(i)->getComponents().at(j))->getPosition().y < 64)
					static_cast<PositionComponent*>(enemyEntities.at(i)->getComponents().at(j))->setPosition(SDL_Point() = { static_cast<PositionComponent*>(enemyEntities.at(i)->getComponents().at(j))->getPosition().x, 64 });
				if (static_cast<PositionComponent*>(enemyEntities.at(i)->getComponents().at(j))->getPosition().y >(704 - 128))
					static_cast<PositionComponent*>(enemyEntities.at(i)->getComponents().at(j))->setPosition(SDL_Point() = { static_cast<PositionComponent*>(enemyEntities.at(i)->getComponents().at(j))->getPosition().x, (704 - 128) });
			}
		}
	}
	for (int i = 0; i < world->map.size(); i++)
	{
		if (cManager.checkCollision(SDL_Rect() = { playerPositionComponent->getPosition().x, playerPositionComponent->getPosition().y, PLAYER_WIDTH, PLAYER_HEIGHT }, world->map.at(i)->bounds))
		{
			float offsetX = 0;
			float offsetY = 0;
			switch (world->map.at(i)->tileType)
			{
			case Tile::WALL:
				offsetX = cManager.getHorizontalIntersectionDepth(SDL_Rect() = { playerPositionComponent->getPosition().x, playerPositionComponent->getPosition().y, PLAYER_WIDTH, PLAYER_HEIGHT }, world->map.at(i)->bounds);
				offsetY = cManager.getVerticalIntersectionDepth(SDL_Rect() = { playerPositionComponent->getPosition().x, playerPositionComponent->getPosition().y, PLAYER_WIDTH, PLAYER_HEIGHT }, world->map.at(i)->bounds);

				if (std::abs(offsetX) > std::abs(offsetY))
				{
					playerPositionComponent->setPosition(SDL_Point() = { playerPositionComponent->getPosition().x, playerPositionComponent->getPosition().y + int(offsetY) });
				}
				else
				{
					playerPositionComponent->setPosition(SDL_Point() = { playerPositionComponent->getPosition().x + int(offsetX), playerPositionComponent->getPosition().y });
				}
				break;
			case Tile::DOOR_N:
				if (!doorsLocked) {
					doorsLocked = false;
					world->initialise(map->getNextRoom(world->map.at(i)->tileType), sdl_renderer);
					playerPositionComponent->setPosition(SDL_Point() = { playerPositionComponent->getPosition().x, (9 * 64) });
					allyPositionComponent->setPosition(SDL_Point() = { allyPositionComponent->getPosition().x, (9 * 64) });
					a->at(2) = true;
					spawnEnemies(map->getNextRoom()->isBossRoom);
				}
				else
				{
					offsetX = cManager.getHorizontalIntersectionDepth(SDL_Rect() = { playerPositionComponent->getPosition().x, playerPositionComponent->getPosition().y, PLAYER_WIDTH, PLAYER_HEIGHT }, world->map.at(i)->bounds);
					offsetY = cManager.getVerticalIntersectionDepth(SDL_Rect() = { playerPositionComponent->getPosition().x, playerPositionComponent->getPosition().y, PLAYER_WIDTH, PLAYER_HEIGHT }, world->map.at(i)->bounds);

					if (std::abs(offsetX) > std::abs(offsetY))
					{
						playerPositionComponent->setPosition(SDL_Point() = { playerPositionComponent->getPosition().x, playerPositionComponent->getPosition().y + int(offsetY) });
					}
					else
					{
						playerPositionComponent->setPosition(SDL_Point() = { playerPositionComponent->getPosition().x + int(offsetX), playerPositionComponent->getPosition().y });
					}
				}
				break;
			case Tile::DOOR_E:
				if (!doorsLocked) {
					doorsLocked = false;
					world->initialise(map->getNextRoom(world->map.at(i)->tileType), sdl_renderer);
					playerPositionComponent->setPosition(SDL_Point() = { (1 * 64), playerPositionComponent->getPosition().y });
					allyPositionComponent->setPosition(SDL_Point() = { (1 * 64), playerPositionComponent->getPosition().y });
					a->at(2) = true;
					spawnEnemies(map->getNextRoom()->isBossRoom);
				}
				else
				{
					offsetX = cManager.getHorizontalIntersectionDepth(SDL_Rect() = { playerPositionComponent->getPosition().x, playerPositionComponent->getPosition().y, PLAYER_WIDTH, PLAYER_HEIGHT }, world->map.at(i)->bounds);
					offsetY = cManager.getVerticalIntersectionDepth(SDL_Rect() = { playerPositionComponent->getPosition().x, playerPositionComponent->getPosition().y, PLAYER_WIDTH, PLAYER_HEIGHT }, world->map.at(i)->bounds);

					if (std::abs(offsetX) > std::abs(offsetY))
					{
						playerPositionComponent->setPosition(SDL_Point() = { playerPositionComponent->getPosition().x, playerPositionComponent->getPosition().y + int(offsetY) });
					}
					else
					{
						playerPositionComponent->setPosition(SDL_Point() = { playerPositionComponent->getPosition().x + int(offsetX), playerPositionComponent->getPosition().y });
					}
				}
				break;
			case Tile::DOOR_S:
				if (!doorsLocked) {
					doorsLocked = false;
					world->initialise(map->getNextRoom(world->map.at(i)->tileType), sdl_renderer);
					playerPositionComponent->setPosition(SDL_Point() = { playerPositionComponent->getPosition().x, (1 * 64) });
					allyPositionComponent->setPosition(SDL_Point() = { playerPositionComponent->getPosition().x, (1 * 64) });
					a->at(2) = true;
					spawnEnemies(map->getNextRoom()->isBossRoom);
				}
				else
				{
					offsetX = cManager.getHorizontalIntersectionDepth(SDL_Rect() = { playerPositionComponent->getPosition().x, playerPositionComponent->getPosition().y, PLAYER_WIDTH, PLAYER_HEIGHT }, world->map.at(i)->bounds);
					offsetY = cManager.getVerticalIntersectionDepth(SDL_Rect() = { playerPositionComponent->getPosition().x, playerPositionComponent->getPosition().y, PLAYER_WIDTH, PLAYER_HEIGHT }, world->map.at(i)->bounds);

					if (std::abs(offsetX) > std::abs(offsetY))
					{
						playerPositionComponent->setPosition(SDL_Point() = { playerPositionComponent->getPosition().x, playerPositionComponent->getPosition().y + int(offsetY) });
					}
					else
					{
						playerPositionComponent->setPosition(SDL_Point() = { playerPositionComponent->getPosition().x + int(offsetX), playerPositionComponent->getPosition().y });
					}
				}
				break;
			case Tile::DOOR_W:
				if (!doorsLocked) {
					doorsLocked = false;
					world->initialise(map->getNextRoom(world->map.at(i)->tileType), sdl_renderer);
					playerPositionComponent->setPosition(SDL_Point() = { (18 * 64), playerPositionComponent->getPosition().y });
					allyPositionComponent->setPosition(SDL_Point() = { (18 * 64), playerPositionComponent->getPosition().y });
					a->at(2) = true;
					spawnEnemies(map->getNextRoom()->isBossRoom);
				}
				else
				{
					offsetX = cManager.getHorizontalIntersectionDepth(SDL_Rect() = { playerPositionComponent->getPosition().x, playerPositionComponent->getPosition().y, PLAYER_WIDTH, PLAYER_HEIGHT }, world->map.at(i)->bounds);
					offsetY = cManager.getVerticalIntersectionDepth(SDL_Rect() = { playerPositionComponent->getPosition().x, playerPositionComponent->getPosition().y, PLAYER_WIDTH, PLAYER_HEIGHT }, world->map.at(i)->bounds);

					if (std::abs(offsetX) > std::abs(offsetY))
					{
						playerPositionComponent->setPosition(SDL_Point() = { playerPositionComponent->getPosition().x, playerPositionComponent->getPosition().y + int(offsetY) });
					}
					else
					{
						playerPositionComponent->setPosition(SDL_Point() = { playerPositionComponent->getPosition().x + int(offsetX), playerPositionComponent->getPosition().y });
					}
				}
				break;
			default:
				break;
			}
		}
	}
	for (int i = 0; i < b->size(); i++)
	{
		if (b->at(i)->getID() == "Player")
		{
			if (m_hud->theBossIsHere)
			{
				for (int k = 0; k < boss->getComponents().size(); k++)
				{
					if (boss->getComponents().at(k)->getID() == "Position")
					{
						if (cManager.checkCollision(SDL_Rect(b->at(i)->getRect()),
							SDL_Rect() = { static_cast<PositionComponent*>(boss->getComponents().at(k))->getPosition().x,
							static_cast<PositionComponent*>(boss->getComponents().at(k))->getPosition().y, PLAYER_WIDTH * 2, PLAYER_HEIGHT * 2 }))
						{
							checkForLoot(static_cast<PositionComponent*>(boss->getComponents().at(k))->getPosition());
							for (int j = 0; j < boss->getComponents().size(); j++)
							{
								if (boss->getComponents().at(j)->getID() == "Health")
								{
									static_cast<HealthComponent*>(boss->getComponents().at(j))->setHealth(static_cast<HealthComponent*>(boss->getComponents().at(j))->getHealth() - 10);
									if (static_cast<HealthComponent*>(boss->getComponents().at(j))->getHealth() <= 0)
									{
										gameState.currentState = gameStates::BOSS_DEFEATED;
										a->at(3) = true;
									}
								}
							}
						}
					}
				}
			}
			for (int k = 0; k < enemyEntities.size(); k++)
			{
				for (int l = 0; l < enemyEntities.at(k)->getComponents().size(); l++)
				{
					if (enemyEntities.at(k) != nullptr && enemyEntities.at(k)->getComponents().at(l)->getID() == "Position")
					{
						if (cManager.checkCollision(SDL_Rect(b->at(i)->getRect()),
							SDL_Rect() = { static_cast<PositionComponent*>(enemyEntities.at(k)->getComponents().at(l))->getPosition().x,
							static_cast<PositionComponent*>(enemyEntities.at(k)->getComponents().at(l))->getPosition().y, PLAYER_WIDTH, PLAYER_HEIGHT }))
						{
							for (int j = 0; j < enemyEntities.at(k)->getComponents().size(); j++)
							{
								if (enemyEntities.at(k)->getComponents().at(j)->getID() == "Health")
								{
									static_cast<HealthComponent*>(enemyEntities.at(k)->getComponents().at(j))->setHealth(static_cast<HealthComponent*>(enemyEntities.at(k)->getComponents().at(j))->getHealth() - 10);
									if (static_cast<HealthComponent*>(enemyEntities.at(k)->getComponents().at(j))->getHealth() <= 0)
									{
										static_cast<HealthComponent*>(enemyEntities.at(k)->getComponents().at(j))->setHealth(0);
										checkForLoot(static_cast<PositionComponent*>(enemyEntities.at(k)->getComponents().at(l))->getPosition());
										enemyEntities.at(k)->~Entity();
										enemyEntities.at(k) = nullptr;
										enemyEntities.erase(enemyEntities.begin() + k);
										enemyEntities.shrink_to_fit();
										if (enemyEntities.size() == 0)
										{
											doorsLocked = false;
										}
										experienceComponent->incExperience(450);
										xp = experienceComponent->getExp();
										erasedEnemy = true;
										a->at(1) = true;
										break;
									}
								}
							}

							b->at(i)->isAlive = false;
						}
					}
					if (erasedEnemy)
					{
						erasedEnemy = false;
						break;
					}
				}
			}
		}
		else if (b->at(i)->getID() == "Enemy")
		{
			if (cManager.checkCollision(SDL_Rect(b->at(i)->getRect()),
				SDL_Rect() = { playerPositionComponent->getPosition().x, playerPositionComponent->getPosition().y, PLAYER_WIDTH, PLAYER_HEIGHT }))
			{
				for (int j = 0; j < player->getComponents().size(); j++)
				{
					if (player->getComponents().at(j)->getID() == "Health")
					{
						static_cast<HealthComponent*>(player->getComponents().at(j))->setHealth(static_cast<HealthComponent*>(player->getComponents().at(j))->getHealth() - 1);
						if (static_cast<HealthComponent*>(player->getComponents().at(j))->getHealth() <= 0)
						{
							static_cast<HealthComponent*>(player->getComponents().at(j))->setHealth(0);
							gameState.currentState = gameStates::GAMEOVER;
							std::cout << "GAME OVER, PLAYER DEAD" << std::endl;
							break;
						}
					}
				}
				b->at(i)->isAlive = false;
			}

			else if (cManager.checkCollision(SDL_Rect(b->at(i)->getRect()),
				SDL_Rect() = { allyPositionComponent->getPosition().x, allyPositionComponent->getPosition().y, PLAYER_WIDTH, PLAYER_HEIGHT }))
			{
				for (int j = 0; j < ally->getComponents().size(); j++)
				{
					if (ally->getComponents().at(j)->getID() == "Health")
					{
						static_cast<HealthComponent*>(ally->getComponents().at(j))->setHealth(static_cast<HealthComponent*>(ally->getComponents().at(j))->getHealth() - 10);
						if (static_cast<HealthComponent*>(ally->getComponents().at(j))->getHealth() <= 0)
						{
							static_cast<HealthComponent*>(ally->getComponents().at(j))->setHealth(0);
							break;
						}
					}
				}
				b->at(i)->isAlive = false;
			}
		}
	}

	if (cManager.checkCollision(SDL_Rect() = { playerPositionComponent->getPosition().x,playerPositionComponent->getPosition().y,PLAYER_WIDTH, PLAYER_HEIGHT },
		SDL_Rect() = { allyPositionComponent->getPosition().x, allyPositionComponent->getPosition().y, PLAYER_WIDTH, PLAYER_HEIGHT }))
	{
		for (int j = 0; j < ally->getComponents().size(); j++)
		{
			if (ally->getComponents().at(j)->getID() == "Health")
			{
				static_cast<HealthComponent*>(ally->getComponents().at(j))->setHealth(static_cast<HealthComponent*>(ally->getComponents().at(j))->getHealth() + 1);

				if (static_cast<HealthComponent*>(ally->getComponents().at(j))->getHealth() >= 100)
				{
					a->at(0) = true;
					static_cast<HealthComponent*>(ally->getComponents().at(j))->setHealth(100);
					break;
				}
			}
		}
	}
}

void Game::spawnEnemies()
{
	for (int i = 0; i < rand() % 6; i++)
	{
		switch ((rand() % 3) + 1)
		{
		case 1:
			enemyEntities.push_back(enemyPool->SpeedEnemy(rand() % 4, sdl_renderer, spawnPoints.at(i)));

			break;
		case 2:
			enemyEntities.push_back(enemyPool->TankEnemy(rand() % 4, sdl_renderer, spawnPoints.at(i)));

			break;
		case 3:
			enemyEntities.push_back(enemyPool->NormalEnemy(rand() % 4, sdl_renderer, spawnPoints.at(i)));

			break;
		}
		/*enemyEntities.push_back(enemyPool->SpeedEnemy(rand() % 4, sdl_renderer));*/
		graphicsSystem.addEntity(*enemyEntities.at(i));
		aiSystem.addEntity(*enemyEntities.at(i));
		std::cout << static_cast<PositionComponent*>(enemyEntities.at(i)->getComponents().at(i))->getPosition().x << std::endl;
	}
}

void Game::spawnEnemies(bool isBossRoom)
{
	if (!isBossRoom)
	{
		for (int i = 0; i < rand() % 6; i++)
		{
			switch ((rand() % 3) + 1)
			{
			case 1:
				enemyEntities.push_back(enemyPool->SpeedEnemy(rand() % 4, sdl_renderer, spawnPoints.at(i)));
				break;
			case 2:
				enemyEntities.push_back(enemyPool->TankEnemy(rand() % 4, sdl_renderer, spawnPoints.at(i)));
				break;
			case 3:
				enemyEntities.push_back(enemyPool->NormalEnemy(rand() % 4, sdl_renderer, spawnPoints.at(i)));
				break;
			}
			/*enemyEntities.push_back(enemyPool->SpeedEnemy(rand() % 4, sdl_renderer));*/
			graphicsSystem.addEntity(*enemyEntities.at(i));
			aiSystem.addEntity(*enemyEntities.at(i));
		}
	}
	else
	{
		graphicsSystem.addEntity(*boss);
		aiSystem.addEntity(*boss);
		m_hud->theBossIsHere = true;
		m_hud->updateBossHp(bossHealthComponent->getHealth(), bossHealthComponent->getMaxHealth());
	}
}

void Game::checkForLoot(SDL_Point dropPosition)
{
	int dropChance = 75; //75% chance to drop an item
	int diceRoll = rand() % 100 + 1;
	std::cout << "Loot Roll: " << diceRoll << std::endl;

	if (diceRoll <= dropChance)
	{
		std::cout << "Success! Creating loot" << std::endl;
		int boostDropChance = 75;
		int gunDropChance = 25;
		diceRoll = rand() % 100 + 1;
		if (diceRoll <= boostDropChance)
		{
			std::cout << "Type: BOOST" << std::endl;
			int boostChance_Green = 35;
			int boostChance_YellowSunshine = 25;
			int boostChance_GymCandy = 20;
			int boostChance_ElectricIce = 15;
			int boostChance_VelvetThunder = 5;
			diceRoll = rand() % 100 + 1;

			if (diceRoll <= boostChance_Green){ //drop a green boost
				droppedItems.push_back(std::make_shared<Item>(Item(dropPosition, Item::LootType::GREEN, sdl_renderer)));
			}
			else if(diceRoll <= boostChance_Green + boostChance_YellowSunshine){ //less than 60 but greater than 35
				droppedItems.push_back(std::make_shared<Item>(Item(dropPosition, Item::LootType::YELLOW_SUNSHINE, sdl_renderer)));
			}
			else if (diceRoll <= boostChance_Green + boostChance_YellowSunshine + boostChance_GymCandy){
				droppedItems.push_back(std::make_shared<Item>(Item(dropPosition, Item::LootType::GYM_CANDY, sdl_renderer)));
			}
			else if (diceRoll <= boostChance_Green + boostChance_YellowSunshine + boostChance_GymCandy + boostChance_ElectricIce){
				droppedItems.push_back(std::make_shared<Item>(Item(dropPosition, Item::LootType::ELECTRIC_ICE, sdl_renderer)));
			}
			else{
				droppedItems.push_back(std::make_shared<Item>(Item(dropPosition, Item::LootType::VELVET_THUNDER, sdl_renderer)));
			}
		}
		else{
			std::cout << "Type: GUN" << std::endl;
			int gunChance_AK = 30;
			int gunChance_Shotgun = 70;
			diceRoll = rand() % 100 + 1;

			if (diceRoll <= gunChance_AK) {
				droppedItems.push_back(std::make_shared<Item>(Item(dropPosition, Item::LootType::AK, sdl_renderer)));
			}
			else {
				droppedItems.push_back(std::make_shared<Item>(Item(dropPosition, Item::LootType::SHOTGUN, sdl_renderer)));
			}
		}
	}

	else
	{
		a->at(6) = true;
	}
}