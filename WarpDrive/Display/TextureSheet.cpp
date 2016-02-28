#include "Display/TextureSheet.hpp"
#include <assert.h>

TextureSheet::TextureSheet()
{
    numCells = Vec2i(0,0);
	cellSize = Vec2i(0,0);

}

void TextureSheet::setNumCells(int x, int y)
{
    assert(image);

    numCells.setX(x);
    numCells.setY(y);
    cellSize.setX(surface->w / numCells.X());
    cellSize.setY(surface->h / numCells.Y());
}

void TextureSheet::setNumCells(Vec2i cells)
{
	setNumCells(cells.X(), cells.Y());
}

void TextureSheet::Blit(int cell, int x, int y) const
{
    assert(numCells.X());
    assert(numCells.Y());

	SDL_Rect src;
	src.w = cellSize.X();
	src.h = cellSize.Y();

	src.x = (cell % numCells.X()) * src.w;
	src.y = (cell / numCells.X()) * src.h; // yes X again, this is not a mistake!

	SDL_Rect dest;
	dest.x = x;
	dest.y = y;

    SDL_RenderCopy(DisplayManager::instance()->getRenderer(), image, &src, &dest );
}


void TextureSheet::Blit (Vec2i cell, int x, int y) const
{

    assert(numCells.X());
    assert(numCells.Y());

	SDL_Rect src;
	src.w = cellSize.X();
	src.h = cellSize.Y();

	src.x = (cell.X()-1) * src.w;
	src.y = (cell.Y()-1) * src.h;

	SDL_Rect dest;
	dest.x = x;
	dest.y = y;

    SDL_RenderCopy(DisplayManager::instance()->getRenderer(), image, &src, &dest );
}


unsigned int TextureSheet::getPixelColour(int cell, int x, int y) const
{
	return SDLImage::getPixelColour( (x + ( (cell%numCells.X())*cellSize.X() ) ) , (y + ( (cell/numCells.X())*cellSize.Y() ) ) );
}

bool TextureSheet::isPixTransparent(int cell, int x, int y) const
{
	return SDLImage::isPixTransparent( (x + ( (cell%numCells.X())*cellSize.X() ) ), (y + ( (cell/numCells.X())*cellSize.Y() ) ) );
}

unsigned int TextureSheet::getPixelColour(Vec2i cell, int x, int y) const
{
	return SDLImage::getPixelColour( (x + ( (cell.X()-1)*cellSize.X() ) ) , (y + ( (cell.Y()-1)*cellSize.Y() ) ) );
}

bool TextureSheet::isPixTransparent(Vec2i cell, int x, int y) const
{
	return SDLImage::isPixTransparent( (x + ( (cell.X()-1)*cellSize.X() ) ) , (y + ( (cell.Y()-1)*cellSize.Y() ) ) );
}
