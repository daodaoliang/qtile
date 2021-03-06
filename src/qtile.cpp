/*
 * =====================================================================================
 *
 *       Filename:  qtile.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/09/2014 15:28:35
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <SFML/Graphics.hpp>
#include "gameworld.h"
#include "tilemap.h"
#include "cartographer.h"
#include <iostream>
#define TILE_DIAMETER 25

int main(int argc, char **argv) {
  srand(time(NULL));
  gameworld *game_world = new gameworld((char*)"game",400,400);
  cartographer *_cartographer = new cartographer(); 
  tilemap *tile_map = new tilemap(game_world->get_window_size(),TILE_DIAMETER,game_world);

  tile_map->generate_map();
  
  sf::Vector2i start_t = tile_map->nominate_random_start();
  std::cout << "Start at ["<<start_t.x << ":" << start_t.y << "]" << std::endl;
  sf::Vector2i end_t = tile_map->nominate_random_end();
  std::cout << "End at ["<<end_t.x << ":" << end_t.y << "]" << std::endl;

  tile_map->generate_noise();

  //crux of the example
  std::list<tile*> *tile_path = _cartographer->generate_path(start_t,end_t,tile_map);

  tile_map->update_best_path(tile_path);

  delete tile_path;

  while(game_world->get_window()->isOpen()) {
    while(game_world->poll_event()) {
      if(game_world->get_event()->type == sf::Event::Closed) {
        game_world->get_window()->close();
      }
    }
    game_world->get_window()->clear(sf::Color::Black);
    tile_map->draw();

    game_world->get_window()->display();
  }
  return 0;
}
