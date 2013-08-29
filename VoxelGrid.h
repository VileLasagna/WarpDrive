#ifndef VOXEL_GRID_H
#define VOXEL_GRID_H

#include "Vec3.h"
#include "CollisionSystem.h"


class VoxelGrid: public CollisionSystem
{

public:

	VoxelGrid();
	VoxelGrid(float Cellsize, int WorldSize);



};

#endif //VOXEL_GRID_H