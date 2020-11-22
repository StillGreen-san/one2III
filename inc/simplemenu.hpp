
/*

infoscreen
enter number sequence
choose conversion rules
choose output style
display output

simplemenu
	view
	callback*

conversionmenustatemachine
	callback(view)
	states[] {{view, {view, view}}}
			   text	  input text

*/

#include <string>
#include <vector>

struct SimpleMenu
{
	std::string_view text;
	std::string_view(*callback)(std::string_view);
	void show();
};

struct MenuState
{
	std::string_view parseInput(std::string_view);
	struct State
	{
		std::string_view text;
		struct InputMap
		{
			std::string_view input;
			std::string_view state;
		};
		std::vector<InputMap> inputmap;
	};
	std::vector<State> states;
};


void testfunc()
{
	
}
