#include "Graphics.h"
#include "BattleStage.h"
#include "Squad.h"
#include "Profession.h"
#include "Unit.h"
#include "Action.h"
#include <ctime>
#include "Cursor.h"
#include "Menu.h"
#include "MenuAnimation.h"
#include "StatusAnimation.h"
#include "BaseLayer.h"


Graphics::Graphics(std::list<Profession> profs, std::list<std::pair<Terrain, std::string>> terrains, sf::RenderWindow* ww, StringHandler* strHand)
{
    initTextures(profs, terrains);
    //initActionMap(actions, animations);
    stringHandler = strHand;
    //BattleAnimation bAnim = BattleAnimation(assets.unitTextureMap, assets.actionMap, ww);
    //mapAnimation = MapAnimation(&mapPackage, bAnim, &mapMenuPackage, ww);
    //mapAnimation2 = MapAnimation2(&assets.mapPackage, bAnim, &assets.verticalMapMenuPackage, ww);
    statusScreenAnimation = StatusAnimation(&assets.unitTextureMap, &assets.screenPackage, &assets.verticalMapMenuPackage, ww);
    squadManimation = SquadManagerAnimation(&assets.browserPackage, &assets.verticalMapMenuPackage, ww, &assets, stringHandler);

    campAnimation = CampAnimation(&assets.browserPackage, &assets.verticalMapMenuPackage, &assets.horizontalMapMenuPackage, ww, &assets, stringHandler);
    //campBaseLayer = CampMenuLayer(&campAnimation, &mapAnimation2, 1, ww);
    window = ww;

    baseLayer = new BaseLayer(mapAnimation2, campAnimation, window, &assets, stringHandler);
}
/*
bool Graphics::drawBattle()
{
    bool battleDone = false;
    window->clear(sf::Color(220, 240, 200, 255));

    battleDone = battleAnimation.progress();
    battleAnimation.draw();

    return battleDone;
}
*/

void Graphics::drawMenu(Menu menu)
{
    VerticalMenuAnimation anim(&assets.verticalMapMenuPackage, UTIL::ScreenCoord(0,0), window);
    anim.draw(menu);
}

void Graphics::applyEvents(GraphicsInterface* gInterface)
{
    events.concatenateQueues(gInterface->getEventQueue());
    unsigned int skipped = 0;
    while (events.size() > skipped)
    {
        StructuredEvent* temp = events.getEventAt(skipped);
        //temp->findBaseLayer(this);
        if (baseLayer->trackEvent(temp))
        {
            events.removeEventAt(skipped);
        }
        else
        {
            skipped = skipped + 1;
        }
        delete temp;
    }
    gInterface->addSignals(baseLayer->collectSignals());
}

std::vector<MouseSignal> Graphics::passMousePos(sf::Vector2i mousePos)
{
    return baseLayer->passMousePos(mousePos);
}

void Graphics::draw()
{
    baseLayer->drawAll();
}

void Graphics::drawVisualStack(GraphicsInterface* stackContainer)
{
    VisualStack stack = stackContainer->getVisualStack();

    if (stack.isMapVisible())
    {
        //std::vector<AnimationSignal> newSignals = mapAnimation.drawMap(stack.getMapVisuals());
        //mapAnimation2.initMapAnimation(stack.getMapVisuals().getMapData());
        
        
        if (stack.isNewMapInitialized())
        {
            mapAnimation2.initMapAnimation(stack.checkoutMapInitData());
        }
        std::vector<AnimationSignal> newSignals = mapAnimation2.drawMap(stack.getMapVisuals2());
        if (!newSignals.empty())
        {
            stackContainer->addSignals(newSignals);
        }
    }
    if (stack.isStatusScreenVisible())
    {
        statusScreenAnimation.draw(stack.getStatusScreenVisuals());
    }

    StructuredEventQueue queue = stack.getCampEvents();
    while (queue.size() > 0)
    {
        StructuredEvent* temp = queue.pop();
        //campBaseLayer.trackEvent(temp);
        delete temp;
    }
    if (!stack.isMapVisible())
    {
        //campBaseLayer.draw();
    }
}
/*
void Graphics::setupPreBattle(BattleStage stage)
{
    battleAnimation = BattleAnimation(stage, unitTextureMap, actionMap, window);
    battleAnimation.draw();
}

void Graphics::setupPostBattle(std::list<FightResults> results)
{
    battleAnimation.setActionList(results);
}


void Graphics::initMap(BattleMapVisualData mapData)
{
    mapAnimation2.initMapAnimation(mapData);
}

void Graphics::initSquadManager(SquadManagerInitVisuals smData)
{
    squadManimation.initialize(smData);
}*/

bool Graphics::run()
{
    sf::Event event;
    while (window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window->close();
            return false;
        }
    }
    window->clear();
    window->display();
    return true;
}

void Graphics::loadGrassTextures(MapPackage* mPack)
{
    sf::Texture texture;

    if (!texture.loadFromFile("textures\\map\\gras\\liten_gras_1.png"))
    {
        throw new std::exception("could not load menu image");
    }
    mPack->grassTextureSmall.push_back(texture);
    if (!texture.loadFromFile("textures\\map\\gras\\liten_gras_2.png"))
    {
        throw new std::exception("could not load menu image");
    }
    mPack->grassTextureSmall.push_back(texture);
    if (!texture.loadFromFile("textures\\map\\gras\\liten_gras_3.png"))
    {
        throw new std::exception("could not load menu image");
    }
    mPack->grassTextureSmall.push_back(texture);
    if (!texture.loadFromFile("textures\\map\\gras\\dubbel_mellan_gras_1.png"))
    {
        throw new std::exception("could not load menu image");
    }
    mPack->grassTextureMid1.push_back(texture);
    if (!texture.loadFromFile("textures\\map\\gras\\dubbel_mellan_gras_2.png"))
    {
        throw new std::exception("could not load menu image");
    }
    mPack->grassTextureMid1.push_back(texture);
    if (!texture.loadFromFile("textures\\map\\gras\\dubbel_mellan_gras_3.png"))
    {
        throw new std::exception("could not load menu image");
    }
    mPack->grassTextureMid1.push_back(texture);
    if (!texture.loadFromFile("textures\\map\\gras\\trippel_mellan_gras_1.png"))
    {
        throw new std::exception("could not load menu image");
    }
    mPack->grassTextureMid2.push_back(texture);
    if (!texture.loadFromFile("textures\\map\\gras\\trippel_mellan_gras_2.png"))
    {
        throw new std::exception("could not load menu image");
    }
    mPack->grassTextureMid2.push_back(texture);
    if (!texture.loadFromFile("textures\\map\\gras\\trippel_mellan_gras_3.png"))
    {
        throw new std::exception("could not load menu image");
    }
    mPack->grassTextureMid2.push_back(texture);
    if (!texture.loadFromFile("textures\\map\\gras\\dubbel_stor_gras_1.png"))
    {
        throw new std::exception("could not load menu image");
    }
    mPack->grassTextureBig.push_back(texture);
    if (!texture.loadFromFile("textures\\map\\gras\\dubbel_stor_gras_2.png"))
    {
        throw new std::exception("could not load menu image");
    }
    mPack->grassTextureBig.push_back(texture);
    if (!texture.loadFromFile("textures\\map\\gras\\dubbel_stor_gras_3.png"))
    {
        throw new std::exception("could not load menu image");
    }
    mPack->grassTextureBig.push_back(texture);
}

void Graphics::loadRiverTextures(MapPackage* mPack)
{
    sf::Texture texture;

    if (!texture.loadFromFile("textures\\map\\back\\riverNorth.png"))
    {
        throw new std::exception("could not load menu image");
    }
    mPack->riverTextureMap.insert({ Direction::up , texture });
    if (!texture.loadFromFile("textures\\map\\back\\riverSouth.png"))
    {
        throw new std::exception("could not load menu image");
    }
    mPack->riverTextureMap.insert({ Direction::down , texture });
    if (!texture.loadFromFile("textures\\map\\back\\riverWest.png"))
    {
        throw new std::exception("could not load menu image");
    }
    mPack->riverTextureMap.insert({ Direction::left , texture });
    if (!texture.loadFromFile("textures\\map\\back\\riverEast.png"))
    {
        throw new std::exception("could not load menu image");
    }
    mPack->riverTextureMap.insert({ Direction::right , texture });
    if (!mPack->riverTexture.loadFromFile("textures\\map\\back\\botten.png"))
    {
        throw new std::exception("could not load menu image");
    }
    if (!mPack->riverEdgeTexture.loadFromFile("textures\\map\\back\\kant.png"))
    {
        throw new std::exception("could not load menu image");
    }
    if (!mPack->skyTexture.loadFromFile("textures\\map\\back\\himlaBox.png"))
    {
        throw new std::exception("could not load menu image");
    }
}

void Graphics::loadBattleAnimTextures(BattleAnimationPackage* bPack)
{
    sf::Texture texture; 
    if (!bPack->lightningStrike.loadFromFile("textures\\actions\\lightningStrike.png"))
    {
        throw new std::exception("could not load menu image");
    }
}

void Graphics::loadMapOverlayTextures(MapOverlayPackage* moPack)
{
    sf::Texture texture;
    if (!moPack->victoryBanner.loadFromFile("textures\\mapOverlay\\victory_swe.png"))
    {
        throw new std::exception("could not load menu image");
    }

}
void Graphics::loadJobTextures(TraitPackage* tPack)
{
    sf::Texture texture;

    if (!tPack->jobForeground.loadFromFile("textures\\jobs\\yrkesRam.png"))
    {
        throw new std::exception("could not load menu image");
    }

    if (!tPack->defaultJobTexture.loadFromFile("textures\\jobs\\defaultYrke.png"))
    {
        throw new std::exception("could not load menu image");
    }
}

void Graphics::loadTraitTextures(TraitPackage* tPack)
{
    sf::Texture texture;

    if (!tPack->traitBackgroundTexture.loadFromFile("textures\\traits\\bakgrund.png"))
    {
        throw new std::exception("could not load menu image");
    }
    if (!tPack->traitCircleHitBox.loadFromFile("textures\\traits\\bakgrund.png"))
    {
        throw new std::exception("could not load menu image");
    }

    if (!texture.loadFromFile("textures\\traits\\plusAttack.png"))
    {
        throw new std::exception("could not load menu image");
    }
    tPack->traitTextures.insert({ TraitTag::enumPlusAttack , texture });

    if (!texture.loadFromFile("textures\\traits\\plusDefense.png"))
    {
        throw new std::exception("could not load menu image");
    }
    tPack->traitTextures.insert({ TraitTag::enumPlusDefense , texture });

    if (!texture.loadFromFile("textures\\traits\\naturalSelection.png"))
    {
        throw new std::exception("could not load menu image");
    }
    tPack->traitTextures.insert({ TraitTag::enumNaturalSelection , texture });
    if (!texture.loadFromFile("textures\\traits\\hugeStrength.png"))
    {
        throw new std::exception("could not load menu image");
    }
    tPack->traitTextures.insert({ TraitTag::enumHugeStrength , texture });
    if (!texture.loadFromFile("textures\\traits\\gains.png"))
    {
        throw new std::exception("could not load menu image");
    }
    tPack->traitTextures.insert({ TraitTag::enumGains , texture });
    if (!texture.loadFromFile("textures\\traits\\fencingDrill.png"))
    {
        throw new std::exception("could not load menu image");
    }
    tPack->traitTextures.insert({ TraitTag::enumFencingDrill , texture });
    if (!texture.loadFromFile("textures\\traits\\martyrTrait.png"))
    {
        throw new std::exception("could not load menu image");
    }
    tPack->traitTextures.insert({ TraitTag::enumMartyrTrait , texture });
    if (!texture.loadFromFile("textures\\traits\\lightningStrikeTrait.png"))
    {
        throw new std::exception("could not load menu image");
    }
    tPack->traitTextures.insert({ TraitTag::enumLightningStrikeTrait , texture });
    if (!texture.loadFromFile("textures\\traits\\blastTrait.png"))
    {
        throw new std::exception("could not load menu image");
    }
    tPack->traitTextures.insert({ TraitTag::enumBlastTrait , texture });
    if (!texture.loadFromFile("textures\\traits\\strikeTrait.png"))
    {
        throw new std::exception("could not load menu image");
    }
    tPack->traitTextures.insert({ TraitTag::enumStrikeTrait , texture });
    if (!texture.loadFromFile("textures\\traits\\dummyTrait.png"))
    {
        throw new std::exception("could not load menu image");
    }
    tPack->traitTextures.insert({ TraitTag::enumDummyTrait , texture });

    if (!texture.loadFromFile("textures\\traits\\giantStrengthTrait.png"))
    {
        throw new std::exception("could not load menu image");
    }
    tPack->traitTextures.insert({ TraitTag::enumGiantStrength , texture });

    if (!texture.loadFromFile("textures\\traits\\shieldBearerTrait.png"))
    {
        throw new std::exception("could not load menu image");
    }
    tPack->traitTextures.insert({ TraitTag::enumShieldBearer , texture });

    if (!texture.loadFromFile("textures\\traits\\warriorProfTrait.png"))
    {
        throw new std::exception("could not load menu image");
    }
    tPack->traitTextures.insert({ TraitTag::enumWarriorProfTrait , texture });

    if (!texture.loadFromFile("textures\\traits\\wizardProfTrait.png"))
    {
        throw new std::exception("could not load menu image");
    }
    tPack->traitTextures.insert({ TraitTag::enumWizardProfTrait , texture });

    if (!texture.loadFromFile("textures\\traits\\heroProfTrait.png"))
    {
        throw new std::exception("could not load menu image");
    }
    tPack->traitTextures.insert({ TraitTag::enumHeroProfTrait , texture });

    if (!texture.loadFromFile("textures\\traits\\heavyArmorTrait.png"))
    {
        throw new std::exception("could not load menu image");
    }
    tPack->traitTextures.insert({ TraitTag::enumHeavyArmor , texture });
    if (!texture.loadFromFile("textures\\traits\\rageTrait.png"))
    {
        throw new std::exception("could not load menu image");
    }
    if (!texture.loadFromFile("textures\\traits\\AttachedTrait.png"))
    {
        throw new std::exception("could not load menu image");
    }
    tPack->traitTextures.insert({ TraitTag::enumAttached , texture });
    if (!texture.loadFromFile("textures\\traits\\AttachedTrait.png"))
    {
        throw new std::exception("could not load menu image");
    }
    tPack->traitTextures.insert({ TraitTag::enumAttached , texture });
    if (!texture.loadFromFile("textures\\traits\\AttachedTrait.png"))
    {
        throw new std::exception("could not load menu image");
    }
    tPack->traitTextures.insert({ TraitTag::enumAttached , texture });
    if (!texture.loadFromFile("textures\\traits\\AttachedTrait.png"))
    {
        throw new std::exception("could not load menu image");
    }
    tPack->traitTextures.insert({ TraitTag::enumAttached , texture });
    if (!texture.loadFromFile("textures\\traits\\AttachedTrait.png"))
    {
        throw new std::exception("could not load menu image");
    }
    tPack->traitTextures.insert({ TraitTag::enumAttached , texture });
    if (!texture.loadFromFile("textures\\traits\\AttachedTrait.png"))
    {
        throw new std::exception("could not load menu image");
    }
    tPack->traitTextures.insert({ TraitTag::enumAttached , texture });
    if (!texture.loadFromFile("textures\\traits\\AttachedTrait.png"))
    {
        throw new std::exception("could not load menu image");
    }
    tPack->traitTextures.insert({ TraitTag::enumAttached , texture });
    if (!texture.loadFromFile("textures\\traits\\AttachedTrait.png"))
    {
        throw new std::exception("could not load menu image");
    }
    tPack->traitTextures.insert({ TraitTag::enumAttached , texture });
    if (!texture.loadFromFile("textures\\traits\\AttachedTrait.png"))
    {
        throw new std::exception("could not load menu image");
    }
    tPack->traitTextures.insert({ TraitTag::enumAttached , texture });
    if (!texture.loadFromFile("textures\\traits\\AttachedTrait.png"))
    {
        throw new std::exception("could not load menu image");
    }
    tPack->traitTextures.insert({ TraitTag::enumAttached , texture });
    if (!texture.loadFromFile("textures\\traits\\AttachedTrait.png"))
    {
        throw new std::exception("could not load menu image");
    }
    tPack->traitTextures.insert({ TraitTag::enumAttached , texture });
    if (!texture.loadFromFile("textures\\traits\\AttachedTrait.png"))
    {
        throw new std::exception("could not load menu image");
    }
    tPack->traitTextures.insert({ TraitTag::enumAttached , texture });
    if (!texture.loadFromFile("textures\\traits\\AttachedTrait.png"))
    {
        throw new std::exception("could not load menu image");
    }
    tPack->traitTextures.insert({ TraitTag::enumAttached , texture });
    if (!texture.loadFromFile("textures\\traits\\AttachedTrait.png"))
    {
        throw new std::exception("could not load menu image");
    }
    tPack->traitTextures.insert({ TraitTag::enumAttached , texture });
    if (!texture.loadFromFile("textures\\traits\\AttachedTrait.png"))
    {
        throw new std::exception("could not load menu image");
    }
    tPack->traitTextures.insert({ TraitTag::enumAttached , texture });
    if (!texture.loadFromFile("textures\\traits\\AttachedTrait.png"))
    {
        throw new std::exception("could not load menu image");
    }
    tPack->traitTextures.insert({ TraitTag::enumAttached , texture });
    if (!texture.loadFromFile("textures\\traits\\AttachedTrait.png"))
    {
        throw new std::exception("could not load menu image");
    }
    tPack->traitTextures.insert({ TraitTag::enumAttached , texture });
    if (!texture.loadFromFile("textures\\traits\\AttachedTrait.png"))
    {
        throw new std::exception("could not load menu image");
    }
    tPack->traitTextures.insert({ TraitTag::enumAttached , texture });
    if (!texture.loadFromFile("textures\\traits\\AttachedTrait.png"))
    {
        throw new std::exception("could not load menu image");
    }
    tPack->traitTextures.insert({ TraitTag::enumAttached , texture });
    if (!texture.loadFromFile("textures\\traits\\AttachedTrait.png"))
    {
        throw new std::exception("could not load menu image");
    }
    tPack->traitTextures.insert({ TraitTag::enumAttached , texture });
    if (!texture.loadFromFile("textures\\traits\\AttachedTrait.png"))
    {
        throw new std::exception("could not load menu image");
    }
    tPack->traitTextures.insert({ TraitTag::enumAttached , texture });
    if (!texture.loadFromFile("textures\\traits\\AttachedTrait.png"))
    {
        throw new std::exception("could not load menu image");
    }
    tPack->traitTextures.insert({ TraitTag::enumAttached , texture });
    if (!texture.loadFromFile("textures\\traits\\HejsanTrait.png"))
    {
        throw new std::exception("could not load menu image");
    }
    tPack->traitTextures.insert({ TraitTag::enumHejsan , texture });
    if (!texture.loadFromFile("textures\\traits\\HejsanTrait.png"))
    {
        throw new std::exception("could not load menu image");
    }
    tPack->traitTextures.insert({ TraitTag::enumHejsan , texture });
    if (!texture.loadFromFile("textures\\traits\\HejsanTrait.png"))
    {
        throw new std::exception("could not load menu image");
    }
    tPack->traitTextures.insert({ TraitTag::enumHejsan , texture });
    //python-entry traitIkon
    if (!tPack->traitCursor.loadFromFile("textures\\traits\\traitCursor.png"))
    {
        throw new std::exception("could not load menu image");
    }
}

void Graphics::loadProfessionPortraits(UnitPackage* unPack)
{
    if (!unPack->defaultPortrait.loadFromFile("textures\\default_portrait.png"))
    {
        throw new std::exception("could not load menu image");
    }
    if (!unPack->portraitFrame.loadFromFile("textures\\portrait_frame.png"))
    {
        throw new std::exception("could not load menu image");
    }
}

void Graphics::loadUITextures(UIMenuPackage* uiPack)
{
    if (!uiPack->draftBackground.loadFromFile("textures\\drafting\\background.png"))
    {
        throw new std::exception("could not load menu image");
    }
}

void Graphics::initTextures(std::list<Profession> profs, std::list<std::pair<Terrain, std::string>> terrains)
{
    sf::Texture texture;
    //load unit and squad textures
    {
        while (!profs.empty())
        {
            Profession temp = profs.front();
            profs.pop_front();

            if (!texture.loadFromFile(temp.getBattleTextureFile()))
            {
                throw new std::exception("could not load image");
            }
            assets.unitTextureMap.insert({ temp.getTag(), texture });

            if (!texture.loadFromFile(temp.getMapTextureFile()))
            {
                throw new std::exception("could not load image");
            }
            assets.mapPackage.squadTextureMap.insert({ temp.getTag(), texture });
        }
    }
    //load map textures
    {
        loadRiverTextures(&assets.mapPackage);
        loadGrassTextures(&assets.mapPackage);
        while (!terrains.empty())
        {
            Terrain temp = terrains.front().first;
            std::string terrainPath = terrains.front().second;
            terrains.pop_front();

            if (!texture.loadFromFile(terrainPath))
            {
                throw new std::exception("could not load image");
            }
            assets.mapPackage.terrainTextureMap.insert({ temp.getType(), texture });
        }
        if (!assets.mapPackage.gridTexture.loadFromFile("textures\\map\\diamantRam.png"))
        {
            throw new std::exception("could not load menu image");
        }
        
        if (!assets.mapPackage.cursorTexture.loadFromFile("textures\\map\\cursorDiamant.png"))
        {
            throw new std::exception("could not load menu image");
        }
        if (!assets.mapPackage.dotTexture.loadFromFile("textures\\map\\dot.png"))
        {
            throw new std::exception("could not load menu image");
        }
        if (!assets.mapPackage.xTexture.loadFromFile("textures\\map\\x.png"))
        {
            throw new std::exception("could not load menu image");
        }
    }
    //load menu window texture
    {
        if (!assets.verticalMapMenuPackage.top.loadFromFile("textures\\menu\\menuTop.png"))
        {
            throw new std::exception("could not load menu image");
        }
        if (!assets.verticalMapMenuPackage.middle.loadFromFile("textures\\menu\\menuVerticalMiddle.png"))
        {
            throw new std::exception("could not load menu image");
        }
        if (!assets.verticalMapMenuPackage.bottom.loadFromFile("textures\\menu\\menuBottom.png"))
        {
            throw new std::exception("could not load menu image");
        }
        //load menu cursor texture
        if (!assets.verticalMapMenuPackage.cursor.loadFromFile("textures\\menu\\menuCursor.png"))
        {
            throw new std::exception("could not load menu cursor image");
        }
        //load menu font
        if (!assets.verticalMapMenuPackage.font.loadFromFile("menuFont.ttf"))
        {
            throw new std::exception("could not load font");
        }
        if (!assets.horizontalMapMenuPackage.left.loadFromFile("textures\\menu\\menuLeftEdge.png"))
        {
            throw new std::exception("could not load menu image");
        }
        if (!assets.horizontalMapMenuPackage.middle.loadFromFile("textures\\menu\\menuHorizontalMiddle.png"))
        {
            throw new std::exception("could not load menu image");
        }
        if (!assets.horizontalMapMenuPackage.right.loadFromFile("textures\\menu\\menuRightEdge.png"))
        {
            throw new std::exception("could not load menu image");
        }
        //load menu cursor texture
        if (!assets.horizontalMapMenuPackage.cursor.loadFromFile("textures\\menu\\menuCursor.png"))
        {
            throw new std::exception("could not load menu cursor image");
        }
        //load menu font
        if (!assets.horizontalMapMenuPackage.font.loadFromFile("menuFont.ttf"))
        {
            throw new std::exception("could not load font");
        }
        //load status screen squad cursor texture
        if (!assets.screenPackage.cursor.loadFromFile("textures\\statusScreen\\cursor.png"))
        {
            throw new std::exception("could not load menu cursor image");
        }
        if (!assets.screenPackage.font.loadFromFile("screenFont.ttf"))
        {
            throw new std::exception("could not load font");
        }
    }
    //load fonts

    if (!assets.fontPackage.standardFont.loadFromFile("PTSerif-Regular.ttf"))
    {
        throw new std::exception("could not load font");
    }
    if (!assets.fontPackage.nameFont.loadFromFile("MorrisRoman-Black.ttf"))
    {
        throw new std::exception("could not load font");
    }
    //load browser textures
    {
        if (!texture.loadFromFile("textures\\map\\krigare.png"))
        {
            throw new std::exception("could not load menu image");
        }
        assets.browserPackage.iconTextures.insert({ BrowsableIconTag::unitKnight , std::make_pair(texture , sf::IntRect(0, 0, MAP_SPRITE_W, MAP_SPRITE_H)) });
        if (!texture.loadFromFile("textures\\map\\krigare.png"))
        {
            throw new std::exception("could not load menu image");
        }
        assets.browserPackage.iconTextures.insert({ BrowsableIconTag::unitWizard , std::make_pair(texture , sf::IntRect(0, 0, MAP_SPRITE_W, MAP_SPRITE_H)) });
        if (!texture.loadFromFile("textures\\browser\\plusIcon.png"))
        {
            throw new std::exception("could not load menu image");
        }
        assets.browserPackage.iconTextures.insert({ BrowsableIconTag::plusSign , std::make_pair(texture , sf::IntRect(0, 0, texture.getSize().x, texture.getSize().y)) });
        if (!texture.loadFromFile("textures\\browser\\emptyUnit.png"))
        {
            throw new std::exception("could not load menu image");
        }
        assets.browserPackage.iconTextures.insert({ BrowsableIconTag::emptyUnit , std::make_pair(texture , sf::IntRect(0, 0, texture.getSize().x, texture.getSize().y)) });
        if (!texture.loadFromFile("textures\\map\\krigare.png"))
        {
            throw new std::exception("could not load menu image");
        }
        assets.browserPackage.iconTextures.insert({ BrowsableIconTag::unitKnightRed , std::make_pair(texture , sf::IntRect(0, 0, MAP_SPRITE_W, MAP_SPRITE_H)) });
        if (!assets.browserPackage.cursorTexture.loadFromFile("textures\\browser\\browserCursor.png"))
        {
            throw new std::exception("could not load menu image");
        }
        if (!assets.browserPackage.background.loadFromFile("textures\\browser\\browserBG.png"))
        {
            throw new std::exception("could not load menu image");
        }

    }
    loadUITextures(&assets.uiPackage);
    //load portraits
    loadProfessionPortraits(&assets.unitPackage);

    loadBattleAnimTextures(&assets.battleAnimationPackage);
    //load trait textures
    loadTraitTextures(&assets.traitPackage);
    loadJobTextures(&assets.traitPackage);
    //load mapoverlay textures
    loadMapOverlayTextures(&assets.mapOverlayPackage);
}

/*void Graphics::initActionMap(std::list<ActionTag> actions, std::list<ActionAnimation> animations)
{
    while (!actions.empty())
    {
        ActionTag actionName = actions.front();
        ActionAnimation matchingAnimation = animations.front();
        actions.pop_front();
        animations.pop_front();
        assets.actionMap.insert({ actionName, matchingAnimation });
    }
}*/