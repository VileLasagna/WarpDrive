#ifndef MODEL_H
#define MODEL_H

#include "3DMaths/Vertex.h"
#include "Display/Texture.h"
#include "BaseSystem/GameObject.h"
#include "3DMaths/ModelLoader.h"

#include <string>
#include <vector>

//typedef bool (*LoaderFunction) (); 

class Model:public GameObject
{
public:
	Model();
	Model(const std::string& filename);
	ModelLoader* Loader(const std::string& FileFormat, ModelLoader* L = 0); //0 gets the function, a pointer sets is to that.
	bool Load(ManagedFile*) override;
	const char* getType() const {return "Model";}
	void Draw() override;
	void Update() override;
	
private:

	std::vector<Vertex> VertexData;
	std::vector<Texture> Tex;

};


#endif //MODEL_H
