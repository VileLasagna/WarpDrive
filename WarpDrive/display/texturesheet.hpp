#ifndef WD_TEXTURE_SHEET_HPP_DEFINED
#define WD_TEXTURE_SHEET_HPP_DEFINED

#include "display/sdlimage.hpp"
#include "basemaths/vec2.hpp"
#include "basesystem/displaymanager.hpp"

class TextureSheet : public SDLImage
{

public:

    TextureSheet();
    void setNumCells(int x, int y);
	void setNumCells(Vec2i cells);
    void blit(int cell, int x, int y) const; //x and y are the coordinates of the top-left corner of the containing rectangle
    void blit(Vec2i cell, int x, int y) const;
	virtual ~TextureSheet() {}
	bool isPixTransparent(int cell, int x, int y) const;
	bool isPixTransparent(Vec2i cell, int x, int y) const;
	unsigned int PixelColour(int cell, int x, int y) const;
	unsigned int PixelColour(Vec2i cell, int x, int y) const;

protected:

	Vec2i numCells;
	Vec2i cellSize;
};

#endif //WD_TEXTURE_SHEET_HPP_DEFINED
