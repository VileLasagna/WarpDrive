#include "WarpDrive/basemaths/cliplinesegbox.hpp"

// Valid points on the line seg are m_start + t * m_direction for
//  t in [0..1] for x, y and z.
// As we check the line against the planes of the box, we reduce 
//  the valid range of t. It starts at [t0.. t1] where t0 starts at 0,
//  and t1 starts at 1.
//
// First we check for intersection with the min. x plane of the box.
// i.e. we solve for m_start.x + t * m_direction.x == box.minx.
// so t = (box.minx - m_start.x) / m_direction.x.
// We can call m_direction.x the denominator, and 
//  (box.minx - m_start.x) the numerator.
//
// If m_direction.x is 0, we are parallel to the box plane. In this
//  case we are either inside or outside the plane: inside if
//  m_start.x >= box.minx, in other words if the numerator is pos.
// If m_direction.x is positive (the line is moving to the right): 
//  We check if t > t1, t < t0, or to < t < t1.
//  If t > t1 the line seg is to the left of the plane - return false.
//  If t < t0 the line seg is to the right of the plane, so ret true.
//  Otherwise the line is clipped. t0 now becomes t.
// If m_direction.x is negative, it's the same idea but in the opposite
//  direction.
//  If t < t0, the line is completely to the left of the plane.
//  If t > t1, the line is completely on the right.
//  Otherwise the line is clipped; the new value for t1 is t.

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-prototypes"

bool ClipAxis(
    float min, float max, float start, float direction, 
    float& t0, float& t1)
{
    if (direction > 0)
    {
        // Moving right
	   auto t = (min - start) / direction;
        if (t > t1)
        {
            return false; // completely clipped
        }
        if (t > t0)
        {
            t0 = t;
        }
    }
    else if (direction < 0)
    {
        // Moving left
	   auto t = (min - start) / direction;
        if (t < t0)
        {
            return false;
        }
        if (t < t1)
        {
            t1 = t;
        }
    }
    else if (start < min)
    {
        return false;
    }


    // Check against box max X
    if (direction > 0)
    {
        // Moving right
	   auto t = (max - start) / direction;
        if (t < t0)
        {
            return false;
        }
        if (t < t1)
        {
            t1 = t;
        }
    }
    else if (direction < 0)
    {
	   auto t = (max - start) / direction;
        if (t > t1)
        {
            return false;
        }
        if (t > t0)
        {
            t0 = t;
        }
    }
    else if (start > max)
    {
        return false;
    }

    return true;
}

#pragma clang diagnostic pop

bool Clip(const LineSeg& ls, const AABBox& box, LineSeg* clipped) noexcept
{
    float t0 = 0;
    float t1 = 1.0f;

    if (!ClipAxis(box.MinX(), box.MaxX(), ls.Start().X(), (ls.End()-ls.Start()).X(), t0, t1))
    {
        return false;
    }

    if (!ClipAxis(box.MinY(), box.MaxY(), ls.Start().Y(), (ls.End()-ls.Start()).Y(), t0, t1))
    {
        return false;
    }

    if (!ClipAxis(box.MinZ(), box.MaxZ(), ls.Start().Z(), (ls.End()-ls.Start()).Z(), t0, t1))
    {
        return false;
    }

    if (clipped != nullptr)
    {
        *clipped = LineSeg(
            ls.Start() + (ls.End()-ls.Start()) * t0,
            (ls.End()-ls.Start()) * (t1 - t0));
    }

    return true;
}

