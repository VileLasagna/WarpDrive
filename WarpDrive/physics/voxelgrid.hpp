#ifndef VOXEL_GRID_H
#define VOXEL_GRID_H

#include "basemaths/vec3.hpp"
#include "physics/collisionsystem.hpp"


class VoxelGrid: public CollisionSystem
{

public:

	VoxelGrid();
	VoxelGrid(float Cellsize, int WorldSize);



};

#endif //VOXEL_GRID_H
