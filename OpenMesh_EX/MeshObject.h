#pragma once

#include <string>
#include <OpenMesh/Core/IO/MeshIO.hh>
#include <OpenMesh/Core/Mesh/TriMesh_ArrayKernelT.hh>
#include <OpenMesh/Core/System/config.h>
#include <OpenMesh/Core/Mesh/Status.hh>
#include <Eigen/Dense>
#include <Eigen/Eigen>
#include "Common.h"
#include <time.h>
typedef OpenMesh::TriMesh_ArrayKernelT<>  TriMesh;
using namespace Eigen;
class MyMesh : public TriMesh
{
public:
	MyMesh();
	~MyMesh();

	int FindVertex(MyMesh::Point pointToFind);
	int FindFace(MyMesh::Point pointToFind1, MyMesh::Point pointToFind2, MyMesh::Point pointToFind3);
	void ClearMesh();
};


class GLMesh
{
public:
	GLMesh();
	~GLMesh();

	bool Init(std::string fileName);
	void Render();
	bool SaveModel(std::string fileName);
	void GetModel(unsigned int faceID, std::vector<unsigned int> selectedFace);
	MyMesh mesh;
	MyMesh mesh2;
	MyMesh mesh_blank;
	std::vector<MyMesh> mesh_tex;
	// generate vertices

	GLuint vao;
	GLuint ebo;
	GLuint vboVertices, vboNormal;
	GLuint vao2;
	GLuint ebo2;
	GLuint vboVertices2, vboNormal2, tex2;
	void LoadToShader();
	void LoadToShader2();
private:

	bool LoadModel(std::string fileName);

	//void caculateUV();

};
//struct Mesh_record {
//	int mesh_id;
//	std::vector<unsigned int> mesh_face;
//};
class MeshObject
{
public:
	MeshObject();
	~MeshObject();

	bool Init(std::string fileName);
	void Render();
	void Render_mesh2(int);
	void Render_TexCoord();
	void Render_TexCoord2();
	void RenderSelectedFace();
	bool AddSelectedFace(unsigned int faceID);
	void DeleteSelectedFace(unsigned int faceID);
	bool FindClosestPoint(unsigned int faceID, glm::vec3 worldPos, glm::vec3& closestPos);
	bool AddSelectedFacefinished();
	void CaculateWeight();
	void step3();
	void step4();
	float cotan(OpenMesh::Vec3f a, OpenMesh::Vec3f b);
	float distance(OpenMesh::Vec3f a);
	//float MeshObject::cotan(const VectorXf &a, const  VectorXf& b);
	bool End(std::string fileName);
	GLuint vao2;
	GLuint ebo2;
	GLuint vboVertices2, vboNormal2, tex2;
	GLuint ebo3;
	void LoadToShader2();
	void increase_face();
	void decrease_face();
	void create_mesh();
	GLMesh model;
	void select_mesh(int);
	int change_mesh = 0;
	int mesh_id;
	void mesh_move(unsigned int);
	bool edit = false;
	bool edit_mode = false;
	//std::vector<struct mesh_record> mesh_record;
private:

	std::vector<unsigned int> selectedFace;
	std::vector<OpenMesh::ArrayKernel::VertexHandle> selectedpoint;
	std::vector<MyMesh::Point> point;
	//std::vector<unsigned int*> fvIDsPtr;
	std::vector<int> elemCount;
	std::vector<MyMesh::VertexHandle> vhandle;
	OpenMesh::EPropHandleT<MyMesh::Edge> ep;
	OpenMesh::VPropHandleT<MyMesh::Point> pp;
	OpenMesh::VPropHandleT<MyMesh::Point> pp2;

	//OpenMesh::VPropHandleT<MyMesh::Point> ppnew;
	OpenMesh::VPropHandleT<MyMesh::Point> notinbound;//存非邊界vertex 的property

	OpenMesh::VPropHandleT<OpenMesh::ArrayKernel::VertexHandle> vertexId;//存新mesh的vertex 的property


	std::vector<MyMesh::VertexHandle> v_boundary;
	OpenMesh::EPropHandleT<float> weight;//存weight



	int inner_point_num = 0;//有幾個內部點
	//int adjacent_point_num = 0;//內部點有幾個相鄰的點
	OpenMesh::VPropHandleT<float> X;//
	OpenMesh::VPropHandleT<float> Y;//
	OpenMesh::VPropHandleT<float> fun_weight;//
	OpenMesh::VPropHandleT<int> change_innerpoints_ID;//

	OpenMesh::VPropHandleT< std::vector<MyMesh::VertexHandle> > adjacent_point_num_ID;//


	OpenMesh::VPropHandleT<OpenMesh::Vec2f> v_2d;//存map到的點位置







	std::vector<GLuint> mesh_vao;
	std::vector<GLuint> mesh_texure;
	std::vector<GLuint> mesh_vboVertices;
	std::vector<GLuint> mesh_vboNormal;
	std::vector<GLuint> mesh_ebo;
	std::vector<GLuint> mesh_ebo_line;



};

