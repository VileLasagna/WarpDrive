#ifndef VOXEL_GRID_H
#define VOXEL_GRID_H

#include "BaseMaths/Vec3.hpp"
#include "Physics/CollisionSystem.hpp"


class VoxelGrid: public CollisionSystem
{

public:

	VoxelGrid();
	VoxelGrid(float Cellsize, int WorldSize);



};

#endif //VOXEL_GRID_H
