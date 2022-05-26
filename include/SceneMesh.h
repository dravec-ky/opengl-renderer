#ifndef MESH_H_
#define MESH_H_

#include <ngl/AbstractMesh.h>
#include <ngl/AbstractVAO.h>
#include "SceneObject.h"
#include "ScenePrimitive.h"
#include <ngl/Obj.h>

struct Material
{
  ngl::Vec3 diffuse;
  ngl::Vec3 specular;
  ngl::Vec3 ambient;
  float shininess;
};

class MeshInfo: public ngl::Obj
{
  public:
    MeshInfo( const std::string& _fname, CalcBB _calcBB=CalcBB::True)  noexcept: ngl::Obj(_fname, _calcBB){};
    ngl::AbstractVAO * getRawVAO() {return m_vaoMesh.get();};
    ~MeshInfo(){};
};

//based on NGL's AbstractMesh and Obj classes, added support for triangulating faces while loading
class SceneMesh : public SceneObject
{
  public:
    SceneMesh(const std::string &_name, const std::string &_fname);
    SceneMesh(const std::string &_primname);
    //bool load(const std::string &_fname,CalcBB _calcBB=CalcBB::True) noexcept;
    void draw() override;
     ~SceneMesh();
    
  protected:
    void load(const std::string &path);
    Material m_shading_info;
    std::unique_ptr<ngl::AbstractVAO> m_vao;
    bool VAO_loaded = false;

    bool isObj;
    std::unique_ptr<ngl::Obj> m_obj;

};

#endif