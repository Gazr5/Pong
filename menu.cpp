#include "menu.h"
//#include <boost/asio.hpp>

#define CONNECTION_MENU_TEXT "Please, print IP of your friend\n\n"

enum class MenuPoint {
	mainMenu,
	multiplayerMenu,
	hostMenu,
	connectionMenu
};

/*edit: 
	Change x and y of scoreBoard
	Send renderer and window to Game() object
*/
Menu::Menu() : keystates(SDL_GetKeyboardState(NULL)), hostMenuDefaultText(std::string(CONNECTION_MENU_TEXT).length()){
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		std::cout << "Failed at SDL_Init()" << std::endl;
	if (SDL_CreateWindowAndRenderer(WINDOWWIDTH, WINDOWHEIGHT, 0, &window, &renderer) < 0)
		std::cout << "Failed at SDL_CreateWindowAndRenderer())" << std::endl;

	message = "1.\tPlay with computer\n2.\tPlay with friend";
	fontSize = 64;

	TTF_Init();
	Sans = TTF_OpenFont("ModernSansSerif7-m3Ym.ttf", fontSize);
	Color = { 255, 255, 255 };

	const std::string text = "1.\tPlay with computer\n2.\tPlay with friend";

	render_ = std::make_shared<SDL_Renderer*>(renderer);
} 

void Menu::MainMenu() {
	SDL_Event e;

	std::string inputText;

	MenuPoint menuPoint = MenuPoint::mainMenu;

	while (!keystates[SDL_SCANCODE_ESCAPE]) {

		switch (menuPoint)
		{
		case MenuPoint::mainMenu:

			if (keystates[SDL_SCANCODE_1])
				StartSingleGame();
			else if (keystates[SDL_SCANCODE_2]) {
				message = "1.\tBe host\n2.\tConnect to friend";
				menuPoint = MenuPoint::multiplayerMenu;
			}
			break;

		case MenuPoint::multiplayerMenu:

			if (keystates[SDL_SCANCODE_1]) {
				menuPoint = MenuPoint::hostMenu;

				boost::asio::ip::address ip_address = boost::asio::ip::address::from_string(boost::asio::ip::host_name());
				message = "Your IP is:\n" + ip_address.to_string() + "\n\n(CTRL + c for copy IP address)";

				std::cout << "Your IP address is: " << ip_address.to_string() << std::endl;
			}
			else if (keystates[SDL_SCANCODE_2]) {
				menuPoint = MenuPoint::connectionMenu;
				message = CONNECTION_MENU_TEXT;
			}
			break;
		
		case MenuPoint::hostMenu:
			
			if (e.key.keysym.sym == SDLK_c && SDL_GetModState() & KMOD_CTRL)
			{
				SDL_SetClipboardText(inputText.c_str());
			}
			break;

		case MenuPoint::connectionMenu:

			WriteIP(message, e);
			break;

		default:
			break;
		}

		Render();
	}
}

//edit
//Write process of inputing IP
void Menu::WriteIP(std::string& inputText, SDL_Event& e) {
	while (SDL_PollEvent(&e) != 0)
	{
		//User requests quit
		if (e.type == SDL_QUIT)
		{
			exit(0);
		}
		//Handle key press
		else if (e.type == SDL_KEYDOWN)
		{
			//Handle backspace
			if (e.key.keysym.sym == SDLK_BACKSPACE && inputText.length() > hostMenuDefaultText)
			{
				//Pop character off end
				inputText.pop_back();
			}
			else if (e.key.keysym.sym == SDLK_RETURN)
			{
				//Add something for connecting to another player?
			}
			//Handle copy
			else if (e.key.keysym.sym == SDLK_c && SDL_GetModState() & KMOD_CTRL)
			{
				SDL_SetClipboardText(inputText.c_str());
			}
			//Handle paste
			else if (e.key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_CTRL)
			{
				inputText = SDL_GetClipboardText();
			}
		}
		//Special text input event
		else if (e.type == SDL_TEXTINPUT)
		{
			//Append character
			inputText += e.text.text;
		}
	}
} 

void Menu::StartSingleGame() {
	Game game = Game();
	game.PlaySingleGame();
}

void Menu::StartMultiplayerGame(bool ifHost) {
	const std::string IP;

	Game game = Game();
	game.PlayMultiplayerGame(IP, ifHost);
} 

//edit
//Make more effective using variables
void Menu::Render() {
	surface = TTF_RenderText_Solid(Sans, message.c_str(), Color);
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	scoreBoard.w = surface->w;
	scoreBoard.h = surface->h;
	scoreBoard.x = 1200 / 2 + fontSize - scoreBoard.w;
	scoreBoard.y = fontSize * 2 - scoreBoard.h;
	SDL_FreeSurface(surface);
	SDL_RenderCopy(*render_.get(), texture, NULL, &scoreBoard);
	SDL_DestroyTexture(texture);
} 