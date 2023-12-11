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
	//void LoadToShader2();
private:

	bool LoadModel(std::string fileName);
	//void caculateUV();
};
//struct Mesh_record {
//	int mesh_id;
//	std::vector<unsigned int> mesh_face;
//};
struct Mesh_tex_record {
	int mesh_id;
	std::vector<float> x;
	std::vector<float> y;
};
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
	void new_mesh_info();
	void CaculateWeight();
	void step3();
	void step4();
	float cotan(OpenMesh::Vec3f a, OpenMesh::Vec3f b);
	float distance(OpenMesh::Vec3f a);
	//float MeshObject::cotan(const VectorXf &a, const  VectorXf& b);
	bool End(std::string fileName);
	void LoadToShader2();
	void increase_face();
	void decrease_face();
	void create_mesh();
	void select_mesh(int);
	void mesh_move(unsigned int);
	void other_mesh_increase();
	void other_mesh_increase_face();
	void face_num();
	void load_tex_info_vector(float,float);
	void load_tex_info();
	void multiselect(unsigned int);

	std::vector<struct Mesh_tex_record> mesh_record;//存貼圖的mesh
	std::vector<unsigned int> boundary;//other_mesh_increase和other_mesh_increase_face用的
	const std::vector<std::string> split(const std::string &str, const char &delimiter);
	std::vector<float> tex_X;//讀檔x座標
	std::vector<float> tex_Y;//讀檔y座標

	GLMesh model;
	//OpenGL
	GLuint vao2;
	GLuint ebo2;
	GLuint vboVertices2, vboNormal2, tex2;
	GLuint ebo3;

	//控制編輯
	bool edit = false;
	bool edit_mode = false;
	int edit_num = 1;

	int new_mesh = 0;//是否為新mesh
	int mesh_id;//第幾張貼圖的mesh
	int origin_face_num = 0;//有幾個face，mesh_move用
	int other_increase = 1;
	bool multi_select = false;

private:
	
	std::vector<unsigned int> selectedFace;
	std::vector<OpenMesh::ArrayKernel::VertexHandle> selectedpoint;
	std::vector<MyMesh::VertexHandle> vhandle;//處理新舊點mappping時用

	OpenMesh::VPropHandleT<MyMesh::Point> pp;//存原本每個選到的點的座標
	OpenMesh::VPropHandleT<MyMesh::Point> pp2;//new mesh邊界的點
	OpenMesh::VPropHandleT<OpenMesh::ArrayKernel::VertexHandle> vertexId;//存新mesh的vertex 的property
	
	OpenMesh::EPropHandleT<float> weight;//存weight

	int inner_point_num = 0;//有幾個內部點
	OpenMesh::VPropHandleT<int> change_innerpoints_ID;//重編內部點編號
	OpenMesh::VPropHandleT< std::vector<MyMesh::VertexHandle> > adjacent_point_num_ID;//記內部點的相鄰點one_ring

	std::vector<MyMesh::VertexHandle> v_boundary; //處理邊界點mapping到正方形上時用

	OpenMesh::VPropHandleT<float> X;//point.x*weight
	OpenMesh::VPropHandleT<float> Y;//point.y*weight
	OpenMesh::VPropHandleT<float> fun_weight;//weight
	
	OpenMesh::VPropHandleT<OpenMesh::Vec2f> v_2d;//存map到的點位置

	//OpenGL
	std::vector<GLuint> mesh_vao;
	std::vector<GLuint> mesh_texure;
	std::vector<GLuint> mesh_vboVertices;
	std::vector<GLuint> mesh_vboNormal;
	std::vector<GLuint> mesh_ebo;
	std::vector<GLuint> mesh_ebo_line;

	//測時間
	int start_time ;
	int end_time ;

};

