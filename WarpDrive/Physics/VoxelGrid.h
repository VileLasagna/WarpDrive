#ifndef VOXEL_GRID_H
#define VOXEL_GRID_H

#include "BaseMaths/Vec3.h"
#include "Physics/CollisionSystem.h"


class VoxelGrid: public CollisionSystem
{

public:

	VoxelGrid();
	VoxelGrid(float Cellsize, int WorldSize);



};

#endif //VOXEL_GRID_H
