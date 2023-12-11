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

	std::vector<struct Mesh_tex_record> mesh_record;//�s�K�Ϫ�mesh
	std::vector<unsigned int> boundary;//other_mesh_increase�Mother_mesh_increase_face�Ϊ�
	const std::vector<std::string> split(const std::string &str, const char &delimiter);
	std::vector<float> tex_X;//Ū��x�y��
	std::vector<float> tex_Y;//Ū��y�y��

	GLMesh model;
	//OpenGL
	GLuint vao2;
	GLuint ebo2;
	GLuint vboVertices2, vboNormal2, tex2;
	GLuint ebo3;

	//����s��
	bool edit = false;
	bool edit_mode = false;
	int edit_num = 1;

	int new_mesh = 0;//�O�_���smesh
	int mesh_id;//�ĴX�i�K�Ϫ�mesh
	int origin_face_num = 0;//���X��face�Amesh_move��
	int other_increase = 1;
	bool multi_select = false;

private:
	
	std::vector<unsigned int> selectedFace;
	std::vector<OpenMesh::ArrayKernel::VertexHandle> selectedpoint;
	std::vector<MyMesh::VertexHandle> vhandle;//�B�z�s���Imappping�ɥ�

	OpenMesh::VPropHandleT<MyMesh::Point> pp;//�s�쥻�C�ӿ�쪺�I���y��
	OpenMesh::VPropHandleT<MyMesh::Point> pp2;//new mesh��ɪ��I
	OpenMesh::VPropHandleT<OpenMesh::ArrayKernel::VertexHandle> vertexId;//�s�smesh��vertex ��property
	
	OpenMesh::EPropHandleT<float> weight;//�sweight

	int inner_point_num = 0;//���X�Ӥ����I
	OpenMesh::VPropHandleT<int> change_innerpoints_ID;//���s�����I�s��
	OpenMesh::VPropHandleT< std::vector<MyMesh::VertexHandle> > adjacent_point_num_ID;//�O�����I���۾F�Ione_ring

	std::vector<MyMesh::VertexHandle> v_boundary; //�B�z����Imapping�쥿��ΤW�ɥ�

	OpenMesh::VPropHandleT<float> X;//point.x*weight
	OpenMesh::VPropHandleT<float> Y;//point.y*weight
	OpenMesh::VPropHandleT<float> fun_weight;//weight
	
	OpenMesh::VPropHandleT<OpenMesh::Vec2f> v_2d;//�smap�쪺�I��m

	//OpenGL
	std::vector<GLuint> mesh_vao;
	std::vector<GLuint> mesh_texure;
	std::vector<GLuint> mesh_vboVertices;
	std::vector<GLuint> mesh_vboNormal;
	std::vector<GLuint> mesh_ebo;
	std::vector<GLuint> mesh_ebo_line;

	//���ɶ�
	int start_time ;
	int end_time ;

};

