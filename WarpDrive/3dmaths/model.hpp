#ifndef WD_MODEL_HPP_DEFINED
#define WD_MODEL_HPP_DEFINED

#include "WarpDrive/3dmaths/vertex.hpp"
#include "WarpDrive/display/texture.hpp"
#include "WarpDrive/basesystem/gameobject.hpp"
#include "WarpDrive/3dmaths/modelloader.hpp"

#include <string>
#include <vector>

//typedef bool (*LoaderFunction) ();

class Model:public GameObject
{
public:
    Model() noexcept;
    Model(const std::string& filename);
    ModelLoader* Loader(const std::string& FileFormat, ModelLoader* L = 0); //0 gets the function, a pointer sets is to that.
    bool load(ManagedFile*) override;
    const char* Type() const override {return "Model";}
    void draw() const override;
    void update() override;

private:

    std::vector<Vertex> VertexData;
    std::vector<WDTexture> Tex;

};

#endif //WD_MODEL_HPP_DEFINED
