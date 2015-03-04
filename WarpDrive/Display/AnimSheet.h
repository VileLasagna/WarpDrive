#ifndef ANIMSHEET_H
#define ANIMSHEET_H

#include "Display/TextureSheet.h"
#include <vector>
#include <iostream>
#include "BaseMaths/Vec2.h"
#include <string>
#include <fstream>
#include <utility>
#include "BaseSystem/StringProc.h"

class AnimSheet : public TextureSheet

{
public:

	AnimSheet(std::string filename); // I COULD provide a default constructor and make things settable and all but no. It's best this way.

	Vec2i getSize() const {return cellSize;}
	Vec2i getCells() const {return numCells;}
	Vec2i getAdjust() const {return adjust;}
	Vec2i nextSprite(Vec2i current) const; //will be called by the play animation loops
	std::vector<std::pair<Vec2<Vec2i>,int> > getAnims() const; //Returns a vector with the start and end of each animation (in order) for this sheet
												// would've been an array, but the having a checkable size is important here
	int getCellIndex(const Vec2i& cell) const; //returns the cell's number
	virtual ~AnimSheet(){}
	
	/*	Vec2<Vec2i> > allows for empty cells trailing after the end of an animation in a cell before
	 *	the end of the sheet. Like the first animation ending in the 10th cell in a 15 cell wide sheet.
	 *	With this level of information it becomes safe for the next animation to simply start at the next
	 *	row, thus potentially preventing lots of work fixing the damn thing.
	 *	Note that I AM assuming, however, that all animations are contiguous and that there are
	 *	no blank spots between one frame and another within the same animation.
	 */

	//Inherited:

   // void Blit(int cell, int x, int y);
	

private:

	int anims;
	int* lengths;
	std::vector<std::pair<std::vector<Vec2i>, int> > animations; // because a Vec2i** doesn't really work ¬¬
	void loadseq (const std::string& s);
	int pass;
	Vec2i adjust; 
	/* if this sheet is part of a larger sprite set 
	   and has an irregular sprite size, this is the 
	   amount by which the position of the top left
	   corner of this set of sprites should be adjusted
	   in order for the sprites to remain aligned.
	 */


};
#endif //ANIMSHEET_H
