module;

#include <iostream>
#include <vector>

export module Texture;

export namespace textures 
{
	export std::string rope = "Resources/rope.jpg";
	export std::string steelBeam = "Resources/steelBeam.jpg";

	export std::vector<std::string> texturesBarMode =
	{
		"Resources/modeConnect.png",
		"Resources/modeBlock.png",
		"Resources/modeDelete.png"
	};
	export std::vector<std::string> texturesBarModeRope =
	{
		"Resources/modeSteelBeam.png",
		"Resources/modeRope.png"
	};
	export std::vector<std::string> texturesBarStatus =
	{
		"Resources/modeStart.png",
		"Resources/modePause.png"
	};

}