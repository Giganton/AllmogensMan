# -*- coding: iso-8859-1 -*-

import shutil
import os
import re

def copy_and_rename_image(original_image_path, new_name):
    # Get the folder and filename from the original image path
    folder, filename = os.path.split(original_image_path)
    
    
    # Construct the new path for the copied image
    new_image_path = os.path.join(folder, new_name)
    
    # Copy the image file
    shutil.copy(original_image_path, new_image_path)
	
def find_x_before_keyword(filename, keyword):
    with open(filename, 'r') as file:
        lines = file.readlines()

    x_value = None
    for i, line in enumerate(lines):
        if keyword in line:
            target_line_index = i - 1
            break

    # If the keyword is not found or it's on the first line, return None
    if 'target_line_index' not in locals() or target_line_index < 0:
        return None

    # Use regular expression to find the value of x in the target line
    pattern = r'\s*=\s*([\S\s]+)'
    match = re.search(pattern, lines[target_line_index])
    if match:
        x_value = int(match.group(1))

    return x_value

def insert_before_all_occurrences_same_row(file_path, search_string, insert_string):
    with open(file_path, 'r') as file:
        content = file.read()

    occurrences = [i for i in range(len(content)) if content.startswith(search_string, i)]

    if occurrences:
        new_content = ""
        start = 0
        for index in occurrences:
            new_content += content[start:index] + insert_string
            start = index
        new_content += content[start:]

        with open(file_path, 'w') as file:
            file.write(new_content)
    else:
        print("Search string not found in the file.")

def insert_text_before_first_instance(filename, search_text, insert_text):
    with open(filename, 'r') as file:
        lines = file.readlines()

    found_index = -1
    for i, line in enumerate(lines):
        if search_text in line:
            found_index = i
            break

    if found_index != -1:
        lines.insert(found_index, insert_text + '\n')

    with open(filename, 'w') as file:
        file.writelines(lines)

def create_and_write_file(file_path, content):
    with open(file_path, 'w') as file:
        file.write(content)
		

if __name__ == "__main__":
    thingName = "Hejsan"
    thingNameSwedish = "Hejsan"
    swedishDescription = "hallåhallå"
    englishDescription = "hallihallå"
    isTriggerable = True
    isBoon=True
    isMajor = False


    #skapa .h-fil-----------------------------------------------
    hfile_boon_content = "#pragma once\n#include \"Boon.h\"\n\nclass <thingName> : public Boon\n{\nprivate:\n\npublic:\n	<thingName>();\n\n	Boon* clone() const override { return new <thingName>(*this); };\n	Boon* allocateNew() const override { return new <thingName>(); };\n\n};\n"

    hfile_reaction_content = "#pragma once\n#include \"Action.h\"\nclass Fight;\n\nclass <thingName> : public ReAction\n{\nprivate:\n\npublic:\n	<thingName>();\n\n	ReAction* clone() const override { return new <thingName>(*this); };\n	ReAction* allocateNew() const override { return new <thingName>(); };\n};"
    content = "hej"
    if (isBoon):
        content = hfile_boon_content
    else:
        content = hfile_reaction_content

    content = content.replace("<thingName>",thingName)
    create_and_write_file(thingName + ".h",content)


    #skapa .cpp-fil---------------------------------------------
    cppfile_reaction_content = "#include \"<thingName>.h\"\n#include \"FightResults.h\"\n#include \"Fight.h\"\n#include \"Unit.h\"\n\<thingName>::<thingName>()\n{\n	targetingType = TargetingType::;\n	tag = ActionTag::<thingName>;\n}\n"
    cppfile_boon_content = "#include \"<thingName>.h\"\n#include \"ReactionStage.h\"\n#include \"Fight.h\"\n#include \"Unit.h\"\n#include \"FightResults.h\"\n\n<thingName>::<thingName>()\n{\n	tag = BoonTag::enum<thingName>;\n	traitTag = TraitTag::enum<thingName>;\n}\n"
    
    content = "hej"
    if (isBoon):
        content = cppfile_boon_content
    else:
        content = cppfile_reaction_content
    content = content.replace("<thingName>",thingName)

    create_and_write_file(thingName + ".cpp",content)


    #lagg till i allActions.h eller allBoons.h------------------------------------
    if isBoon:
        content = "#include \""+thingName+".h\""
        search_text = "//python-entry allBoons.h"
        insert_text_before_first_instance("allBoons.h", search_text, content)
    else:
        content = "#include \""+thingName+".h\""
        search_text = "//python-entry allActions.h"
        insert_text_before_first_instance("allActions.h", search_text, content)

    #lagg till ny traittagg---------------------------------------------------------
    enumNr_trait = find_x_before_keyword("TraitTag.h","//python-entry TraitTag.h")+1
    traitTagName = "enum"+thingName
    content = "	,"+traitTagName+" = " + str(enumNr_trait)
    search_text = "//python-entry TraitTag.h"
    insert_text_before_first_instance("TraitTag.h", search_text, content)


    #lagg till ny boontagg---------------------------------------------------------
    if isBoon:
        search_text = "//python-entry BoonTags.h"
        enumNr = find_x_before_keyword("BoonTags.h",search_text)+1
        content = "	,enum"+thingName+" = " + str(enumNr)
        insert_text_before_first_instance("BoonTags.h", search_text, content)


    #lagg till ny actiontagg---------------------------------------------------------
    if not isBoon:
        search_text = "//python-entry ActionTag.h"
        enumNr = find_x_before_keyword("ActionTag.h",search_text)+1
        content = "	,"+thingName+" = " + str(enumNr)
        insert_text_before_first_instance("ActionTag.h", search_text, content)


    #lagg till actiontagg till createAction-------------------------------------------
    if not isBoon:
        search_text = "//python-entry createAction"
        content = "	case ActionTag::<thingName>:\n		return new <thingName>();\n		break;"
        content = content.replace("<thingName>",thingName)
        insert_text_before_first_instance("Action.cpp", search_text, content)


    #lagg till actiontagg till createBoon-------------------------------------------
    if isBoon:
        search_text = "//python-entry createBoon"
        content = "	case BoonTag::enum<thingName>:\n		return new <thingName>();\n		break;"
        content = content.replace("<thingName>",thingName)
        insert_text_before_first_instance("Boon.cpp", search_text, content)


    #lagg till tagg till traitkonstruktor--------------------------------------------------

    content = "	case <traitTagName>:\n		<addedType>.push_back(new <thingName>());\n		break;"
    content = content.replace("<thingName>",thingName)
    content = content.replace("<traitTagName>",traitTagName)
    if (isBoon):
        addedType = "boons"
    else:
        addedType = "reactions"
    content = content.replace("<addedType>",addedType)
    search_text = "//python-entry TraitConstructor"
    insert_text_before_first_instance("Trait.cpp", search_text, content)


    #skapa en ikon för traiten---------------------------------------------------------
    namn = thingName+"Trait.png"
    copy_and_rename_image("textures/traits/default.png",namn)


    #knyt ikonen till traiten i koden
    search_text = "//python-entry traitIkon"
    content = "    if (!texture.loadFromFile(\"textures\\\\traits\\\\<thingName>Trait.png\"))\n    {\n        throw new std::exception(\"could not load menu image\");\n    }\n    tPack->traitTextures.insert({ TraitTag::enum<thingName> , texture });"
    content = content.replace("<thingName>",thingName)
    insert_text_before_first_instance("Graphics.cpp", search_text, content)


    #skapa .h-fil för animation-----------------------------------------------
    if not isBoon:
        content = "#pragma once\n#include \"ActionAnimation.h\"\n\nclass ActionAnimation_<thingName> : public ActionAnimation\n{\nprivate:\n	//void moveSprites() override;\npublic:\n	ActionAnimation_<thingName>() {};\n	ActionAnimation_<thingName>(BattleAnimation* battleAnim, ActionResults results, bool isMaster, GraphicsAssets* assets, sf::RenderWindow* ww);\n\n	ActionAnimation* clone() const override { return new ActionAnimation_<thingName>(*this); };\n	ActionAnimation* allocateNew() const override { return new ActionAnimation_<thingName>(); };\n\n	bool progressAction() override;\n};"
        content = content.replace("<thingName>",thingName)
        create_and_write_file("ActionAnimation_"+thingName + ".h",content)


    #skapa .cpp-fil för animation-----------------------------------------------
    if not isBoon:
        content = "#include  \"ActionAnimation_<thingName>.h\"\n\nActionAnimation_<thingName>::ActionAnimation_<thingName>(BattleAnimation* battleAnim, ActionResults results, bool isMaster, GraphicsAssets* assets, sf::RenderWindow* ww) : ActionAnimation(battleAnim, results, isMaster, assets, ww)\n{\n\n}\n\nbool ActionAnimation_<thingName>::progressAction()\n{\n	unsigned int i;\n	bool allFinished = false;\n	std::vector<FightEffect> effects = animatedResults.getEffects();\n	fixa nån animation kanske?\n\n	switch (step)\n	{\n	case 0:\n		spriteAnimations.find(activatorID)->second.addToQueue(enumSpriteAnimType::move);\n		step = 1;\n		break;\n	case 1:\n		if (spriteAnimations.find(activatorID)->second.hasTriggered1())\n		{\n			step = 2;\n			effectsAnimations.startInstance(activeInstance);\n		}\n		break;\n	case 2:\n		if (spriteAnimations.find(activatorID)->second.isFinished() && effectsAnimations.isFinished(activeInstance))\n		{\n			step = 3;\n		}\n		break;\n	case 3:\n		actionInstanceFinished = true;\n	}\n\n	return (actionInstanceFinished);\n}\n"
        content = content.replace("<thingName>",thingName)
        create_and_write_file("ActionAnimation_"+thingName + ".cpp",content)
    #lagg till ref i allActoinAnimations........----------------------------------
    if not isBoon:
        content = "#include \"ActionAnimation_"+thingName+".h\""
        search_text = "//python-entry AllActionAnimations.h"
        insert_text_before_first_instance("AllActionAnimations.h", search_text, content)


    #lagg till .obj i projfil-----------------------------------------------------------------------------
    search_text = "HeavyArmor.obj;Rage.obj;ActionAnimation_Rage.obj;%(AdditionalDependencies)</AdditionalDependencies>"
    content = thingName+".obj;"
    #filename = "C:\\Privat\\proj\\OgEm\\TestAllmoge\\TestAllmoge.vcxproj"
    filename = "TestAllmoge.vcxproj"
    insert_before_all_occurrences_same_row(filename,search_text,content)


    #lagg till i languageFiles
    search_text = "\n	]"
    content = ",\n		{\n			\"ID\" : \"<traitNumber>\",\n			\"name\" : \"<thingName>\",\n			\"description\" : \"<desc>\"\n		}"
    traitNumber = enumNr_trait
    content = content.replace("<traitNumber>",str(traitNumber))

    sweContent = content.replace("<thingName>",thingNameSwedish)
    sweContent = sweContent.replace("<desc>",swedishDescription)

    engContent = content.replace("<thingName>",thingName)
    engContent = engContent.replace("<desc>",englishDescription)
    print("häääj dööö")
    sweFile = "languageFiles\\svenska\\traits.json"
    engFile = "languageFiles\\english\\traits.json"
    insert_before_all_occurrences_same_row(sweFile, search_text, sweContent)
    insert_before_all_occurrences_same_row(engFile, search_text, engContent)