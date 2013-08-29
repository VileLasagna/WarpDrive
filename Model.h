#ifndef MODEL_H
#define MODEL_H

#include "Vertex.h"
#include "Texture.h"
#include "GameObject.h"
#include "ModelLoader.h"

#include <string>
#include <Vector>

//typedef bool (*LoaderFunction) (); 

class Model:public GameObject
{
public:
	Model();
	Model(const std::string& filename);
	ModelLoader* Loader(const std::string& FileFormat, ModelLoader* L = 0); //0 gets the function, a pointer sets is to that.
	bool Load(const std::string& filename);
	const char* getType() const {return "Model";}
	void Draw();
	void Update();
	
private:

	std::vector<Vertex> VertexData;
	std::vector<Texture> Tex;

};


#endif //MODEL_H