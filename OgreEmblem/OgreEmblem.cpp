// OgreEmblem.cpp : This file contains the 'main' function. Program execution begins and ends there.
//hej Anton

#include "Unit.h"
#include "Action.h"
#include "BattleStage.h"
#include "Squad.h"
#include "Graphics.h"
#include "Profession.h"
#include<string>
#include "BattleMap.h"
#include "GameMaster.h"
#include "Terrain.h"
#include "Flag.h"
#include <ctime>
#include "SquadManager.h"
#include "BrowserEvent.h"
#include "IdCreator.h"
#include "Camp.h"
#include "StringHandler.h"
#include "TraitTree.h"
#include  "allActions.h"
#include "ChapterCollection.h"
#include<chrono>
#include "ActionTests.h"
#include "MainHelpers.h"

int main()
{
    sf::RectangleShape shape;
    shape.getGlobalBounds().contains(sf::Vector2f(2, 2));
    srand((unsigned int)time(NULL));
    //TraitTree test = TraitTree(TraitTreeType::triangle);
    sf::ContextSettings settings;
    settings.antialiasingLevel = 16.0;
    sf::RenderWindow window(sf::VideoMode(1920, 1080, 32), "Allmogens Män", sf::Style::Close, settings);//, sf::Style::Fullscreen);
    StringHandler stringHandler = StringHandler(Language::Svenska);
    while (1)
    {
        bool restart = false;
        

        std::map<ProfessionTag, Profession> pMap = createProfMap();

        Terrain* field = new Terrain(TerrainTypes::field);
        std::list<std::pair<Terrain, std::string>> tList = { std::make_pair(*field, "textures\\map\\diamantRutaGras.png") };

        std::map<std::string, TerrainTypes> terrainMap = createTerrainMap();

        IdCreator idCreator;

        ChapterCollection chapters(&idCreator, pMap);

        bool loop = true;
        Graphics* graphics = new Graphics(createProfList(), tList, &window, &stringHandler);

        GameMaster* master = new GameMaster(idCreator, pMap, terrainMap, &stringHandler, chapters, true);


        sf::Event event;

        double frameTime;
        std::chrono::steady_clock::time_point clock1, clock2;
        std::chrono::microseconds time1, time2, time3, time4, time5, time6, time7, time8;
        std::clock_t startTime = std::clock();
        GraphicsInterface graphInt;
        while (!restart)
        {
            clock1 = std::chrono::high_resolution_clock::now();
            while (window.pollEvent(event))
            {
                switch (event.type)
                {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyPressed:
                    switch (event.key.code)
                    {
                    case sf::Keyboard::Escape:
                        restart = true;
                        break;
                    default:
                        master->takeInput(event);
                        //camp.handleInput(event);
                        break;
                    }
                    break;
                case sf::Event::MouseButtonPressed:
                case sf::Event::MouseButtonReleased:
                    master->takeInput(event);
                    break;
                }
            }
            clock2 = std::chrono::high_resolution_clock::now();
            time2 = std::chrono::duration_cast<std::chrono::microseconds>(clock2 - clock1);
            clock1 = clock2;
            
            graphInt.clearVisualStack();

            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            std::vector<MouseSignal> mouseSignals = graphics->passMousePos(mousePos);
            master->passMouseSignals(mouseSignals);
            clock2 = std::chrono::high_resolution_clock::now();
            time3 = std::chrono::duration_cast<std::chrono::microseconds>(clock2 - clock1);
            clock1 = clock2;
            master->createVisualStack(&graphInt);
            clock2 = std::chrono::high_resolution_clock::now();
            time4 = std::chrono::duration_cast<std::chrono::microseconds>(clock2 - clock1);
            clock1 = clock2;
            graphics->drawVisualStack(&graphInt);
            clock2 = std::chrono::high_resolution_clock::now();
            time5 = std::chrono::duration_cast<std::chrono::microseconds>(clock2 - clock1);
            clock1 = clock2;
            graphics->applyEvents(&graphInt);
            clock2 = std::chrono::high_resolution_clock::now();
            time6 = std::chrono::duration_cast<std::chrono::microseconds>(clock2 - clock1);
            clock1 = clock2;
            frameTime = ((double)std::clock() - (double)startTime) / (double)CLOCKS_PER_SEC;
            //graphics->draw();
            master->run();
            
            if (frameTime > FRAMELENGTH)
            {
                graphics->draw();
                window.display();
                startTime = std::clock();
                //graphics->clearWindow();
                window.clear();

                //graphInt.getVisualStackPointer()->setSquadManagerVisuals(sqdMan.getVisuals());
                //camp.compileVisualStack(&graphInt);

                clock2 = std::chrono::high_resolution_clock::now();
                time7 = std::chrono::duration_cast<std::chrono::microseconds>(clock2 - clock1);
                clock1 = clock2;
            }
            clock2 = std::chrono::high_resolution_clock::now();
            time8 = std::chrono::duration_cast<std::chrono::microseconds>(clock2 - clock1);
            clock1 = clock2;
        }

        //std::cout << "Färdig!\n";
        delete(graphics);
        delete(master);
    }
}


int main1()
{
    srand((unsigned int)time(NULL));

    sf::ContextSettings settings;
    settings.antialiasingLevel = 16.0;
    sf::RenderWindow window(sf::VideoMode(1920, 1080, 32), "Allmogens Män", sf::Style::Close, settings);//, sf::Style::Fullscreen);

    StringHandler stringHandler = StringHandler(Language::Svenska);
    IdCreator idCreator;

    Terrain* field = new Terrain(TerrainTypes::field);
    std::list<std::pair<Terrain, std::string>> tList = { std::make_pair(*field, "textures\\map\\diamantRutaGras.png") };
    Graphics* graphics = new Graphics(createProfList(), tList, &window, &stringHandler);

    ActionTests tests = ActionTests(createProfMap(), &stringHandler, &idCreator, &window, graphics->getAssetsPtr());

    double frameTime;
    std::clock_t startTime = std::clock();

    while (1)
    {

        frameTime = ((double)std::clock() - (double)startTime) / (double)CLOCKS_PER_SEC;
        tests.progress();
        if (frameTime > FRAMELENGTH)
        {
            window.display();
            startTime = std::clock();
        }
    }
    return 1;
}