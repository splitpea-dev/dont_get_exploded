#include "game.h"

// constructor
Game::Game(SDL_Window* window, SDL_Renderer* renderer, SDL_Surface* tiles)
{
	// set rendering pointers for game object
	this->window = window;
	this->renderer = renderer;
	this->tiles = tiles;

	// set width and height variables
	SDL_GetWindowSize(this->window, &width, &height);

	// surfaces for game image and mixing surface for shadow effect blending
	pixels = SDL_CreateRGBSurface(0, width, height, 32, 0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff);
	mix_surface_1 = SDL_CreateRGBSurface(0, width, height, 32, 0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff);
	mix_surface_2 = SDL_CreateRGBSurface(0, width, height, 32, 0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff);
	bg_surface = SDL_CreateRGBSurface(0, width, height, 32, 0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff);

	// stream texture to render final image
	render_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, width, height);

	// optimize loaded bitmaps
	this->tiles = SDL_ConvertSurface(tiles, mix_surface_1->format, 0);
	
	// set color key game image and tiles
	Uint32 color_key = SDL_MapRGBA(this->tiles->format, 0x00, 0xff, 0xff, 0xff);
	SDL_SetColorKey(pixels, SDL_TRUE, color_key);
	SDL_SetColorKey(this->tiles, SDL_TRUE, color_key);
	SDL_SetSurfaceBlendMode(pixels, SDL_BLENDMODE_BLEND);
	
	// initialize sprite map
	for(int i = 0; i < 30; i++)
		sprites[i].w = sprites[i].h = 32;
	for(int i = 0; i < 15; i++)
	{
		sprites[i].x = i * 32;
		sprites[i].y = 0;

		sprites[i + 15].x = i * 32;
		sprites[i + 15].y = 32;
	}

	// messages
	for(int i = 0; i < 3; i++)
	{
		sprites[i + 30].w = 480;
		sprites[i + 30].h = 32;
		sprites[i + 30].x = 0;
		sprites[i + 30].y = (i + 2) * 32;
	}

	// default LCD color
	bg_colors[0].first = SDL_MapRGBA(bg_surface->format, 0xaf, 0xae, 0x88, 0xff);
	bg_colors[0].second = SDL_MapRGBA(bg_surface->format, 0x58, 0x57, 0x44, 0xff);
	
	// blue LCD
	bg_colors[1].first = SDL_MapRGBA(bg_surface->format, 0x00, 0xa0, 0xe0, 0xff);
	bg_colors[1].second = SDL_MapRGBA(bg_surface->format, 0x00, 0x50, 0x70, 0xff);
	
	// red LCD
	bg_colors[2].first = SDL_MapRGBA(bg_surface->format, 0xe0, 0x00, 0x00, 0xff);
	bg_colors[2].second = SDL_MapRGBA(bg_surface->format, 0x70, 0x00, 0x00, 0xff);

	renderBackground(bg_colors[0].first, bg_colors[0].second);

	// initialize game
	difficulty = EASY_PEASY;
	initialize();
}

// destructor
Game::~Game()
{
	SDL_FreeSurface(pixels);
	SDL_FreeSurface(mix_surface_1);
	SDL_FreeSurface(mix_surface_2);
	SDL_FreeSurface(bg_surface);
}


// initialize for new game
void Game::initialize()
{
	// set number of mines
	switch(difficulty)
	{
		case EASY_PEASY:
		default:
			mines = 30;
			break;
		case I_LIKE_IT_SPICY:
			mines = 60;
			break;
		case WHY_SO_SERIOUS:
			mines = 90;
			break;
	}

	// initialize bools
	is_playing = true;
	got_exploded = false;
	
	// reset play stats
	correctly_placed_flags = 0;
	placed_flags = 0;

	// genrate new map
	generateMap();

	// current message
	current_message = 0;

	// render
	renderWindow();

}

// build new game map
void Game::generateMap()
{
	// initialize lower half (first)
	/*
		0: empty space
		1 - 8: proximity count space
		9: mine
		A: exploded mine
	*/
	
	for(int i = 0; i < 400; i++)
	{
		map[i].first = 0; // lower (see details below)
		map[i].second = 1; // upper (see details above)
	}

	// initialize upper half (second)
	/* 	
		0: not shown
		1: shown
		2: shown with flag
		3: shown with incorrect flag
	*/


	// C++ Standard 11 <random>
	std::random_device r;
	std::mt19937 generated(r());
	std::uniform_int_distribution<> d(0, 399);

	for(int i = 0; i < mines; i++)
	{
		int x = d(generated);
		while(map[x].first != 0)
			x = d(generated);
		map[x].first = 9;
		
	}

	// proximity
	for(int row = 0; row < 20; row++)
	{
		for(int col = 0; col < 20; col++)
		{
			if(map[(row * 20) + col].first == 0)
			{
				// if cell is a space count neighbors
				int c = 0;
				for(int rn = -1; rn < 2; rn++)
				{
					for(int cn = -1; cn < 2; cn++)
					{
						if(((row + rn) >=0) && ((row + rn) < 20))
						{
							if(((col + cn) >=0) && ((col + cn) < 20))
							{
								if(map[(((row + rn) * 20) + (col + cn))].first == 9)
								{
									c++;
								}
							}
						}
					}
				}
				map[(row * 20) + col].first = c;
			}
		}
	}

	/*
	// display lower map (console)
	for(int i = 0; i < 400; i++)
	{
		if((i % 20) == 0)
			std::cout << '\n';
		std::cout << map[i].first;
	}
	*/
	
}

// main game loop
void Game::play()
{
	while(is_running)
	{
		// get input
		while(SDL_PollEvent(&event) > 0)
		{
			if(event.type == SDL_QUIT)
			{
				is_playing = false;
				is_running = false;
			}
			else if(event.type == SDL_KEYDOWN)
			{
				// F1 reset to difficulty EASY PEASY
				if(event.key.keysym.sym == SDLK_F1)
				{
 
					difficulty = EASY_PEASY;
					initialize();
				}
				// F2 reset to difficulty I LIKE IT SPICY
				if(event.key.keysym.sym == SDLK_F2)
				{
					difficulty = I_LIKE_IT_SPICY;
					initialize();
				}
				// F3 reset to difficulty WHY SO SERIOUS?
				if(event.key.keysym.sym == SDLK_F3)
				{
					difficulty = WHY_SO_SERIOUS;
					initialize();
				}
				// F5 default BG color
				if(event.key.keysym.sym == SDLK_F5)
				{
					changeBackgroundColor(0);
				}
				// F6 blue BG color
				if(event.key.keysym.sym == SDLK_F6)
				{
					changeBackgroundColor(1);
				}
				// F7 default BG color
				if(event.key.keysym.sym == SDLK_F7)
				{
					changeBackgroundColor(2);
				}
				// F9 reset to current difficulty
				if(event.key.keysym.sym == SDLK_F9)
				{
					initialize();
				}
				// PRINTSCREEN to save screenshot
				// to be implemented
			}
			else if(event.type == SDL_MOUSEBUTTONDOWN)
			{
				if(is_playing)
				{
					// ONLY IF IN GAME
					std::pair<int, int> pin; // story (x, y)
					pin.first = event.button.x;
					pin.second = event.button.y;
					int pinned_tile = getTile(pin.first, pin.second);
					if(event.button.button == SDL_BUTTON_LEFT)
					{ 
						// LEFT BUTTON
						if(pinned_tile > -1)
						{
							if(sweepCell(pinned_tile) == 9)
							{
								map[pinned_tile].first = 11;
								for(int i = 0; i < 400; i++)
								{
									if(map[i].first == 9)
									{
										if(map[i].second == 2)
											map[i].first = 10;
										map[i].second = 0;
									}
									else
									{
										if(map[i].second == 2)
											map[i].second = 3;
									}
								}
								current_message = 2;	
								std::cout << "GAME OVER! -- YOU GO EXPLODED!!!\n";
								is_playing = false;
								got_exploded = true;
							}
							renderWindow();
						}
					}
					else
					{
						// RIGHT BUTTON
						if(pinned_tile > -1)
						{
							flagCell(pinned_tile);
							if(correctly_placed_flags == mines)
							{
								current_message = 1;
								std::cout << "GAME OVER! -- YOU WIN!!!\n";
								is_playing = false;
							}
							renderWindow();
						}
					}
				}
			}
		}
	}
}

// convert x, y coords to a tile position
int Game::getTile(int x, int y)
{
	x = x / 32;
	y = y / 32;
	return (y * 20 + x);
}

// main rendering method
void Game::renderWindow()
{
	SDL_Rect position;
	position.w = position.h = 32;

	Uint32 cx = SDL_MapRGBA(pixels->format, 0x00, 0xff, 0xff, 0xff);
	SDL_FillRect(pixels, NULL, cx);
	
	// render map to pixels surface
	for(int row = 0; row < 20; row++)
	{
		for(int col = 0; col < 20; col++)
		{
			position.x = col * 32;
			position.y = row * 32;
			if(map[row * 20 + col].second == 0)
			{
				switch(map[row * 20 + col].first)
				{
					case 0:
					default:
						// space
						SDL_BlitSurface(tiles, &sprites[6], pixels, &position);
						break;
					case 1:
						SDL_BlitSurface(tiles, &sprites[7], pixels, &position);
						break;
					case 2:
						SDL_BlitSurface(tiles, &sprites[8], pixels, &position);
						break;
					case 3:
						SDL_BlitSurface(tiles, &sprites[9], pixels, &position);
						break;
					case 4:
						SDL_BlitSurface(tiles, &sprites[10], pixels, &position);
						break;
					case 5:
						SDL_BlitSurface(tiles, &sprites[11], pixels, &position);
						break;
					case 6:
						SDL_BlitSurface(tiles, &sprites[12], pixels, &position);
						break;
					case 7:
						SDL_BlitSurface(tiles, &sprites[13], pixels, &position);
						break;	
					case 8:
						SDL_BlitSurface(tiles, &sprites[14], pixels, &position);
						break;
					case 9:
						SDL_BlitSurface(tiles, &sprites[4], pixels, &position);
						break;
					case 10:
						SDL_BlitSurface(tiles, &sprites[3], pixels, &position);
						break;
					case 11:
						SDL_BlitSurface(tiles, &sprites[5], pixels, &position);
						break;

				}
			}
			else
			{
				switch(map[row * 20 + col].second)
				{
					case 1:
					default:
						SDL_BlitSurface(tiles, &sprites[0], pixels, &position);
						break;
					case 2:
						SDL_BlitSurface(tiles, &sprites[1], pixels, &position);
						break;
					case 3:
						SDL_BlitSurface(tiles, &sprites[2], pixels, &position);
						break;
				}
			}
		}
	}

	// render messages to pixels surface
	renderStats();

	/*
	// draw border
	Uint32* pp = (Uint32*) pixels->pixels; // direct access to plot to pixels surface
	Uint32 black = SDL_MapRGBA(pixels->format, 0x00, 0x00, 0x00, 0xff);
	for(int i = 0; i < 640; i++)
	{	
		pp[i] = black;
		pp[640 * 640 + i] = black;
		pp[640 * i] = black;
		pp[640 * i + 639] = black;
	}
	*/

	Uint32* ms1 = (Uint32*) mix_surface_1->pixels; // read data
	Uint32* ms2 = (Uint32*) mix_surface_2->pixels; // write data
	Uint32 p; // pixel
	
	// render bg surface to mix surface 1
	SDL_BlitSurface(bg_surface, NULL, mix_surface_1, NULL);
	position.w = width;
	position.h = height;
	for(int offset = 2; offset >= 0; offset--)
	{
		position.x = position.y = offset;
		if(offset == 0)
		{
			// average blur mix surface 1 to mix surface 2 (for LCD shadow effect)
			for(int i_row = 0; i_row < 672; i_row++)
			{
				for(int i_col = 0; i_col < 640; i_col++)
				{
					int c = 0; // count
					int r_sum = 0;
					int g_sum = 0;
					int b_sum = 0;
					Uint8 r, g, b;
					for(int s_row = -1; s_row < 2; s_row++)
					{
						for(int s_col = -1; s_col < 2; s_col++)
						{
							if(((i_row + s_row) >= 0) && ((i_row + s_row) < 672))
							{
								if(((i_col + s_col) >= 0) && ((i_col + s_col) < 640))
								{
									p = ms1[((i_row + s_row) * 640) + i_col + s_col];
									SDL_GetRGB(p, mix_surface_1->format, &r, &g, &b);
									r_sum += int(r);
									g_sum += int(g);
									b_sum += int(b);
									c++;
								}
							}
						}
					}

					// average sum
					r = (r_sum / c);
					g = (g_sum / c);
					b = (b_sum / c);

					p = SDL_MapRGB(mix_surface_2->format, r, g, b);
					ms2[i_row * 640 + i_col] = p;
				}
			}
			
			// render pixels surface LCD image on top of blurred shadows
			SDL_SetSurfaceAlphaMod(pixels, 255);
			SDL_BlitSurface(pixels, NULL, mix_surface_2, &position);
		}
		else
		{
			// render pre-blurred shadow maps
			SDL_SetSurfaceAlphaMod(pixels, 96 / offset);
			SDL_BlitSurface(pixels, NULL, mix_surface_1, &position);
		}	
	}

	// render
	SDL_UpdateTexture(render_texture, NULL, ms2, width * sizeof(Uint32));
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, render_texture, NULL, NULL);
	SDL_RenderPresent(renderer);
}

int Game::sweepCell(int cell)
{
	if(map[cell].second == 1)
	{
		// if user clicked on dirt do...
		map[cell].second = 0; // expose dirt
		if(map[cell].first == 0)
		{
			if(cell > 19)
			{ // NOT on first row
				if((cell % 20) != 0)
				{ // NOT on left-most edge
					sweepCell(cell - 21); // sweep upper-left corner
				}
				if(((cell + 1) % 20) != 0)
				{ // NO on right-most edge
					sweepCell(cell - 19); // sweep upper_right corner
				}
				sweepCell(cell - 20); // sweep above
			}
			if(cell < 380)
			{ // NOT on bottom row
				if((cell % 20) != 0)
				{ // NOT on left-most edge
					sweepCell(cell + 19); // sweep lower-left corner
				}
				if(((cell + 1) % 20) !=0)
				{ // NOT on right-most edge
					sweepCell(cell + 21); // sweep lower-right corner
				}
				sweepCell(cell + 20); // sweep below
			}
			if((cell % 20) != 0)
			{ // NOT on left-most edge
				sweepCell(cell - 1); // sweep left
			}
			if(((cell + 1) % 20) !=0)
			{ // NOT on right-most edge
				sweepCell(cell + 1); // sweep right
			}
		}
		else if(map[cell].first == 9)
			return 9;
		else;
	}
	// default
	return -1;
}

// handle user attempt to flag cell
void Game::flagCell(int cell)
{
	if(map[cell].second == 1)
	{ // if dirt...
		if(placed_flags < mines)
		{
			map[cell].second = 2;
			placed_flags++;
			if(map[cell].first == 9)
				correctly_placed_flags++;
		}
	}
	else if(map[cell].second == 2)
	{
		map[cell].second = 1;
		placed_flags--;
		if(map[cell].first == 9)
			correctly_placed_flags--;
	}
	
	/*
	std::cout << "Placed Flags: " << placed_flags << '\n';
	std::cout << "Correctly Placed Flags: " << correctly_placed_flags << '\n';
	std::cout << "Mines: " << mines << '\n';
	*/
}

void Game::renderStats()
{
	SDL_Rect p;
	p.w = p.h = 32;
	p.y = 640;
	int value = mines - placed_flags;
	for(int c = 0; c < 2; c++)
	{
		int d = value % 10;
		if(((c == 1) && (d > 0)) || (c == 0))
		{
			p.x = width - ((c + 1) * 32);
			SDL_BlitSurface(tiles, &sprites[20 + d], pixels, &p); 
	 		value = value / 10;
		}
	}

	// render flag
	p.x = 544;
	SDL_BlitSurface(tiles, &sprites[19], pixels, &p);
	
	// render difficulty
	p.x = 512;
	SDL_BlitSurface(tiles, &sprites[15 + difficulty], pixels, &p);

	// display current message
	p.x = 32;
	SDL_BlitSurface(tiles, &sprites[30 + current_message], pixels, &p);
	
}


// this function fills the bg_surface with a radial gradient
void Game::renderBackground(Uint32 s_color, Uint32 e_color)
{
	int w = width / 2; // for quarter chunking
	int h = height / 2; // ditto
	Uint32 pixel_color; // read-write pixel color
	double degrees, radians, tick;
	int radius = 448; // adjust this for longer or shorter spread
	Uint32* pixels = (Uint32*) bg_surface->pixels; // pointer to surface pixels
	Uint8 r, g, b; // linear gradient RGB
	Uint8 sr, sg, sb; // start color RGB
	Uint8 er, eg, eb; // end color RGB
	SDL_GetRGB(s_color, bg_surface->format, &sr, &sg, &sb); // obtain individual RGB
	SDL_GetRGB(e_color, bg_surface->format, &er, &eg, &eb); // ditto
	
	// clear background to end color
	for(int row = 0; row < height; row++)
	{
		for(int col = 0; col < width; col++)
		{
			pixels[row * width + col] = e_color;
		}
	}

	// paint quarter radial gradient in lower right corner
	for(degrees = 0; degrees <= 90; degrees += .01)
	{
		for(int steps = 0; steps < radius; steps++)
		{
			tick = (double) steps / (double) (radius - 1);
			r = ((double) sr * (1 - tick)) + ((double) er * tick);
			g = ((double) sg * (1 - tick)) + ((double) eg * tick);
			b = ((double) sb * (1 - tick)) + ((double) eb * tick);
			pixel_color = SDL_MapRGBA(bg_surface->format, r, g, b, 0xff);
			radians = degrees / 180 * 3.14159265359;
			int x = cos(radians) * steps;
			int y = sin(radians) * steps;
			if(((x > 0) && (x < width / 2)) && ((y > 0) && (y < height / 2)))
				pixels[(y + h) * width + x + (w)] = pixel_color;
		}
	}

	// top edge fix
	for(int c = w; c < width ; c++)
	{
		pixel_color = pixels[(h + 1) * width + c];
		pixels[(h * width) + c] = pixel_color;
	}

	// left edge fix
	for(int r = h; r < height; r++)
	{
		pixel_color = pixels[width * r + w + 1];
		pixels[width * r + w] = pixel_color;
	}

	// mirror quarter to lower left corner
	for(int r = 0; r < h; r++)
	{
		for(int c = 0; c < w; c++)
		{
			pixel_color = pixels[((r + h) * width) + (c + w)];
			pixels[(r + h) * width + (w - 1 - c)] = pixel_color;
		}
	}

	// mirror bottom to top
	for(int r = 0; r < h; r++)
	{
		for(int c = 0; c < width; c++)
		{
			pixel_color = pixels[((r + h) * width) + c];
			pixels[((h - 1 - r) * width) + c] = pixel_color;
		}
	}

	// done. =)
}

void Game::changeBackgroundColor(int index)
{
	renderBackground(bg_colors[index].first, bg_colors[index].second);
	renderWindow();
}
