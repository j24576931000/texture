#include "MeshObject.h"
#include <Eigen/Sparse>
#include <Eigen/Dense>
#include <map>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <cstdint>
#define Quad
//#define Harmonic

struct OpenMesh::VertexHandle const OpenMesh::PolyConnectivity::InvalidVertexHandle;

#pragma region MyMesh

MyMesh::MyMesh()
{
	request_face_normals();
	request_vertex_normals();
	request_vertex_status();
	request_face_status();
	request_edge_status();
}

MyMesh::~MyMesh()
{

}

int MyMesh::FindVertex(MyMesh::Point pointToFind)
{
	int idx = -1;
	for (MyMesh::VertexIter v_it = vertices_begin(); v_it != vertices_end(); ++v_it)
	{
		MyMesh::Point p = point(*v_it);
		if (pointToFind == p)
		{
			idx = v_it->idx();
			break;
		}
	}

	return idx;
}
int MyMesh::FindFace(MyMesh::Point pointToFind1, MyMesh::Point pointToFind2,MyMesh::Point pointToFind3)
{
	int idx = -1;
	std::vector<int>point_face1;
	std::vector<int>point_face2;
	int num = 0;
	for (MyMesh::VertexIter v_it = vertices_begin(); v_it != vertices_end(); ++v_it)
	{
		MyMesh::Point p = point(*v_it);
		if (pointToFind1 == p)
		{
			for (MyMesh::VertexFaceIter vf_it = vf_iter(*v_it); vf_it.is_valid(); ++vf_it)
			{
				point_face1.push_back(vf_it->idx());
			}
			break;
		}
	}
	for (MyMesh::VertexIter v_it = vertices_begin(); v_it != vertices_end(); ++v_it)
	{
		MyMesh::Point p = point(*v_it);
		if (pointToFind2 == p)
		{
			for (MyMesh::VertexFaceIter vf_it = vf_iter(*v_it); vf_it.is_valid(); ++vf_it)
			{
				if (std::find(point_face1.begin(), point_face1.end(), (*vf_it).idx()) != point_face1.end())
				{
					point_face2.push_back(vf_it->idx());
				}
			}
			break;
		}	
	}
	for (MyMesh::VertexIter v_it = vertices_begin(); v_it != vertices_end(); ++v_it)
	{
		MyMesh::Point p = point(*v_it);
		if (pointToFind3 == p)
		{
			for (MyMesh::VertexFaceIter vf_it = vf_iter(*v_it); vf_it.is_valid(); ++vf_it)
			{
				if (std::find(point_face2.begin(), point_face2.end(), (*vf_it).idx()) != point_face2.end())
				{
					idx=(vf_it->idx());					
				}
			}
			break;
		}		
	}	
	return idx;
}
void MyMesh::ClearMesh()
{
	if (!faces_empty())
	{
		for (MyMesh::FaceIter f_it = faces_begin(); f_it != faces_end(); ++f_it)
		{
			delete_face(*f_it, true);
		}

		garbage_collection();
	}
}

#pragma endregion

#pragma region GLMesh

GLMesh::GLMesh()
{

}

GLMesh::~GLMesh()
{

}

bool GLMesh::Init(std::string fileName)
{
	if (LoadModel(fileName))
	{
		LoadToShader();
		return true;
	}
	return false;
}


bool GLMesh::LoadModel(std::string fileName)
{
	OpenMesh::IO::Options ropt;
	if (OpenMesh::IO::read_mesh(mesh, fileName, ropt))
	{
		if (!ropt.check(OpenMesh::IO::Options::VertexNormal) && mesh.has_vertex_normals())
		{
			mesh.request_face_normals();
			mesh.request_edge_status();
			//mesh.request_edge_position();
			mesh.update_normals();
			mesh.release_face_normals();
		}

		return true;
	}

	return false;
}
bool GLMesh::SaveModel(std::string fileName)
{
	bool isSave = false;
	if (OpenMesh::IO::write_mesh(mesh, fileName))
	{
		isSave = true;
	}
	return isSave;
}

void GLMesh::LoadToShader()
{
	std::vector<MyMesh::Point> vertices;
	vertices.reserve(mesh.n_vertices());
	for (MyMesh::VertexIter v_it = mesh.vertices_begin(); v_it != mesh.vertices_end(); ++v_it)
	{
		vertices.push_back(mesh.point(*v_it));

		MyMesh::Point p = mesh.point(*v_it);
	}

	std::vector<MyMesh::Normal> normals;
	normals.reserve(mesh.n_vertices());
	for (MyMesh::VertexIter v_it = mesh.vertices_begin(); v_it != mesh.vertices_end(); ++v_it)
	{
		normals.push_back(mesh.normal(*v_it));
	}

	std::vector<unsigned int> indices;
	indices.reserve(mesh.n_faces() * 3);
	for (MyMesh::FaceIter f_it = mesh.faces_begin(); f_it != mesh.faces_end(); ++f_it)
	{
		for (MyMesh::FaceVertexIter fv_it = mesh.fv_iter(*f_it); fv_it.is_valid(); ++fv_it)
		{
			indices.push_back(fv_it->idx());
		}
	}

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vboVertices);
	glBindBuffer(GL_ARRAY_BUFFER, vboVertices);
	glBufferData(GL_ARRAY_BUFFER, sizeof(MyMesh::Point) * vertices.size(), &vertices[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glGenBuffers(1, &vboNormal);
	glBindBuffer(GL_ARRAY_BUFFER, vboNormal);
	glBufferData(GL_ARRAY_BUFFER, sizeof(MyMesh::Normal) * normals.size(), &normals[0], GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * indices.size(), &indices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}
#pragma endregion

MeshObject::MeshObject()
{

}

MeshObject::~MeshObject()
{
}

bool MeshObject::Init(std::string fileName)
{
	selectedFace.clear();

	return model.Init(fileName);
}
bool MeshObject::End(std::string fileName)
{
	//selectedFace.clear();
	return model.SaveModel(fileName);
}

void MeshObject::Render()
{
	glBindVertexArray(model.vao);
	glDrawElements(GL_TRIANGLES, model.mesh.n_faces() * 3, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void MeshObject::RenderSelectedFace()
{
	if (selectedFace.size() > 0)
	{

		std::vector<unsigned int*> offsets(selectedFace.size());
		for (int i = 0; i < offsets.size(); ++i)
		{
			offsets[i] = (GLuint*)(selectedFace[i] * 3 * sizeof(GLuint));
		}

		std::vector<int> count(selectedFace.size(), 3);

		glBindVertexArray(model.vao);
		glMultiDrawElements(GL_TRIANGLES, &count[0], GL_UNSIGNED_INT, (const GLvoid **)&offsets[0], selectedFace.size());
		glBindVertexArray(0);
	}
}

bool MeshObject::AddSelectedFace(unsigned int faceID)
{
	if (multi_select == true)//multi-select
	{
		multiselect(faceID);
	}
	else if (multi_select == false&&edit_num == 2)//other_mesh_increase
	{
		if (std::find(selectedFace.begin(), selectedFace.end(), faceID) == selectedFace.end() &&
			faceID >= 0 && faceID < model.mesh.n_faces())
		{
			selectedFace.push_back(faceID);
		}
		if (std::find(boundary.begin(), boundary.end(), faceID) == boundary.end() &&
			faceID >= 0 && faceID < model.mesh.n_faces())
		{
			boundary.push_back(faceID);
		}	
	}
	
	else if (edit == true&&edit_mode==true&& edit_num==1&& multi_select == false)//mesh_move
	{
		mesh_move(faceID);
	}
	else//normal select
	{
		if (std::find(selectedFace.begin(), selectedFace.end(), faceID) == selectedFace.end() &&
			faceID >= 0 && faceID < model.mesh.n_faces() )
		{
			selectedFace.push_back(faceID);
		}			
	}

	return false;
}
bool MeshObject::AddSelectedFacefinished()
{
	multi_select = false;
	model.mesh2.ClearMesh();
	start_time = clock();
	for (int i = 0; i < selectedFace.size(); i++)//把選到的面的點都記起來
	{      	
		for (MyMesh::FaceVertexIter fv_it = model.mesh.fv_iter((OpenMesh::ArrayKernel::FaceHandle)selectedFace[i]); fv_it.is_valid(); ++fv_it)
		{
			if (std::find(selectedpoint.begin(), selectedpoint.end(), *fv_it) == selectedpoint.end())
			{
				selectedpoint.push_back(*fv_it);
			}
			model.mesh.property(pp, *fv_it) = model.mesh.point(*fv_it);//每個點map到它的頂點座標(x,y,z)

		}
	}

	//add point到new mesh
	for (int i = 0; i < selectedpoint.size(); i++)
	{
		vhandle.push_back(model.mesh2.add_vertex(MyMesh::Point(model.mesh.point(selectedpoint[i]))));//add選的點到new mesh
		model.mesh.property(vertexId, selectedpoint[i]) = vhandle[i];//對應新舊點vertex ID
	}
	//add face到new mesh
	std::vector<MyMesh::VertexHandle>  face_vhandles;

	for (int i = 0; i < selectedFace.size(); i++)
	{
		for (MyMesh::FaceVertexIter fv_it = model.mesh.fv_iter((OpenMesh::ArrayKernel::FaceHandle)selectedFace[i]); fv_it.is_valid(); ++fv_it)
		{
			face_vhandles.push_back(model.mesh.property(vertexId, *fv_it));
		}
		model.mesh2.add_face(face_vhandles);
		face_vhandles.clear();
	}

	vhandle.clear();
	model.mesh_tex[mesh_id] = model.mesh2;

	selectedpoint.clear();
	if (edit_num != 3)
	{
		new_mesh_info();
	}
	return true;
}
void MeshObject::new_mesh_info()
{
	model.mesh2.add_property(adjacent_point_num_ID);

	model.mesh2.add_property(change_innerpoints_ID);
	//測試存邊界的點
	model.mesh2.add_property(pp2);

	for (MyMesh::VertexIter v_it = model.mesh2.vertices_begin(); v_it != model.mesh2.vertices_end(); ++v_it)
	{
		for (MyMesh::VertexVertexIter vv_it = model.mesh2.vv_iter(*v_it); vv_it.is_valid(); ++vv_it)
		{
			//找內部點的相鄰的點
			if (!model.mesh2.is_boundary(*v_it))
			{
				if (model.mesh2.is_boundary(*vv_it))
				{
					model.mesh2.property(adjacent_point_num_ID, *v_it).push_back(*vv_it);
				}
			}
		}
		if (!model.mesh2.is_boundary(*v_it))
		{
			model.mesh2.property(change_innerpoints_ID, *v_it) = inner_point_num;//單獨重編內部點編號
			inner_point_num++;//算解線性系統時的矩陣大小
		}
		//紀錄邊界點
		if (model.mesh2.is_boundary(*v_it))
		{
			model.mesh2.property(change_innerpoints_ID, *v_it) = -1;
			model.mesh2.property(pp2, *v_it) = model.mesh2.point(*v_it);//存邊界的點
		}
	}
	model.mesh2.remove_property(pp2);
	
	CaculateWeight();

}
void MeshObject::CaculateWeight()
{
	double cotan_alpha = 0;
	double cotan_beta = 0;
	double wij = 0;
	const float eps = 1e-6f;
	const float cotan_max = cos(eps) / sin(eps);
	model.mesh2.add_property(weight);
	std::cout << "weight correct" << std::endl;
	for (MyMesh::EdgeIter e_it = model.mesh2.edges_begin(); e_it != model.mesh2.edges_end(); ++e_it)
	{
		if (!model.mesh2.is_boundary(*e_it))
		{
			TriMesh::HalfedgeHandle heh, heh_next, heh2, heh_next2;
			OpenMesh::ArrayKernel::VertexHandle   vertex_j, vertex_j_next, vertex_j_prev, vertex_i;
			heh = model.mesh2.halfedge_handle(*e_it, 1);//左邊
			heh2 = model.mesh2.halfedge_handle(*e_it, 0);//右邊

			vertex_j = model.mesh2.from_vertex_handle(heh);//<---------------------------------------------vertex_j
			vertex_i = model.mesh2.to_vertex_handle(heh);//<---------------------------------------------vertex_i

			heh_next = model.mesh2.next_halfedge_handle(heh);
			heh_next2 = model.mesh2.next_halfedge_handle(heh2);

			vertex_j_next = model.mesh2.to_vertex_handle(heh_next);//<---------------------------------------------vertex_j_next
			vertex_j_prev = model.mesh2.to_vertex_handle(heh_next2);//<---------------------------------------------vertex_j_prev

			OpenMesh::Vec3f v1 = model.mesh2.point(vertex_i) - model.mesh2.point(vertex_j);
			OpenMesh::Vec3f v2 = model.mesh2.point(vertex_i) - model.mesh2.point(vertex_j_prev);
			OpenMesh::Vec3f v3 = model.mesh2.point(vertex_j_prev) - model.mesh2.point(vertex_j);
			OpenMesh::Vec3f v4 = model.mesh2.point(vertex_i) - model.mesh2.point(vertex_j_next);
			OpenMesh::Vec3f v5 = model.mesh2.point(vertex_j_next) - model.mesh2.point(vertex_j);
			float e1 = v1.norm();
			float e2 = v2.norm();
			float e3 = v3.norm();
			float e4 = v4.norm();
			float e5 = v5.norm();
			cotan_alpha = fabs((e3*e3 + e2 * e2 - e1 * e1) / (2.0f*e3*e2));
			cotan_beta = fabs((e4*e4 + e5 * e5 - e1 * e1) / (2.0f*e4*e5));
			float cotan1 = cotan_alpha / sqrt(1.0f - cotan_alpha * cotan_alpha);
			float cotan2 = cotan_beta / sqrt(1.0f - cotan_beta * cotan_beta);
			wij = (cotan1 + cotan2) / 2.0f;
			if (wij >= cotan_max) {
				wij = cotan_max;
			}
			model.mesh2.property(weight, *e_it) = wij;
		}
	}
	//檢查weights
	/*for (MyMesh::EdgeIter e_it = model.mesh2.edges_begin(); e_it != model.mesh2.edges_end(); ++e_it)
	{
		std::cout << "====================================" << std::endl;
		std::cout<< *e_it <<" weight= "<<model.mesh2.property(weight, *e_it)<<std::endl;
	}*/
	step3();
}
void MeshObject::step3()
{

	std::vector<float>dis;
	float dis_total = 0, dis_tmp = 0;
	model.mesh2.add_property(v_2d);
	//1.挑一個點繞boundary的邊  2.算距離
	for (MyMesh::HalfedgeIter e_it = model.mesh2.halfedges_begin(); e_it != model.mesh2.halfedges_end(); ++e_it)
	{
		if (model.mesh2.is_boundary(*e_it))
		{
			TriMesh::HalfedgeHandle heh, heh_next;

			heh = model.mesh2.halfedge_handle(model.mesh2.to_vertex_handle(*e_it));//1.挑一個點繞boundary的邊
			v_boundary.push_back(model.mesh2.to_vertex_handle(heh));//1.挑一個點繞boundary的邊			
			dis.push_back(distance(model.mesh2.point(model.mesh2.to_vertex_handle(heh)) - model.mesh2.point(model.mesh2.from_vertex_handle(heh)))); //2.算距離

			while (*e_it != heh)
			{
				heh = model.mesh2.halfedge_handle(model.mesh2.to_vertex_handle(heh));//1.挑一個點繞boundary的邊
				v_boundary.push_back(model.mesh2.to_vertex_handle(heh));//1.挑一個點繞boundary的邊
				dis.push_back(distance(model.mesh2.point(model.mesh2.to_vertex_handle(heh)) - model.mesh2.point(model.mesh2.from_vertex_handle(heh))));//2.算距離
			}
			break;
		}
	}
	//算周長
	for (int i = 0; i < dis.size(); i++)
	{
		dis_total = dis_total + dis[i];
	}

	//map到貼圖座標
	for (int i = 1; i < v_boundary.size(); i++)
	{
		dis_tmp = dis_tmp + dis[i] / dis_total * 4;
		model.mesh2.property(v_2d, v_boundary[0]) = OpenMesh::Vec2f(0, 0);//(x,0)

		if ((0 + dis_tmp) <= 1)
		{
			model.mesh2.property(v_2d, v_boundary[i]) = OpenMesh::Vec2f(0 + dis_tmp, 0);//(x,0)			
		}
		else if ((0 + dis_tmp) > 1 && (0 + dis_tmp) <= 2)
		{
			model.mesh2.property(v_2d, v_boundary[i]) = OpenMesh::Vec2f(1, (dis_tmp - 1));//(1,y)
		}
		else if ((0 + dis_tmp) > 2 && (0 + dis_tmp) <= 3)
		{
			model.mesh2.property(v_2d, v_boundary[i]) = OpenMesh::Vec2f(1 - (dis_tmp - 2), 1);//(x,1)
		}
		else if ((0 + dis_tmp) > 3 && (0 + dis_tmp) < 4)
		{
			model.mesh2.property(v_2d, v_boundary[i]) = OpenMesh::Vec2f(0, 1 - (dis_tmp - 3));//(0,y)
		}
		else if ((0 + dis_tmp) >= 4)
		{
			model.mesh2.property(v_2d, v_boundary[i]) = OpenMesh::Vec2f(0, 0);//(0,0)
		}
	}
	//查看map到的點
	//for (MyMesh::VertexIter v_it = model.mesh2.vertices_begin(); v_it != model.mesh2.vertices_end(); ++v_it)
	//{
		//std::cout << "貼圖座標"<<*v_it<<" *v_it "<< model.mesh2.property(v_2d, *v_it) << std::endl;
	//}
	//查看點的順序
	/*for (int i = 0; i < v_boundary.size(); i++)
	{

		std::cout << v_boundary[i] << std::endl;
	}*/

	dis.clear();
	dis_total = 0;
	dis_tmp = 0;
	v_boundary.clear();

	if (inner_point_num > 0)
	{
		step4();
	}
	else
	{
		model.mesh_tex[mesh_id] = model.mesh2;
		struct Mesh_tex_record record;
		//最後點的位置
		for (MyMesh::VertexIter v_it = model.mesh2.vertices_begin(); v_it != model.mesh2.vertices_end(); ++v_it)
		{
			record.mesh_id = mesh_id;
			record.x.push_back(model.mesh2.property(v_2d, *v_it)[0]);
			record.y.push_back(model.mesh2.property(v_2d, *v_it)[1]);
		}
		if (new_mesh == 0)//對已存在的貼圖mesh編輯
			mesh_record[mesh_id] = record;
		else//新的貼圖mesh
			mesh_record.push_back(record);

		LoadToShader2();
	}
}
//填矩陣並解Ax=b
void MeshObject::step4()
{
	model.mesh2.add_property(X);
	model.mesh2.add_property(Y);
	model.mesh2.add_property(fun_weight);
	std::vector< std::vector<float>> vertexnewID;
	std::vector<float>  vertexto;
	for (int i = 0; i < inner_point_num; i++)
	{
		for (int j = 0; j < inner_point_num; j++)
		{
			vertexto.push_back(0);
		}
		vertexnewID.push_back(vertexto);
		vertexto.clear();
	}
	//處理含邊界點的邊的w*p和處理中間不含邊界點的邊的w
	for (MyMesh::EdgeIter e_it = model.mesh2.edges_begin(); e_it != model.mesh2.edges_end(); ++e_it)
	{
		TriMesh::HalfedgeHandle heh;
		if (!model.mesh2.is_boundary(*e_it))
		{
			heh = model.mesh2.halfedge_handle(*e_it, 0);
			
			if (model.mesh2.is_boundary(model.mesh2.to_vertex_handle(heh)))//b矩陣，w*p
			{
				OpenMesh::Vec2f v2 = model.mesh2.property(v_2d, model.mesh2.to_vertex_handle(heh));

				model.mesh2.property(X, model.mesh2.to_vertex_handle(heh)) = v2[0] * model.mesh2.property(weight, *e_it);//point.x*weight
				model.mesh2.property(Y, model.mesh2.to_vertex_handle(heh)) = v2[1] * model.mesh2.property(weight, *e_it);//point.y*weight
				model.mesh2.property(fun_weight, model.mesh2.to_vertex_handle(heh)) = model.mesh2.property(weight, *e_it);//weight
			}
			else if (model.mesh2.is_boundary(model.mesh2.from_vertex_handle(heh)))//b矩陣，w*p
			{
				OpenMesh::Vec2f v1 = model.mesh2.property(v_2d, model.mesh2.from_vertex_handle(heh));

				model.mesh2.property(X, model.mesh2.from_vertex_handle(heh)) = v1[0] * model.mesh2.property(weight, *e_it);//point.x*weight
				model.mesh2.property(Y, model.mesh2.from_vertex_handle(heh)) = v1[1] * model.mesh2.property(weight, *e_it);//point.y*weight
				model.mesh2.property(fun_weight, model.mesh2.from_vertex_handle(heh)) = model.mesh2.property(weight, *e_it);//weight
			}
			else if (!model.mesh2.is_boundary(model.mesh2.from_vertex_handle(heh)) && !model.mesh2.is_boundary(model.mesh2.to_vertex_handle(heh)))//A矩陣w
			{
				int tmp = 0, tmp2 = 0;
				if (model.mesh2.property(change_innerpoints_ID, model.mesh2.from_vertex_handle(heh)) > model.mesh2.property(change_innerpoints_ID, model.mesh2.to_vertex_handle(heh)))
				{
					tmp = model.mesh2.property(change_innerpoints_ID, model.mesh2.to_vertex_handle(heh));
					tmp2 = model.mesh2.property(change_innerpoints_ID, model.mesh2.from_vertex_handle(heh));
					vertexnewID[tmp][tmp2] = model.mesh2.property(weight, *e_it);
				}
				else if (model.mesh2.property(change_innerpoints_ID, model.mesh2.from_vertex_handle(heh)) < model.mesh2.property(change_innerpoints_ID, model.mesh2.to_vertex_handle(heh)))
				{
					tmp = model.mesh2.property(change_innerpoints_ID, model.mesh2.from_vertex_handle(heh));
					tmp2 = model.mesh2.property(change_innerpoints_ID, model.mesh2.to_vertex_handle(heh));
					vertexnewID[tmp][tmp2] = model.mesh2.property(weight, *e_it);
				}
			}
		}
	}
	//讓ji邊同步跟ij邊變一樣，A矩陣01和10位置值是一樣的，以此類推
	for (int i = 0; i < vertexnewID.size(); i++)
	{
		for (int j = 0; j < vertexnewID[i].size(); j++)
		{
			vertexnewID[j][i] = vertexnewID[i][j];
		}

	}
	//處理B向量  和   大W部分
	std::vector<double> funx;
	std::vector<double> funy;
	std::vector<double> funweight;
	std::vector<double> funx_total_final;
	std::vector<double> funy_total_final;
	std::vector<double> funweight_total_final;
	double funx_total = 0, funy_total = 0, funweight_total = 0;
	for (MyMesh::VertexIter v_it = model.mesh2.vertices_begin(); v_it != model.mesh2.vertices_end(); ++v_it)
	{
		if (!model.mesh2.is_boundary(*v_it))
		{
			for (int i = 0; i < model.mesh2.property(adjacent_point_num_ID, *v_it).size(); i++)
			{
				//std::cout <<"與 "<< *v_it <<" 相鄰的有 "<< model.mesh2.property(adjacent_point_num_ID, *v_it)[i] << std::endl;
				funx.push_back(model.mesh2.property(X, (model.mesh2.property(adjacent_point_num_ID, *v_it)[i])));//相鄰點x，b矩陣
				funy.push_back(model.mesh2.property(Y, (model.mesh2.property(adjacent_point_num_ID, *v_it)[i])));//相鄰點y，b矩陣
				funweight.push_back(model.mesh2.property(fun_weight, (model.mesh2.property(adjacent_point_num_ID, *v_it)[i])));//W，A矩陣
			}

			for (int i = 0; i < funx.size(); i++)
			{
				funx_total += funx[i];//<-------------------------------------相鄰點x總和，b矩陣
				funy_total += funy[i];//<-------------------------------------相鄰點y總和，b矩陣
				funweight_total += funweight[i];//<---------------------------W，A矩陣
			}
			funx_total_final.push_back(funx_total);
			funy_total_final.push_back(funy_total);
			funweight_total_final.push_back(funweight_total);

			funx_total = 0;
			funy_total = 0;
			funweight_total = 0;
			funx.clear();
			funy.clear();
			funweight.clear();
		}
	}

	//這邊開始使用Eigen解線性方程(least square solution)
	int time=clock();
	//填入A矩陣
	int size = inner_point_num;
	SparseMatrix<double, Eigen::ColMajor> inner_points_edge(size, size);
	for (int i = 0; i < size; i++)
	{
		for (int j = i + 1; j < size; j++)
		{
			if (vertexnewID[i][j] != 0)
			{
				inner_points_edge.insert(i, j) = inner_points_edge.insert(j, i) = -(vertexnewID[i][j]);
				funweight_total_final[i] += vertexnewID[i][j];
			}
		}
		for (int k = i - 1; k >= 0; k--)
		{
			if (vertexnewID[i][k] != 0)
			{
				funweight_total_final[i] += vertexnewID[i][k];
			}
		}
		inner_points_edge.insert(i, i) = funweight_total_final[i];
	}

	int time2 = clock();
	std::cout << "time  "<<time2- time << std::endl;

	//填入b矩陣，x座標
	inner_points_edge.makeCompressed();
	VectorXd B(size);
	for (int i = 0; i < B.size(); i++)
	{
		B[i] = funx_total_final[i];
	}

	//填入b矩陣，y座標
	VectorXd C(size);
	for (int i = 0; i < C.size(); i++)
	{
		C[i] = funy_total_final[i];;
	}

	int start = clock();

	Eigen::SimplicialCholesky<SparseMatrix<double >> linearSolver(inner_points_edge.transpose()*inner_points_edge);//開始解LS
	//SparseQR<SparseMatrix<double>, COLAMDOrdering<int>> linearSolver;
	linearSolver.compute(inner_points_edge);
	int end = clock();
	std::cout << "linearSolver time  " <<  end- start << std::endl;


	VectorXd X = linearSolver.solve(B);//取出解完的內部點x座標矩陣
	VectorXd Y = linearSolver.solve(C);//取出解完的內部點y座標矩陣
	
	//把算出的點存回 property(v_2d)
	for (int i = 0; i < X.size(); i++)
	{
		for (MyMesh::VertexIter v_it = model.mesh2.vertices_begin(); v_it != model.mesh2.vertices_end(); ++v_it)
		{
			if (i == model.mesh2.property(change_innerpoints_ID, *v_it))
			{
				model.mesh2.property(v_2d, *v_it) = OpenMesh::Vec2f(X[i], Y[i]);
			}
		}
	}

	struct Mesh_tex_record record;
	//最後點的位置
	for (MyMesh::VertexIter v_it = model.mesh2.vertices_begin(); v_it != model.mesh2.vertices_end(); ++v_it)
	{
		//std::cout << "FINAL============================================FINAL" << std::endl;
		//std::cout<<"第 "<< v_it<<" 個點位置 "<<model.mesh2.property(v_2d, *v_it)<<std::endl ;
		
		record.mesh_id = mesh_id;
		record.x.push_back(model.mesh2.property(v_2d, *v_it)[0]);
		//std::cout << "第 " << v_it << " 個點位置 " << model.mesh2.property(v_2d, *v_it)[0] << std::endl;
		record.y.push_back(model.mesh2.property(v_2d, *v_it)[1]);
		//std::cout << "第 " << v_it << " 個點位置 " << model.mesh2.property(v_2d, *v_it)[1] << std::endl;					
	}
	if(new_mesh == 0)//對已存在的貼圖mesh編輯
		mesh_record[mesh_id] = record;
	else//新的貼圖mesh
		mesh_record.push_back(record);

	funx_total_final.clear();
	funy_total_final.clear();
	funweight_total_final.clear();
	vertexnewID.clear();
	vertexto.clear();
	inner_point_num = 0;
	funx_total_final.clear();
	funy_total_final.clear();
	std::cout << "solve " << mesh_id << std::endl;
	model.mesh_tex[mesh_id] = model.mesh2;//解完存取來，mesh_id就是第幾張貼圖
	LoadToShader2();
}

void MeshObject::LoadToShader2()
{
	std::vector<MyMesh::Point> vertices2;
	vertices2.reserve(model.mesh2.n_vertices());
	for (MyMesh::VertexIter v_it = model.mesh2.vertices_begin(); v_it != model.mesh2.vertices_end(); ++v_it)
	{
		vertices2.push_back(model.mesh2.point(*v_it));
		//std::cout << "pos: " << model.mesh2.point(*v_it) << std::endl;
	}

	std::vector<MyMesh::Normal> normals2;
	normals2.reserve(model.mesh2.n_vertices());
	for (MyMesh::VertexIter v_it = model.mesh2.vertices_begin(); v_it != model.mesh2.vertices_end(); ++v_it)
	{
		OpenMesh::ArrayKernel::VertexHandle v2_p = (OpenMesh::ArrayKernel::VertexHandle)(model.mesh.FindVertex(model.mesh2.point(*v_it)));
		normals2.push_back(model.mesh.normal(v2_p));
		//std::cout << "normal: " << model.mesh.normal(v2_p) << std::endl;
	}

	std::vector<OpenMesh::Vec2f> texture2;
	texture2.reserve(model.mesh2.n_vertices());
	for (MyMesh::VertexIter v_it = model.mesh2.vertices_begin(); v_it != model.mesh2.vertices_end(); ++v_it)
	{
		texture2.push_back(model.mesh2.property(v_2d, *v_it));
		//std::cout <<"tex: "<< model.mesh2.property(v_2d, *v_it) <<std::endl;
	}

	std::vector<unsigned int> indices2;
	indices2.reserve(model.mesh2.n_faces() * 3);
	for (MyMesh::FaceIter f_it = model.mesh2.faces_begin(); f_it != model.mesh2.faces_end(); ++f_it)
	{
		for (MyMesh::FaceVertexCCWIter fv_it = model.mesh2.fv_ccwiter(*f_it); fv_it.is_valid(); ++fv_it)
		{
			indices2.push_back(fv_it->idx());
			//std::cout << "indices: " << fv_it->idx() << std::endl;
		}
	}

	std::vector<unsigned int> indices3;
	indices3.reserve(model.mesh2.n_edges() * 2);
	for (MyMesh::EdgeIter e_it = model.mesh2.edges_begin(); e_it != model.mesh2.edges_end(); ++e_it)
	{
		MyMesh::HalfedgeHandle now = model.mesh2.halfedge_handle(*e_it, 0);
		indices3.push_back((model.mesh2.to_vertex_handle(now)).idx());
		indices3.push_back((model.mesh2.from_vertex_handle(now)).idx());
	}

	glGenVertexArrays(1, &mesh_vao[mesh_id]);
	glBindVertexArray(mesh_vao[mesh_id]);

	glGenBuffers(1, &mesh_vboVertices[mesh_id]);
	glBindBuffer(GL_ARRAY_BUFFER, mesh_vboVertices[mesh_id]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(MyMesh::Point) * vertices2.size(), &vertices2[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glGenBuffers(1, &mesh_vboNormal[mesh_id]);
	glBindBuffer(GL_ARRAY_BUFFER, mesh_vboNormal[mesh_id]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(MyMesh::Normal) * normals2.size(), &normals2[0], GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	glGenBuffers(1, &mesh_texure[mesh_id]);
	glBindBuffer(GL_ARRAY_BUFFER, mesh_texure[mesh_id]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(OpenMesh::Vec2f) * texture2.size(), &texture2[0], GL_STATIC_DRAW);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(2);
	//std::cout << "texure: "<<model.mesh_tex[mesh_id].n_faces()<<" :id"<< mesh_id << std::endl;

	glGenBuffers(1, &mesh_ebo[mesh_id]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh_ebo[mesh_id]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * indices2.size(), &indices2[0], GL_STATIC_DRAW);

	glGenBuffers(1, &mesh_ebo_line[mesh_id]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh_ebo_line[mesh_id]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * indices3.size(), &indices3[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void MeshObject::Render_mesh2(int i)
{
	//std::cout << model.mesh_tex.size() << std::endl;
	//for (int i = 0; i < model.mesh_tex.size(); i++)
	//{
	glBindVertexArray(mesh_vao[i]);
	glBindBuffer(GL_ARRAY_BUFFER, mesh_vboVertices[i]);
	glBindBuffer(GL_ARRAY_BUFFER, mesh_vboNormal[i]);
	glBindBuffer(GL_ARRAY_BUFFER, mesh_texure[i]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh_ebo[i]);
	glDrawElements(GL_TRIANGLES, model.mesh_tex[i].n_faces() * 3, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	//}
}
void MeshObject::Render_TexCoord()
{
	glBindVertexArray(mesh_vao[mesh_id]);
	glBindBuffer(GL_ARRAY_BUFFER, mesh_vboVertices[mesh_id]);
	glBindBuffer(GL_ARRAY_BUFFER, mesh_vboNormal[mesh_id]);
	glBindBuffer(GL_ARRAY_BUFFER, mesh_texure[mesh_id]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh_ebo_line[mesh_id]);
	glDrawElements(GL_LINES, model.mesh2.n_edges() * 2, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}
void MeshObject::Render_TexCoord2()
{
	glBindVertexArray(mesh_vao[mesh_id]);
	glBindBuffer(GL_ARRAY_BUFFER, mesh_vboVertices[mesh_id]);
	glBindBuffer(GL_ARRAY_BUFFER, mesh_vboNormal[mesh_id]);
	glBindBuffer(GL_ARRAY_BUFFER, mesh_texure[mesh_id]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh_ebo[mesh_id]);
	glDrawElements(GL_TRIANGLES, model.mesh2.n_faces() * 3, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}
void MeshObject::select_mesh(int mesh_num)
{
	new_mesh = 0;
	mesh_id = mesh_num;
	model.mesh2.ClearMesh();
	selectedFace.clear();
	selectedpoint.clear();
	//model.mesh2 = model.mesh_tex[mesh_id];
	
	for (MyMesh::FaceIter f_it = model.mesh_tex[mesh_id].faces_begin(); f_it != model.mesh_tex[mesh_id].faces_end(); ++f_it)
	{
		for (MyMesh::FaceVertexIter fv_it = model.mesh_tex[mesh_id].fv_iter(*f_it); fv_it.is_valid(); ++fv_it)
		{
			MyMesh::Point p1 = model.mesh_tex[mesh_id].point(*fv_it);
			++fv_it;
			MyMesh::Point p2 = model.mesh_tex[mesh_id].point(*fv_it);
			++fv_it;
			MyMesh::Point p3 = model.mesh_tex[mesh_id].point(*fv_it);
			int now = model.mesh.FindFace(p1, p2,p3);
			AddSelectedFace(now);
		}
	}	
	AddSelectedFacefinished();
}
void MeshObject::create_mesh()
{
	new_mesh = 1;
	model.mesh2.ClearMesh();
	selectedFace.clear();
	selectedpoint.clear();
	tex_X.clear();
	tex_Y.clear();
	model.mesh.remove_property(pp);
	model.mesh.remove_property(vertexId);
	model.mesh2.remove_property(adjacent_point_num_ID);
	model.mesh2.remove_property(change_innerpoints_ID);
	model.mesh2.remove_property(weight);
	model.mesh2.remove_property(X);
	model.mesh2.remove_property(Y);
	model.mesh2.remove_property(fun_weight);
	model.mesh_tex.push_back(model.mesh_blank);
	model.mesh.add_property(pp);
	model.mesh.add_property(vertexId);	
    mesh_id = model.mesh_tex.size() - 1;
	mesh_vao.push_back(0);
	mesh_vboVertices.push_back(0);
	mesh_vboNormal.push_back(0);
	mesh_texure.push_back(0);
	mesh_ebo.push_back(0);
	mesh_ebo_line.push_back(0);
	std::cout << "create" << std::endl;
}
void MeshObject::increase_face()
{
	new_mesh = 0;
	std::vector<int> face_id;
	std::vector<int>mesh2_boundary;			
	for (MyMesh::VertexIter v_it = model.mesh_tex[mesh_id].vertices_begin(); v_it != model.mesh_tex[mesh_id].vertices_end(); ++v_it)
	{
		if (model.mesh_tex[mesh_id].is_boundary(*v_it))
		{
			int boundary_p = model.mesh.FindVertex(model.mesh_tex[mesh_id].point(*v_it));
			mesh2_boundary.push_back(boundary_p);
		}
	}
	for (int i = 0; i < selectedFace.size(); i++)
	{
		face_id.push_back(selectedFace[i]);
	}
	for (int i = 0; i < mesh2_boundary.size(); i++)
	{
		for (MyMesh::VertexFaceIter vf_it = model.mesh.vf_iter((OpenMesh::ArrayKernel::VertexHandle)mesh2_boundary[i]); vf_it.is_valid(); ++vf_it)
		{
			face_id.push_back((*vf_it).idx());
		}
	}

	/*for (int i = 0; i < selectedFace.size(); i++)
	{
		std::cout << selectedFace[i] << std::endl;
	}
	for (int i = 0; i < selectedpoint.size(); i++)
	{
		std::cout << selectedpoint[i] << std::endl;
	}*/
	model.mesh2.ClearMesh();
	selectedFace.clear();
	selectedpoint.clear();
	model.mesh.add_property(pp);
	for (int i = 0; i < face_id.size(); i++)
	{		
		AddSelectedFace(face_id[i]);
	}
	face_id.clear();
	AddSelectedFacefinished();
	/*for (MyMesh::VertexIter v_it = model.mesh_tex[mesh_id].vertices_begin(); v_it != model.mesh_tex[mesh_id].vertices_end(); ++v_it)
	{
		if (model.mesh_tex[mesh_id].is_boundary(*v_it))
		{
			std::cout << " this: "<<*v_it << std::endl;
		}
	}*/

}
void MeshObject::decrease_face()
{
	new_mesh = 0;
	std::vector<int> face_id;
	std::vector<int>mesh2_boundary;
	for (MyMesh::VertexIter v_it = model.mesh2.vertices_begin(); v_it != model.mesh2.vertices_end(); ++v_it)
	{
		if (model.mesh2.is_boundary(*v_it))
		{
			int boundary = model.mesh.FindVertex(model.mesh2.point(*v_it));
			mesh2_boundary.push_back(boundary);
		}

	}
	for (int i = 0; i < mesh2_boundary.size(); i++)
	{
		for (MyMesh::VertexFaceIter vf_it = model.mesh.vf_iter((OpenMesh::ArrayKernel::VertexHandle)mesh2_boundary[i]); vf_it.is_valid(); ++vf_it)
		{
			DeleteSelectedFace((*vf_it).idx());

		}
	}
	for (int i = 0; i < selectedFace.size(); i++)
	{
		face_id.push_back(selectedFace[i]);
	}


	model.mesh2.ClearMesh();
	selectedFace.clear();
	selectedpoint.clear();
	model.mesh.add_property(pp);
	for (int i = 0; i < face_id.size(); i++)
	{
		AddSelectedFace(face_id[i]);

	}
	face_id.clear();
	AddSelectedFacefinished();
}

void MeshObject::mesh_move(unsigned int faceID)
{
	model.mesh2.ClearMesh();
	model.mesh_tex[mesh_id].ClearMesh();
	selectedFace.clear();
	selectedpoint.clear();
	edit = false;
	AddSelectedFace(faceID);
	std::vector<OpenMesh::ArrayKernel::VertexHandle>used_point;
	edit_num = 3;
	while (model.mesh_tex[mesh_id].n_faces() < origin_face_num)
	{		
		increase_face();

	}	
	int extra_face = 0,internal_face=0;
	for (MyMesh::FaceIter f_it = model.mesh_tex[mesh_id].faces_begin(); f_it != model.mesh_tex[mesh_id].faces_end(); ++f_it)
	{
		if (model.mesh_tex[mesh_id].is_boundary(*f_it))
		{
			extra_face++;
		}
		if (!model.mesh_tex[mesh_id].is_boundary(*f_it))
		{
			internal_face++;
		}
	}	
	edit_num = 1;
	new_mesh_info();
	edit = true;	
}
void MeshObject::multiselect(unsigned int faceID)
{
	multi_select = false;
	AddSelectedFace(faceID);
	std::vector<int>used_point;
	std::vector<int>used_point2;
	/*for (int i = 0; i < selectedFace.size(); i++)
	{
		used_point.push_back(selectedFace[i]);
	}*/
	for (MyMesh::FaceFaceIter ff_it = model.mesh.ff_iter((OpenMesh::ArrayKernel::FaceHandle)faceID); ff_it.is_valid(); ++ff_it)
	{
		AddSelectedFace((*ff_it).idx());
		used_point.push_back((*ff_it).idx());
	}
	for (int j = 0; j < 4; j++)
	{
		for (int i = 0; i < used_point.size(); i++)
		{
			for (MyMesh::FaceFaceIter ff_it = model.mesh.ff_iter((OpenMesh::ArrayKernel::FaceHandle)used_point[i]); ff_it.is_valid(); ++ff_it)
			{
				AddSelectedFace((*ff_it).idx());
				used_point2.push_back((*ff_it).idx());
			}
		}
		used_point.clear();
		for (int i = 0; i < used_point2.size(); i++)
		{
			for (MyMesh::FaceFaceIter ff_it = model.mesh.ff_iter((OpenMesh::ArrayKernel::FaceHandle)used_point2[i]); ff_it.is_valid(); ++ff_it)
			{
				AddSelectedFace((*ff_it).idx());
				used_point.push_back((*ff_it).idx());
			}
		}
		used_point2.clear();
	}
	edit_num = 1;
	//new_mesh_info();
	multi_select = true;
}
void MeshObject::face_num()
{	
	origin_face_num = model.mesh_tex[mesh_id].n_faces() ;
}
void MeshObject::other_mesh_increase()
{
	edit_num = 3;
	for (int i = 0; i < boundary.size(); i++)
	{
		DeleteSelectedFace(boundary[i]);
	}
	edit_num = 2;
	
	edit_num = 3;
	bool flag = true;
	int num = 0;
	int numlast = 0;
	int time = 0;
	while (flag == true)
	{
		if(other_increase==0)
			other_mesh_increase_face();
		else if(other_increase == 1)
			increase_face();
		int total = boundary.size();
		
		//num++;
		//std::cout << "boundary.size() " << total << std::endl;
		
		for (int i = 0; i < boundary.size(); i++)
		{

			if (std::find(selectedFace.begin(), selectedFace.end(), boundary[i]) != selectedFace.end())
			{
				num++;
				//std::cout << "看 "<< num<< std::endl;
			}

		}
		//std::cout << "time" << num << std::endl;
		if (total == num)
		{
			flag = false;
		}
		/*if (numlast = num&&num!=0)
		{
			time++;
		}
		if (time == 3)
		{
			time = 0;
			flag = false;
		}*/
		//numlast = num;
		
		num = 0;
	}	
	edit_num = 2;
	new_mesh_info();
	end_time = clock();
	std::cout<< "total time :"<< end_time-start_time <<std::endl;
}
void MeshObject::other_mesh_increase_face()
{
	new_mesh = 0;
	std::vector<int> face_id;
	std::vector<int>mesh2_boundary_face;
	std::vector<int>mesh2_boundary_face_ring;
	for (MyMesh::FaceIter f_it = model.mesh_tex[mesh_id].faces_begin(); f_it != model.mesh_tex[mesh_id].faces_end(); ++f_it)
	{
		if (model.mesh_tex[mesh_id].is_boundary(*f_it))
		{			
				for (MyMesh::FaceVertexIter fv_it = model.mesh_tex[mesh_id].fv_iter(*f_it); fv_it.is_valid(); ++fv_it)
				{
					MyMesh::Point p1 = model.mesh_tex[mesh_id].point(*fv_it);
					++fv_it;
					MyMesh::Point p2 = model.mesh_tex[mesh_id].point(*fv_it);
					++fv_it;
					MyMesh::Point p3 = model.mesh_tex[mesh_id].point(*fv_it);
					int boundary_f = model.mesh.FindFace(p1, p2, p3);
					if (std::find(boundary.begin(), boundary.end(), boundary_f) == boundary.end())
						mesh2_boundary_face.push_back(boundary_f);
				}			
		}
	}
	for (int i = 0; i < selectedFace.size(); i++)
	{
		face_id.push_back(selectedFace[i]);
	}
	for (int i = 0; i < mesh2_boundary_face.size(); i++)
	{
		for (MyMesh::FaceFaceIter ff_it = model.mesh.ff_iter((OpenMesh::ArrayKernel::FaceHandle)mesh2_boundary_face[i]); ff_it.is_valid(); ++ff_it)
		{
			face_id.push_back((*ff_it).idx());
		}
	}
	model.mesh2.ClearMesh();
	selectedFace.clear();
	selectedpoint.clear();
	model.mesh.add_property(pp);
	for (int i = 0; i < face_id.size(); i++)
	{
		AddSelectedFace(face_id[i]);
	}
	face_id.clear();
	AddSelectedFacefinished();

}
void MeshObject::load_tex_info_vector(float x, float y)
{
	tex_X.push_back(x);
	tex_Y.push_back(y);
	//std::cout << "X " << tex_X.size() << '\n';
	//std::cout << "Y " << tex_Y.size() << '\n';
}
void MeshObject::load_tex_info()
{
	
	model.mesh2.add_property(v_2d);
	for (int i = 0; i < tex_X.size(); i++)
	{			
		model.mesh2.property(v_2d, (OpenMesh::ArrayKernel::VertexHandle)i) = OpenMesh::Vec2f(tex_X[i], tex_Y[i]);		
	}
	std::cout << "tex_info_finish"<<std::endl;
	struct Mesh_tex_record record;
	//最後點的位置
	for (MyMesh::VertexIter v_it = model.mesh2.vertices_begin(); v_it != model.mesh2.vertices_end(); ++v_it)
	{
		record.mesh_id = mesh_id;
		record.x.push_back(model.mesh2.property(v_2d, *v_it)[0]);
		record.y.push_back(model.mesh2.property(v_2d, *v_it)[1]);				
	}
	if (new_mesh == 0)
		mesh_record[mesh_id] = record;
	else
		mesh_record.push_back(record);
	std::cout << " size " << mesh_record.size() << std::endl;
	std::cout <<  "點數 " << mesh_record[mesh_id].x.size() << std::endl;
	LoadToShader2();
	
}
float MeshObject::cotan(OpenMesh::Vec3f a, OpenMesh::Vec3f b) {
	return (a | b) / (a%b).norm();
}
float MeshObject::distance(OpenMesh::Vec3f a) {

	return  a.norm();
}
const std::vector<std::string>  MeshObject::split(const std::string &str, const char &delimiter) {
	std::vector<std::string> result;
	std::stringstream ss(str);
	std::string tok;

	while (std::getline(ss, tok, delimiter)) {
		result.push_back(tok);
	}
	return result;
}

void MeshObject::DeleteSelectedFace(unsigned int faceID)
{
	selectedFace.erase(std::remove(selectedFace.begin(), selectedFace.end(), faceID), selectedFace.end());
	//is_used.erase(std::remove(is_used.begin(), is_used.end(), faceID), is_used.end());
	if (edit_num == 2)
	{
		boundary.erase(std::remove(boundary.begin(), boundary.end(), faceID), boundary.end());
	}
}

bool MeshObject::FindClosestPoint(unsigned int faceID, glm::vec3 worldPos, glm::vec3& closestPos)
{
	OpenMesh::FaceHandle fh = model.mesh.face_handle(faceID);
	if (!fh.is_valid())
	{
		return false;
	}

	double minDistance = 0.0;
	MyMesh::Point p(worldPos.x, worldPos.y, worldPos.z);
	MyMesh::FVIter fv_it = model.mesh.fv_iter(fh);
	MyMesh::VertexHandle closestVH = *fv_it;
	MyMesh::Point v1 = model.mesh.point(*fv_it);
	++fv_it;

	minDistance = (p - v1).norm();
	for (; fv_it.is_valid(); ++fv_it)
	{
		MyMesh::Point v = model.mesh.point(*fv_it);
		double distance = (p - v).norm();
		if (minDistance > distance)
		{
			minDistance = distance;
			closestVH = *fv_it;
		}
	}
	MyMesh::Point closestPoint = model.mesh.point(closestVH);
	closestPos.x = closestPoint[0];
	closestPos.y = closestPoint[1];
	closestPos.z = closestPoint[2];
	return true;
}
