#ifndef TEXTURE_SHEET_H
#define TEXTURE_SHEET_H

#include "display/sdlimage.hpp"
#include "basemaths/vec2.hpp"
#include "basesystem/displaymanager.hpp"

class TextureSheet : public SDLImage
{
public:
    TextureSheet();
    void setNumCells(int x, int y);
	void setNumCells(Vec2i cells);
    void Blit(int cell, int x, int y) const; //x and y are the coordinates of the top-left corner of the containing rectangle
	void Blit(Vec2i cell, int x, int y) const;
	virtual ~TextureSheet() {}
	bool isPixTransparent(int cell, int x, int y) const;
	bool isPixTransparent(Vec2i cell, int x, int y) const;
	unsigned int getPixelColour(int cell, int x, int y) const;
	unsigned int getPixelColour(Vec2i cell, int x, int y) const;


protected:
	Vec2i numCells;
	Vec2i cellSize;
};

#endif
