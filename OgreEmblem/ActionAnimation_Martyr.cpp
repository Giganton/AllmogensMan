#include "ActionAnimation_Martyr.h"
#include "ActionSpecifics.h"

ActionAnimation_Martyr::ActionAnimation_Martyr(BattleAnimation* battleAnim, ActionResults results, bool isMaster, GraphicsAssets* assets, sf::RenderWindow* ww) : ActionAnimation(battleAnim, results, isMaster, assets, ww)
{
	if (results.getSpecifics().at(0) == MartyrSpecifics::ms_jumpingTo)
	{
		jumpingHome = false;
	}
	else if (results.getSpecifics().at(0) == MartyrSpecifics::ms_jumpingHome)
	{
		martyrDied = results.getSpecifics().at(1) == MartyrSpecifics::ms_martyrDied;
		jumpingHome = true;
	}
	else
	{
		throw new std::exception();
	}
}

/*signekirufuifjgtjugt7ut5458k8cmmicweurexjixuxduixxeqjexiwwwwwwuiiuuuuumdzieuiuiujjjkzjkkkkkkkkszmmzmzmmmmmmkzjjjjjjjjjjjjjjjjjjjjjjjzzHUJJJJJJJJJJJJJJJJJJJJJJJJJJ
JJJJIMJJJVIMJFCJUFCENIRJIRCIJEREICU NCCUJEUNGTU GUJNCISKCEJDSNIKDSNAJAAJSNDJN,D,KDSJSDNSDJDSJDSJDKKNHFUFEHRNUSHNRERUUNUHVIIUHRNII RUICFUIECUCICEIIII
XIIIIIIIUIUXIUUENEIJXNX JXIJIDADSNAIXNSDUDSUHDSUDSUI NUHRCYUKFCYFYYUCNYUCYUCYUNYCRNYUR FNCKNFURUIFCIUECNURINUNIU IROMOIMROMRIMJROIMMMMIRI CRJIERURU
IRUMTIUOEUIMNRUNCEU IMROEMVROJIRFOITIMRIURM MIRCOICRIM4ICOIFWWPRCMICRE JCINUCIECCEIINVNUIERIIUEUII CIMFLOIEIIMRCEIEUREUREIUM TIMOEREOITEI FJWIUEUENCW
UMOIWMDJEIJDIX ORIOECOIMEUOREIRE MIEOSIMUVSUIMDFOJLVIRURIROUIRSIUVURRIVSIUE NUJCIUEJREUNIEIUEINUYIENRYRCYFUEYINUINNNNYUYUIUIEUIERYUREUYEURIUCRUUREUIRCUCIRUYUIRURUIIUUYRI
MVIOEFLURLIEROIREMCIMC FENRUSRIRIUCRICIUEEICNERUR VMOIURENJUERJERIUEIUUEUNCIUCEFINENUIRENUIREINRCIWNENEIUNUNOWIEOIENIYUVWTNVEINVTEEVONTWWWWWWWWWWWWWPIVNIWVÅÖÄRJUNRIUNVINRNVTRINVTNI
*/

bool ActionAnimation_Martyr::progressAction_jumpingTo()
{
	unsigned int i;
	bool allFinished = false;
	//std::vector<FightEffect> effects = animatedResults.getEffects();
	double time;
	sf::Vector2f newPos, targetSpritePos;
	FightPos pos;
	if (times.size() > 0)
	{
		times.push_back((((double)std::clock() - (double)startTime) / (double)CLOCKS_PER_SEC) - times.at(0));
	}
	else
	{
		times.push_back(((double)std::clock() - (double)startTime) / (double)CLOCKS_PER_SEC);
	}

	switch (step)
	{
	case 0:
		spriteAnimations.find(activatorID)->second.startRelativeMovementAnimation(1, sf::Vector2f(45, 0), 0.3);
		spriteAnimations.find(activatorID)->second.startFadeAnimation(2, 0.1, true);
		step = 1;
		break;
	case 1:
		if (spriteAnimations.find(activatorID)->second.isTagFinished(1) && spriteAnimations.find(activatorID)->second.isTagFinished(2))
		{
			step = 2;
		}
		break;
	case 2:
		//pos = animatedResults.getTargets().at(0).getPrimaryTarget().first;
		targetSpritePos = spriteAnimations.find(animatedResults.getTargets().at(0).getPrimaryTarget().second)->second.getSpritePos();
		//spriteAnimations.find(activatorID)->second.moveToFightPos(pos);
		newPos = targetSpritePos + sf::Vector2f(-50, -60);
		spriteAnimations.find(activatorID)->second.setSpritePos(newPos);

		spriteAnimations.find(activatorID)->second.startRelativeMovementAnimation(3, sf::Vector2f(0, 60), 0.15);
		spriteAnimations.find(activatorID)->second.startFadeAnimation(4, 0.15, false);

		step = 3;
		break;
	case 3:
		if (spriteAnimations.find(activatorID)->second.isTagFinished(3) && spriteAnimations.find(activatorID)->second.isTagFinished(4))
		{
			step = 6;
		}
		break;
		/*case 4:
			pos = animatedResults.getTargets().at(0).getPrimaryTarget();

			spriteAnimations.find(activatorID)->second.moveToFightPos(pos);
			newPos = spriteAnimations.find(activatorID)->second.getSpritePos();
			spriteAnimations.find(activatorID)->second.setSpritePos(newPos + sf::Vector2f(-25, 0));

			step = 5;
			startTime = std::clock();
			break;
		case 5:
			time = ((double)std::clock() - (double)startTime) / (double)CLOCKS_PER_SEC;
			if (time > 2)
			{
				step = 6;
			}
			else
			{

			}
			break;*/
	case 6:
		actionInstanceFinished = true;
		times2.push_back(times.at(1));
		for (i = 2; i < times.size(); i++)
		{
			times2.push_back(times.at(i) - times.at(i - 1));
		}
		break;
	}
	return actionInstanceFinished;
}

bool ActionAnimation_Martyr::progressAction_jumpingHome()
{
	unsigned int i;
	bool allFinished = false;
	//std::vector<FightEffect> effects = animatedResults.getEffects();
	double time;
	sf::Vector2f newPos, targetSpritePos;
	FightPos pos;
	if (times.size() > 0)
	{
		times.push_back((((double)std::clock() - (double)startTime) / (double)CLOCKS_PER_SEC) - times.at(0));
	}
	else
	{
		times.push_back(((double)std::clock() - (double)startTime) / (double)CLOCKS_PER_SEC);
	}
	if (martyrDied)
	{
		actionInstanceFinished = true;
	}
	else
	{
		switch (step)
		{
		case 0:
			spriteAnimations.find(activatorID)->second.startRelativeMovementAnimation(1, sf::Vector2f(0, -160), 0.40);
			spriteAnimations.find(activatorID)->second.startFadeAnimation(2, 0.15, true);
			step = 1;
			break;
		case 1:
			if (spriteAnimations.find(activatorID)->second.isTagFinished(1) && spriteAnimations.find(activatorID)->second.isTagFinished(2))
			{
				step = 3;
			}
			break;
		case 2:

		case 3:
			pos = animatedResults.getTargets().at(0).getPrimaryTarget().first;
			//targetSpritePos = spriteAnimations.find(animatedResults.getTargets().at(0).getPrimaryTarget().second)->second.getSpritePos();
			spriteAnimations.find(activatorID)->second.moveToFightPos(pos);
			newPos = spriteAnimations.find(activatorID)->second.getSpritePos() + sf::Vector2f(15, 0);
			spriteAnimations.find(activatorID)->second.setSpritePos(newPos);

			spriteAnimations.find(activatorID)->second.startRelativeMovementAnimation(3, sf::Vector2f(-15, 0), 0.1);
			spriteAnimations.find(activatorID)->second.startFadeAnimation(4, 0.1, false);

			step = 4;
			break;
		case 4:
			if (spriteAnimations.find(activatorID)->second.isTagFinished(3) && spriteAnimations.find(activatorID)->second.isTagFinished(4))
			{
				step = 6;
			}
			break;
		case 6:
			actionInstanceFinished = true;
			times2.push_back(times.at(1));
			for (i = 2; i < times.size(); i++)
			{
				times2.push_back(times.at(i) - times.at(i - 1));
			}
			break;
		}
	}
	
	return actionInstanceFinished;
}

bool ActionAnimation_Martyr::progressAction()
{
	if (jumpingHome)
	{
		return progressAction_jumpingHome();
	}
	else
	{
		return progressAction_jumpingTo();
	}
}