#include "game.hpp"

Game::Game() : m_distribution(5000, 10000){
    m_boostTimer = m_distribution(m_randomEngine);

    m_brickGrid = std::make_unique<BrickGrid>(BRICKW, BRICKW);
    m_brickGrid->initGridFromFile("grids/grid3.txt", INITX, INITY);
    
    position ballPosition = {BALLX, BALLY};
    objectSize ballSize = {BALLSIZE, BALLSIZE};
    velocity ballVelocity = {40, 40};
    m_balls.push_back(std::make_unique<Ball>(ballPosition, ballSize, ballVelocity)); 
    m_numBalls = 1;
    
    position paddlePosition = {PADDLEX, PADDLEY};
    objectSize paddleSize = {PADDLEW, PADDLEH};
    m_paddle = std::make_unique<Paddle>(paddlePosition, paddleSize);

    position wallPosition = {WALLSX, WALLSY};
    objectSize wallSize = {WALLSW, WALLSH};
    m_wall = std::make_unique<Wall>(wallPosition, wallSize);
    m_isWinner = false;
};

void Game::init(){
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return ;
    }
    if(TTF_Init() == -1) {
        printf("TTF_Init: %s\n", TTF_GetError());
        exit(2);
    }

    m_window = SDL_CreateWindow("Kirpish syndyru", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (m_window == nullptr) {
        std::cerr << "Failed to create window: " << SDL_GetError() << std::endl;
        throw std::runtime_error(SDL_GetError());
        return;
    }

    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
    if (m_renderer == nullptr) {
        std::cerr << "Failed to create renderer: " << SDL_GetError() << std::endl;
        throw std::runtime_error(SDL_GetError());
        return ;
    }

    backgroundImage = IMG_LoadTexture(m_renderer, "img/qazaqyurt.png");
    if (backgroundImage == nullptr) {
        std::cerr << "Failed to load image: " << IMG_GetError() << std::endl;
        return;
    }
   
    for(auto& ball : m_balls){
        if(ball!=nullptr){
            ball->init(m_renderer, ball->getPosition().x, ball->getPosition().y);
            ball->setMoving(true);
            ball->setVelocityX(0);
            ball->setVelocityY(-BALLSPEED);
            ball->startGame();
        }
    }
}


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
        
        for (auto& boost : m_boosts) {  
            if(boost!=nullptr){
                if (boost->collidesWith(*m_paddle.get())) {
                    applyBoost(boost, m_paddle.get());
                    boost = nullptr;
                    m_boosts.erase(std::remove_if(m_boosts.begin(), m_boosts.end(), [&](const auto& boost) { return boost == nullptr; }), m_boosts.end());
                }
            }          
            
        }
    
    }
}

void Game::update(){
    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255); 
    SDL_RenderClear(m_renderer);    

    m_boosts.erase(std::remove_if(m_boosts.begin(), m_boosts.end(), [](const auto& boost) { return boost == nullptr; }), m_boosts.end());
    for(auto& ball : m_balls){
        if(ball!=nullptr){
            ball->update();

           if(m_numBalls==1 && m_balls[0]->getPosition().y - m_balls[0]->getSize().height > SCREEN_HEIGHT){
                SDL_RenderClear(m_renderer);   
                std::cout << "Game Over" << std::endl;
                m_numBalls=0;
            }
            if(m_brickGrid->allBricksDestroyed()){
                SDL_RenderClear(m_renderer);   
                m_isWinner = true;
            }

            if(ball->getPosition().x < WALLSX || ball->getPosition().x + ball->getSize().width > SCREEN_WIDTH - WALLSX){
                ball->setVelocityX(-ball->getVelocityX());
            }
            if(ball->getPosition().y < WALLSY ){
                ball->setVelocityY(-ball->getVelocityY());
            }
            
            if(ball->collidesWith(*m_paddle)){
                handleCollision(ball.get(), m_paddle.get());
            }

            for(auto& brick_vector : m_brickGrid->getBricks()){
                for(auto& brick : brick_vector){
                    if(ball->collidesWith(*brick.get()) ){
                        if(!brick->isDestroyed()){
                            handleCollision(ball.get(), brick.get());
                        }
                        
                    }
                }
            }
        }
    }


   
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

    for (auto& boost : m_boosts) {
        if (boost != nullptr) {
            boost->update();
        }
    }
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
    // SDL_RenderCopy(m_renderer, backgroundImage, nullptr, nullptr); // background image
    // SDL_SetRenderDrawColor(m_renderer, 250, 212, 216, 255);
    // SDL_RenderClear(m_renderer);
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
    TTF_Font* font = TTF_OpenFont("./LoveDays-2v7Oe.ttf", 20);
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
void Game::applyBoost(T& boost, GameObject* obj){
    velocity ballVelocity = {40, 40};
    if (dynamic_cast<BonusMultiBall*>(boost.get())) {
        std::cout << "MultiBall" << std::endl;
        m_balls.push_back(std::make_unique<Ball>(obj->getPosition(), obj->getSize(), ballVelocity));
        m_numBalls++;
    }
    else if (dynamic_cast<BonusWidePaddle*>(boost.get())) {
        std::cout << "WidePaddle" << std::endl;
        m_paddle->setWidth(m_paddle->getWidth() + 10);
    }
    else if (dynamic_cast<MalusNarrowPaddle*>(boost.get())) {
        std::cout << "NarrowPaddle" << std::endl;
        m_paddle->setWidth(m_paddle->getWidth() - 10);
    }
}

BrickGrid& Game::getBrickGrid(){
    return *m_brickGrid;
}

std::unique_ptr<Paddle>& Game::getPaddle() {
    return m_paddle;
}

Game::~Game(){
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}