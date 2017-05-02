#ifndef WD_CLIP_LINE_SEG_BOX_HPP_DEFINED
#define WD_CLIP_LINE_SEG_BOX_HPP_DEFINED

#include "WarpDrive/basemaths/lineseg.hpp"
#include "WarpDrive/physics/alignedboundingbox.hpp"

// Clips the given line segment against the given bounding box.
// Returns false if the line is completely clipped; returns true
//  if there is all or some of the line seg left after clipping.
// The line seg pointed to by clipped will be set to the clipped
//  remnant of the original line seg, if clipped is not zero.
bool Clip(const LineSeg& lineSeg, const AABBox& box, LineSeg* clipped = nullptr) noexcept;

#endif //WD_CLIP_LINE_SEG_BOX_HPP_DEFINED
