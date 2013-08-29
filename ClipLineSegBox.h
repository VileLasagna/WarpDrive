#ifndef CLIP_LINE_SEG_BOX_H
#define CLIP_LINE_SEG_BOX_H

#include "LineSeg.h"
#include "BoundingBox.h"

// Clips the given line segment against the given bounding box.
// Returns false if the line is completely clipped; returns true
//  if there is all or some of the line seg left after clipping.
// The line seg pointed to by clipped will be set to the clipped
//  remnant of the original line seg, if clipped is not zero.
bool Clip(const LineSeg& lineSeg, const BBox& box, LineSeg* clipped = 0);

#endif