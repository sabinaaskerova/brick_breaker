#include "game.hpp"

Game::Game(const std::string& gridType, const int gridNumber)
    : m_distribution(5000, 10000), m_sdlWrapper(SDL_INIT_VIDEO) {
  m_sdlWrapper = SDLWrapper(SDL_INIT_VIDEO);
  m_window = m_sdlWrapper.createWindow(
      "Brick Breaker", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
      SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
  m_renderer =
      m_sdlWrapper.createRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);

  m_boostTimer = m_distribution(m_randomEngine);

  if (gridType == "classic") {
    m_brickGrid = std::make_unique<ClassicBrickGrid>(BRICKW, BRICKW);
  } else if (gridType == "hexagonal") {
    m_brickGrid = std::make_unique<HexagonalBrickGrid>(BRICKW, BRICKW);
  } else {
    throw std::invalid_argument("Invalid grid type");
  }
  std::string gridFile = "grids/grid" + std::to_string(gridNumber) + ".txt";
  m_brickGrid->initGridFromFile(gridFile, INITX, INITY);

  position ballPosition = {BALLX, BALLY};
  objectSize ballSize = {BALLSIZE, BALLSIZE};
  velocity ballVelocity = {40, 40};
  m_balls.push_back(
      std::make_unique<Ball>(m_renderer, ballPosition, ballSize, ballVelocity));
  m_numBalls = 1;

  position paddlePosition = {PADDLEX, PADDLEY};
  objectSize paddleSize = {PADDLEW, PADDLEH};
  m_paddle = std::make_unique<Paddle>(paddlePosition, paddleSize);

  position wallPosition = {WALLSX, WALLSY};
  objectSize wallSize = {WALLSW, WALLSH};
  m_wall = std::make_unique<Wall>(wallPosition, wallSize);
  m_isWinner = false;

  for (auto& ball : m_balls) {
    if (ball != nullptr) {
      ball->setMoving(true);
      ball->setVelocityX(0);
      ball->setVelocityY(-BALLSPEED);
    }
  }
};

void Game::game_loop()
{
    const int FPS = 60;
    const int frameDelay = 1000 / FPS;

    int frameTime;
    bool keep_running = true;
    while(keep_running)
    {
        m_frameStart = SDL_GetTicks();
		while(SDL_PollEvent(&m_window_event) > 0)
		{
			switch(m_window_event.type)
			{
			case SDL_QUIT:
				keep_running = false;
			}

			m_paddle->handle_input(m_window_event);
		}
        
        if(m_numBalls>0){
            update();
		    
        }
        draw();
        frameTime = SDL_GetTicks() - m_frameStart;

        if(frameDelay > frameTime)
        {
            SDL_Delay(frameDelay - frameTime);
        }
        Uint32 currentFrameTime = SDL_GetTicks();
        float deltaTime = (currentFrameTime - m_frameStart) ; // / 10.0f;
        m_frameStart = currentFrameTime;
        m_boostTimer -= deltaTime; // deltaTime is the time since the last frame
        
    }
}

void Game::updateBalls(){

    for (size_t i = 0; i < m_balls.size(); /* no increment here */) {
        if (m_balls[i] != nullptr) {
            m_balls[i]->update();

            if (m_balls[i]->getPosition().y - m_balls[i]->getSize().height > SCREEN_HEIGHT) {
                m_balls.erase(m_balls.begin() + i);
                m_numBalls--;

                if (m_numBalls == 0) {
                    SDL_RenderClear(m_renderer);
                    std::cout << "Game Over" << std::endl;
                }
            } else {
                if (m_balls[i]->getPosition().x < WALLSX) {
                    m_balls[i]->setPositionX(WALLSX);
                    m_balls[i]->setVelocityX(-m_balls[i]->getVelocityX());
                } 
                else if (m_balls[i]->getPosition().x + m_balls[i]->getSize().width > SCREEN_WIDTH - WALLSX) {
                    m_balls[i]->setPositionX(SCREEN_WIDTH - WALLSX - m_balls[i]->getSize().width);
                    m_balls[i]->setVelocityX(-m_balls[i]->getVelocityX());
                }
                if(m_balls[i]->getPosition().y < WALLSY - 1){
                    m_balls[i]->setVelocityY(-m_balls[i]->getVelocityY());
                }

                
                if(m_balls[i]->collidesWith(*m_paddle)){
                    handleCollision(m_balls[i].get(), m_paddle.get());
                }
                for(auto& brick_vector : m_brickGrid->getBricks()){
                    for(auto& brick : brick_vector){
                        if(m_balls[i]->collidesWith(*brick.get()) ){
                            if(!brick->isDestroyed()){
                                handleCollision(m_balls[i].get(), brick.get());
                            }
                            
                        }
                    }
                }
                i++; // only increment the index if we didn't erase a ball
            }
        }
        
    }
}


void Game::generateBoosts(){
    if (m_boostTimer <= 0) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(WALLSX, SCREEN_WIDTH - WALLSX - BALLSIZE); 
        std::uniform_int_distribution<> disBoostType(0, 2); // Generate a number between 0 and 2

        int randomX = dis(gen);
        position boostPosition = {static_cast<double>(randomX), WALLSY}; 
        objectSize boostSize = {BOOSTSIZE, BOOSTSIZE};
        velocity boostVelocity = {0, BOOSTSPEED}; 

        BoostType randomBoostType = static_cast<BoostType>(disBoostType(gen));

        std::unique_ptr<Boost> boost;
        switch (randomBoostType) {
            case BoostType::MultiBall:
                boost = std::make_unique<BonusMultiBall>(m_renderer, boostPosition, boostSize, boostVelocity, BOOSTDURATION);
                break;
            case BoostType::WidePaddle:
                boost = std::make_unique<BonusWidePaddle>(m_renderer, boostPosition, boostSize, boostVelocity, BOOSTDURATION);
                break;
            case BoostType::NarrowPaddle:
                boost = std::make_unique<MalusNarrowPaddle>(m_renderer, boostPosition, boostSize, boostVelocity, BOOSTDURATION);
                break;
        }
        m_boosts.push_back(std::move(boost));
        m_boostTimer = m_distribution(m_randomEngine);
    }
}

void Game::updateBoosts(){

    for (size_t i = 0; i < m_boosts.size(); /* no increment here */) {
        if (m_boosts[i]!= nullptr) {
            m_boosts[i]->update();
            if (m_boosts[i]->collidesWith(*m_paddle.get())) {
                applyBoost(m_boosts[i]);
                m_boosts[i] = nullptr;
                m_boosts.erase(std::remove(m_boosts.begin(), m_boosts.end(), nullptr), m_boosts.end());
            }
            else {
                ++i;
            }
        }
        
    }
   

}
void Game::update(){
    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255); 
    SDL_RenderClear(m_renderer);    
    updateBalls();
    if(m_brickGrid->allBricksDestroyed()){
        SDL_RenderClear(m_renderer);   
        m_isWinner = true;
    }
    generateBoosts();
    updateBoosts();
}

void Game::handleCollision(Ball* ball, GameObject* gameObject){
    
    Brick* brick = dynamic_cast<Brick*>(gameObject);
    Paddle* paddle = dynamic_cast<Paddle*>(gameObject);
    if (brick != nullptr) { // if the object is a brick
        if(brick->getType() == typeBrick::EMPTY){
            return;
        }
        else if(brick->getType() == typeBrick::NORMAL){
            brick->setDestroyed(true);
        }else if(brick->getType() == typeBrick::DOUBLE){
            brick->setType(typeBrick::NORMAL);
        }else if(brick->getType() == typeBrick::TRIPLE){
            brick->setType(typeBrick::DOUBLE);
        }
        
        double ballCenterX = ball->getPosition().x + ball->getSize().width / 2;
        double ballCenterY = ball->getPosition().y + ball->getSize().height / 2;
        double brickCenterX = brick->getPosition().x + brick->getSize().width / 2;
        double brickCenterY = brick->getPosition().y + brick->getSize().height / 2;

        double dx = ballCenterX - brickCenterX;
        double dy = ballCenterY - brickCenterY;
        
        if (std::abs(dx) > std::abs(dy)) {
            ball->setVelocityX(-ball->getVelocityX());
        } else {
            ball->setVelocityY(-ball->getVelocityY());
        }
    }
    else if(paddle != nullptr){
        ball->setVelocityY(-sqrt(abs(BALLSPEED - ball->getVelocityX() * ball->getVelocityX())));
        double impact = (ball->getPosition().x - paddle->getPosition().x) / paddle->getSize().width;
        ball->setVelocityX((impact - 0.5) * BALLSPEED);
        // Normalizing the speed vector so that the ball maintains a constant speed regardless of where it hits the paddle
        double magnitude = sqrt(ball->getVelocityX() * ball->getVelocityX() + ball->getVelocityY() * ball->getVelocityY());
        double normalizedX = ball->getVelocityX() / magnitude;
        double normalizedY = ball->getVelocityY() / magnitude;
        // ball velocity is the normalized vector multiplied by the desired speed
        double desiredSpeed = BALLSPEED;
        ball->setVelocityX(normalizedX * desiredSpeed);
        ball->setVelocityY(normalizedY * desiredSpeed);
    }
    
    else{
        double impact = (ball->getPosition().x - gameObject->getPosition().x) / gameObject->getSize().width;
        ball->setVelocityX((impact - 0.5) * 2 * BALLSPEED);
        ball->setVelocityY(-sqrt(abs( BALLSPEED - ball->getVelocityX() * ball->getVelocityX())));
    }

}

void Game::draw()
{
    m_brickGrid->draw(m_renderer);
    m_wall->draw(m_renderer);
    m_paddle->draw(m_renderer);

    for(auto& ball : m_balls){
        if(ball!=nullptr){
            ball->draw(m_renderer);
        }
    }
    for (auto& boost : m_boosts) {
        if (boost != nullptr) {
            boost->draw(m_renderer);
        }
    }
    if (m_isWinner) {
        SDL_RenderClear(m_renderer);   
        drawMessage("You Win!", WALLSW / 2 + WALLSX/2, SCREEN_HEIGHT / 2);
    } else if (m_numBalls == 0) {
        SDL_RenderClear(m_renderer);   
        drawMessage("Game Over", WALLSW / 2 + WALLSX/2, SCREEN_HEIGHT / 2);
    }
    
    SDL_RenderPresent(m_renderer);
}

void Game::drawMessage(const std::string& text, int x, int y) {
    TTF_Font* font = TTF_OpenFont("./LoveDays-2v7Oe.ttf", 40);
    SDL_Color color = {255,204,255,255}; 

    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(m_renderer, surface);

    SDL_Rect dst;
    dst.x = x;
    dst.y = y;
    SDL_QueryTexture(texture, NULL, NULL, &dst.w, &dst.h);
    SDL_RenderCopy(m_renderer, texture, NULL, &dst);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
    TTF_CloseFont(font);
}

template <typename T>
void Game::applyBoost(T& boost){
    velocity ballVelocity = {BALLSPEED, BALLSPEED};
    objectSize ballsize = {BALLSIZE, BALLSIZE};

    if (dynamic_cast<BonusMultiBall*>(boost.get())) {
      m_balls.push_back(std::make_unique<Ball>(
          m_renderer, m_balls[0]->getPosition(), ballsize, ballVelocity));
      m_numBalls++;

    } else if (dynamic_cast<BonusWidePaddle*>(boost.get())) {
      if (m_paddle->getType() == PaddleType::NARROW) {
        m_paddle->setWidth(m_paddle->getWidth() + 40);
      } else if (m_paddle->getType() == PaddleType::NORMAL) {
        m_paddle->setWidth(m_paddle->getWidth() + 30);
      }
      m_paddle->setType(PaddleType::WIDE);

    } else if (dynamic_cast<MalusNarrowPaddle*>(boost.get())) {
      if (m_paddle->getType() == PaddleType::WIDE) {
        m_paddle->setWidth(m_paddle->getWidth() - 40);
      } else if (m_paddle->getType() == PaddleType::NORMAL) {
        m_paddle->setWidth(m_paddle->getWidth() - 30);
      }
      m_paddle->setType(PaddleType::NARROW);
    }
}

template <typename T>
void Game::endBoost(T& boost){
    if (dynamic_cast<BonusWidePaddle*>(boost.get())) {
        m_paddle->setWidth(m_paddle->getWidth() - 20);
    }
    else if (dynamic_cast<MalusNarrowPaddle*>(boost.get())) {
        m_paddle->setWidth(m_paddle->getWidth() + 10);
    }
}


Game::~Game(){
  SDL_DestroyRenderer(m_renderer);
  SDL_DestroyWindow(m_window);
  SDL_Quit();
}