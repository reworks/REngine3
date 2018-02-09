///
/// TMXUtils.hpp
/// starlight
///
/// Created by reworks on 07/02/2018.
/// MIT License.
/// Refer to LICENSE.txt for more details.
///

#ifndef STARLIGHT_TMXUTILS_HPP_
#define STARLIGHT_TMXUTILS_HPP_

#include <allegro5/color.h>
#include <allegro5/bitmap_draw.h>
#include <allegro5/allegro_primitives.h>

#include "tmx/tmx.h"
#include "sl/core/World.hpp"
#include "sl/utils/Utils.hpp"
#include "sl/graphics/Window.hpp"
#include "sl/graphics/TextureAtlas.hpp"
#include "sl/components/SpriteComponent.hpp"
#include "sl/components/AnimationComponent.hpp"
#include "sl/components/TransformComponent.hpp"

/// Sorry...can't stand american english...
#define ALLEGRO_COLOUR ALLEGRO_COLOR

///
/// Most of the following code is taken from:
/// https://github.com/baylej/tmx/blob/master/examples/allegro/allegro.c
/// https://github.com/baylej/tmx/blob/master/examples/dumper/dumper.c
/// Code is licensed under the same license as the library (tmxlib):
/// BSD 2-Clause "Simplified" License
///
namespace sl
{
	namespace tmxutils
	{
		///
		/// The line thickness to draw objects with.
		/// Defaults to 1.0f.
		///
		static inline float LINE_THICKNESS = 1.0f;

		///
		/// Convert TMX colour to allegro colour.
		///
		static inline ALLEGRO_COLOUR intToColour(int colour, unsigned char opacity)
		{
			unsigned char r, g, b;

			r = (color >> 16) & 0xFF;
			g = (color >> 8) & 0xFF;
			b = (color) & 0xFF;

			return al_map_rgba(r, g, b, opacity);
		}

		///
		/// Draws a line. 
		///
		static inline void drawPolyline(double **points, double x, double y, int pointsc, ALLEGRO_COLOUR colour)
		{
			int i;
			for (i = 1; i<pointsc; i++) 
			{
				al_draw_line(x + points[i - 1][0], y + points[i - 1][1], x + points[i][0], y + points[i][1], colour, LINE_THICKNESS);
			}
		}

		///
		/// Draws a polygon.
		///
		static inline void drawPolygon(double **points, double x, double y, int pointsc, ALLEGRO_COLOUR colour)
		{
			drawPolyline(points, x, y, pointsc, color);
			if (pointsc > 2)
			{
				al_draw_line(x + points[0][0], y + points[0][1], x + points[pointsc - 1][0], y + points[pointsc - 1][1], colour, LINE_THICKNESS);
			}
		}

		///
		/// Draws tmx objects.
		///
		static inline void drawObjects(tmx_object_group *objgr)
		{
			ALLEGRO_COLOR color = intToColour(objgr->color);
			tmx_object *head = objgr->head;

			while (head)
			{
				if (head->visible)
				{
					if (head->obj_type == OT_SQUARE)
					{
						al_draw_rectangle(head->x, head->y, head->x + head->width, head->y + head->height, color, LINE_THICKNESS);
					}
					else if (head->obj_type == OT_POLYGON)
					{
						drawPolygon(head->content.shape->points, head->x, head->y, head->content.shape->points_len, color);
					}
					else if (head->obj_type == OT_POLYLINE)
					{
						drawPolyline(head->content.shape->points, head->x, head->y, head->content.shape->points_len, color);
					}
					else if (head->obj_type == OT_ELLIPSE)
					{
						al_draw_ellipse(head->x + head->width / 2.0, head->y + head->height / 2.0, head->width / 2.0, head->height / 2.0, color, LINE_THICKNESS);
					}
				}

				head = head->next;
			}
		}

		///
		/// Extracts tile gid flags.
		///
		static inline int gidExtractFlags(unsigned int gid)
		{
			int res = 0;

			if (gid & TMX_FLIPPED_HORIZONTALLY) res |= ALLEGRO_FLIP_HORIZONTAL;
			if (gid & TMX_FLIPPED_VERTICALLY)   res |= ALLEGRO_FLIP_VERTICAL;
			/* FIXME allegro has no diagonal flip */
			return res;
		}

		///
		/// Clear gid flags.
		///
		static inline unsigned int gidClearFlags(unsigned int gid)
		{
			return gid & TMX_FLIP_BITS_REMOVAL;
		}

		///
		/// Process the image layer(s).
		///
		static inline void processImageLayers(tmx_layer* layer)
		{
			float op = layer->opacity;
			World* world = World::inst();

			entt::Entity entity = world->m_registry.create();
			world->m_registry.assign<SpriteComponent>(entity, utils::removeExtension(layer->content.image->source), op);
			world->m_registry.assign<TransformComponent>(entity, tmx_get_property(layer->properties, "layer")->value.integer, 0.0f, {layer->offsetx, layer->offsety, layer->content.image->width, layer->content.image->height});
			world->m_inUse.push_back(entity);
		}

		///
		/// Process a tile layer.
		///
		static inline void processLayer(tmx_map *map, tmx_layer *layer)
		{
			unsigned long i, j;
			unsigned int gid, x, y, w, h, flags;
			unsigned int counter = 0;
			tmx_tileset *ts;
			tmx_image *im;
			std::string identifier;
			ALLEGRO_BITMAP* tileset;
			float op = layer->opacity;

			World* world = World::inst();
			entt::Entity entity = world->m_registry.create();
			world->m_registry.assign<TransformComponent>(entity, tmx_get_property(layer->properties, "layer")->value.integer, 0.0f, { layer->offsetx, layer->offsety, map->width, map->height });

			ALLEGRO_BITMAP* tileLayer = al_create_bitmap(map->width, map->height);
			al_set_target_bitmap(tileLayer);
			al_clear_to_color(intToColour(m_map->backgroundcolor, op));
			al_hold_bitmap_drawing(true);

			for (i = 0; i<map->height; i++)
			{
				for (j = 0; j<map->width; j++)
				{
					gid = gidClearFlags(layer->content.gids[(i*map->width) + j]);
					if (map->tiles[gid] != NULL)
					{
						if (!(map->tiles[gid]->animation))
						{
							ts = map->tiles[gid]->tileset;
							im = map->tiles[gid]->image;
							x = map->tiles[gid]->ul_x;
							y = map->tiles[gid]->ul_y;
							w = ts->tile_width;
							h = ts->tile_height;

							if (im)
							{
								identifier = utils::removeExtension(im->source);
								tileset = TextureAtlas::inst()->al_create_packed_sub_bitmap(identifier);
							}
							else
							{
								identifier = utils::removeExtension(ts->image->source);
								tileset = TextureAtlas::inst()->al_create_packed_sub_bitmap(identifier);
							}

							flags = gidExtractFlags(layer->content.gids[(i*map->width) + j]);
							al_draw_tinted_bitmap_region(tileset, al_map_rgba_f(0.0f, 0.0f, 0.0f, op), x, y, w, h, j*ts->tile_width, i*ts->tile_height, flags);
							al_destroy_bitmap(tileset);
						}
						else
						{
							ts = map->tiles[gid]->tileset;
							im = map->tiles[gid]->image;
							w = ts->tile_width;
							h = ts->tile_height;

							if (im)
							{
								identifier = utils::removeExtension(im->source);
							}
							else
							{
								identifier = utils::removeExtension(ts->image->source);
							}

							auto pr = TextureAtlas::inst()->get(entt::HashedString{ identifier });
							x = pr.m_x + map->tiles[gid]->ul_x;
							y = pr.m_y + map->tiles[gid]->ul_y;

							std::string id(layer->name);
							id += "AnimatedTile" + std::to_string(counter);
							TextureAtlas::addRectToAtlas(id, {x, y, w, h});

							entt::Entity animatedEntity = world->m_registry.create();
							world->m_registry.assign<TransformComponent>(animatedEntity, tmx_get_property(layer->properties, "layer")->value.integer, 0.0f, {j*ts->tile_width, i*ts->tile_height, w, h});
							world->m_registry.assign<SpriteComponent>(animatedEntity, id, op);
							world->m_registry.assign<AnimationComponent>(animatedEntity, map, map->tiles[gid], pr.m_x, pr.m_y, w, h, layer->name);
							world->m_inUse.push_back(animatedEntity);

							++counter;
						}
					}
				}
			}

			al_hold_bitmap_drawing(false);
			al_flip_display();
			al_set_target_backbuffer(Window::inst()->getDisplay());
			TextureAtlas::addTextureToAtlas(layer->name, tileLayer);
			al_destroy_bitmap(tileLayer);

			world->m_registry.assign<SpriteComponent>(entity, layer->name, op);
			world->m_inUse.push_back(entity);
		}

		static inline void draw_all_layers(tmx_map *map, tmx_layer *layers)
		{
			while (layers) {
				if (layers->visible) {
					if (layers->type == L_GROUP) {
						draw_all_layers(map, layers->content.group_head);
					}
					else if (layers->type == L_OBJGR) {
						draw_objects(layers->content.objgr);
					}
					else if (layers->type == L_IMAGE) {
						if (layers->opacity < 1.) {
							float op = layers->opacity;
							al_draw_tinted_bitmap((ALLEGRO_BITMAP*)layers->content.image->resource_image, al_map_rgba_f(op, op, op, op), 0, 0, 0);
						}
						al_draw_bitmap((ALLEGRO_BITMAP*)layers->content.image->resource_image, 0, 0, 0);
					}
					else if (layers->type == L_LAYER) {
						draw_layer(map, layers);
					}
				}
				layers = layers->next;
			}
		}
	}
}