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

/*void GLMesh::Render()
{
	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, mesh.n_faces() * 3, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}*/


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
void GLMesh::LoadToShader2()
{


	//std::vector<MyMesh::Point> vertices2;
	//vertices2.reserve(mesh.n_vertices());
	//for (MyMesh::VertexIter v_it = mesh2.vertices_begin(); v_it != mesh2.vertices_end(); ++v_it)
	//{
	//	vertices2.push_back(mesh2.point(*v_it));
	//}

	//std::vector<MyMesh::Normal> normals2;
	//normals2.reserve(mesh2.n_vertices());
	//for (MyMesh::VertexIter v_it = mesh2.vertices_begin(); v_it != mesh2.vertices_end(); ++v_it)
	//{
	//	normals2.push_back(mesh2.normal(*v_it));
	//}

	//std::vector<unsigned int> indices2;
	//indices2.reserve(mesh2.n_faces() * 3);
	//for (MyMesh::FaceIter f_it = mesh2.faces_begin(); f_it != mesh2.faces_end(); ++f_it)
	//{
	//	for (MyMesh::FaceVertexIter fv_it = mesh2.fv_iter(*f_it); fv_it.is_valid(); ++fv_it)
	//	{
	//		indices2.push_back(fv_it->idx());
	//	}
	//}

	//glGenVertexArrays(1, &vao2);
	//glBindVertexArray(vao2);

	//glGenBuffers(1, &vboVertices2);
	//glBindBuffer(GL_ARRAY_BUFFER, vboVertices2);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(MyMesh::Point) * vertices2.size(), &vertices2[0], GL_STATIC_DRAW);
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	//glEnableVertexAttribArray(0);

	//glGenBuffers(1, &vboNormal2);
	//glBindBuffer(GL_ARRAY_BUFFER, vboNormal2);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(MyMesh::Normal) * normals2.size(), &normals2[0], GL_STATIC_DRAW);
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	//glEnableVertexAttribArray(1);

	//glGenBuffers(1, &ebo2);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo2);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * indices2.size(), &indices2[0], GL_STATIC_DRAW);

	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	//glBindVertexArray(0);
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
	//std::cout << "faceID:   " << faceID << std::endl;
	if (std::find(selectedFace.begin(), selectedFace.end(), faceID) == selectedFace.end() &&
		faceID >= 0 && faceID < model.mesh.n_faces())
	{
		selectedFace.push_back(faceID);

		//for (MyMesh::FaceIter f_it = model.mesh.faces_begin(); f_it != model.mesh.faces_end(); ++f_it)
		//{			
			//for (int i = 0; i < selectedFace.size(); i++)
			//{					
				//if (*f_it == (const OpenMesh::ArrayKernel::FaceHandle)selectedFace[i])
				//{
		for (MyMesh::FaceVertexIter fv_it = model.mesh.fv_iter((OpenMesh::ArrayKernel::FaceHandle)faceID); fv_it.is_valid(); ++fv_it)
		{
			if (std::find(selectedpoint.begin(), selectedpoint.end(), *fv_it) == selectedpoint.end())
			{
				selectedpoint.push_back(*fv_it);
			}
			model.mesh.property(pp, *fv_it) = model.mesh.point(*fv_it);
			//std::cout << *fv_it << ":   " << model.mesh.property(pp, *fv_it) << std::endl;					
		}
		//}		
	//}
//}
		return true;
	}
	return false;
}
bool MeshObject::AddSelectedFacefinished()
{
	std::cout << "fun2" << std::endl;
	for (int i = 0; i < selectedFace.size(); i++)
	{
		//std::cout << "selectedFace :  " << selectedFace[i] << std::endl;
	}
	for (int i = 0; i < selectedpoint.size(); i++)
	{
		//std::cout << "selectedpoint :  " << selectedpoint[i] << std::endl;
	}
	//刪掉上一次選的點
	/*if (!model.mesh2.vertices_empty())
	{
		for (MyMesh::VertexIter v_it = model.mesh2.vertices_begin(); v_it != model.mesh2.vertices_end(); ++v_it)
		{
			model.mesh2.delete_vertex(*v_it, true);
		}

		model.mesh2.garbage_collection();
	}*/
	//std::cout << "111111111111111111111111   " << std::endl;
	//add選的點到new mesh和對應新舊點vertex ID
	for (int i = 0; i < selectedpoint.size(); i++)
	{
		vhandle.push_back(model.mesh2.add_vertex(MyMesh::Point(model.mesh.point(selectedpoint[i]))));
		model.mesh.property(vertexId, selectedpoint[i]) = vhandle[i];
		//std::cout  << "add選的點到new mesh和對應新舊點vertex ID:   " << model.mesh.property(vertexId, selectedpoint[i]) << std::endl;
	}
	//std::cout << "2222222222222222222222222   " << std::endl;
	//add face到new mesh
	std::vector<MyMesh::VertexHandle>  face_vhandles;
	//for (MyMesh::FaceIter f_it = model.mesh.faces_begin(); f_it != model.mesh.faces_end(); ++f_it)
	//{
	for (int i = 0; i < selectedFace.size(); i++)
	{
		//if (*f_it == (const OpenMesh::ArrayKernel::FaceHandle)selectedFace[i])
		//{
		face_vhandles.clear();
		for (MyMesh::FaceVertexIter fv_it = model.mesh.fv_iter((OpenMesh::ArrayKernel::FaceHandle)selectedFace[i]); fv_it.is_valid(); ++fv_it)
		{
			face_vhandles.push_back(model.mesh.property(vertexId, *fv_it));
			//std::cout <<  "add face到new mesh:   " << model.mesh.property(vertexId, *fv_it) << std::endl;
		}
		model.mesh2.add_face(face_vhandles);
		//}
	}
	//}
	//std::cout << "333333333333333333333333333333" << std::endl;
	model.mesh2.add_property(adjacent_point_num_ID);
	std::cout << "adjacent_point_num_ID correct" << std::endl;
	model.mesh2.add_property(change_innerpoints_ID);
	std::cout << "change_innerpoints_ID correct" << std::endl;
	//測試存邊界的點
	model.mesh2.add_property(pp2);
	std::cout << "pp2 correct" << std::endl;
	for (MyMesh::VertexIter v_it = model.mesh2.vertices_begin(); v_it != model.mesh2.vertices_end(); ++v_it)
	{
		//std::cout << " 看這裡*v_it   : " << *v_it << std::endl;
		for (MyMesh::VertexVertexIter vv_it = model.mesh2.vv_iter(*v_it); vv_it.is_valid(); ++vv_it)
		{
			if (!model.mesh2.is_boundary(*v_it))
			{
				//std::cout <<  " 看這裡*vv_it   : "<<*vv_it  << std::endl;
				//adjacent_point_num ++;
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

		if (model.mesh2.is_boundary(*v_it))
		{
			model.mesh2.property(change_innerpoints_ID, *v_it) = -1;
			model.mesh2.property(pp2, *v_it) = model.mesh2.point(*v_it);//存邊界的點
			//std::cout << *v_it << " *v_it:   " << model.mesh2.property(pp2, *v_it) << std::endl;
		}
	}
	model.mesh2.remove_property(pp2);
	//model.mesh2.remove_property(ep);
	face_vhandles.clear();
	vhandle.clear();
	CaculateWeight();
	return true;
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

			//std::cout << model.mesh2.to_vertex_handle(heh) << std::endl;
			vertex_j = model.mesh2.from_vertex_handle(heh);//<---------------------------------------------vertex_j

			//std::cout << vertex_j << std::endl;
			//std::cout << model.mesh2.from_vertex_handle(heh) << std::endl;
			vertex_i = model.mesh2.to_vertex_handle(heh);//<---------------------------------------------vertex_i
			/*std::cout << vertex_i << std::endl;

			std::cout << model.mesh2.to_vertex_handle(heh2) << std::endl;
			std::cout << model.mesh2.from_vertex_handle(heh2) << std::endl;
			std::cout << "heh: " << heh << std::endl;
			std::cout << "heh2: " << heh2 << std::endl;
			std::cout << "---------------------------------------- " << std::endl;*/
			heh_next = model.mesh2.next_halfedge_handle(heh);
			heh_next2 = model.mesh2.next_halfedge_handle(heh2);
			//heh_pre = model.mesh2.prev_halfedge_handle(heh);
			//std::cout << "hehnext: " << heh_next << std::endl;
			//std::cout << "hehnext2: " << heh_next2 << std::endl;
			//std::cout << "---------------------------------------- " << std::endl;

			vertex_j_next = model.mesh2.to_vertex_handle(heh_next);//<---------------------------------------------vertex_j_next
			//std::cout << vertex_j_next << std::endl;
			vertex_j_prev = model.mesh2.to_vertex_handle(heh_next2);//<---------------------------------------------vertex_j_prev
			/*std::cout << vertex_j_prev << std::endl;
			std::cout << "---------------------------------------- " << std::endl;*/

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
	//std::cout << "step3" <<  std::endl;
	model.mesh2.add_property(v_2d);
	std::cout << "v_2d correct" << std::endl;
	//1.挑一個點繞boundary的邊  2.算距離
	for (MyMesh::HalfedgeIter e_it = model.mesh2.halfedges_begin(); e_it != model.mesh2.halfedges_end(); ++e_it)
	{
		if (model.mesh2.is_boundary(*e_it))
		{
			//std::cout << *e_it << " *e_it:   "  << std::endl;
			TriMesh::HalfedgeHandle heh, heh_next;
			heh = model.mesh2.halfedge_handle(model.mesh2.to_vertex_handle(*e_it));//1.挑一個點繞boundary的邊
			v_boundary.push_back(model.mesh2.to_vertex_handle(heh));//1.挑一個點繞boundary的邊		
			//std::cout << model.mesh2.point(model.mesh2.to_vertex_handle(heh)) - model.mesh2.point(model.mesh2.from_vertex_handle(heh)) << std::endl;
			dis.push_back(distance(model.mesh2.point(model.mesh2.to_vertex_handle(heh)) - model.mesh2.point(model.mesh2.from_vertex_handle(heh)))); //2.算距離

			while (*e_it != heh)
			{
				heh = model.mesh2.halfedge_handle(model.mesh2.to_vertex_handle(heh));//1.挑一個點繞boundary的邊
				v_boundary.push_back(model.mesh2.to_vertex_handle(heh));//1.挑一個點繞boundary的邊
				//std::cout << model.mesh2.point(model.mesh2.to_vertex_handle(heh)) - model.mesh2.point(model.mesh2.from_vertex_handle(heh)) << std::endl;
				dis.push_back(distance(model.mesh2.point(model.mesh2.to_vertex_handle(heh)) - model.mesh2.point(model.mesh2.from_vertex_handle(heh))));//2.算距離
			}
			break;
		}
	}
	//算周長
	for (int i = 0; i < dis.size(); i++)
	{
		//std::cout << "dis: "<<i <<"="<< dis[i] << std::endl;
		dis_total = dis_total + dis[i];
	}
	//map到貼圖座標

	for (int i = 1; i < v_boundary.size(); i++)
	{
		//std::cout << dis[i] / dis_total * 4 << std::endl;
		dis_tmp = dis_tmp + dis[i] / dis_total * 4;
		model.mesh2.property(v_2d, v_boundary[0]) = OpenMesh::Vec2f(0, 0);//(x,0)
		//std::cout <<"dis_tmp: "<< dis_tmp << std::endl;
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
	for (MyMesh::VertexIter v_it = model.mesh2.vertices_begin(); v_it != model.mesh2.vertices_end(); ++v_it)
	{
		//std::cout << "貼圖座標"<<*v_it<<" *v_it "<< model.mesh2.property(v_2d, *v_it) << std::endl;
	}
	//查看點的順序
	/*for (int i = 0; i < v_boundary.size(); i++)
	{

		std::cout << v_boundary[i] << std::endl;
	}*/

	dis.clear();
	dis_total = 0;
	dis_tmp = 0;
	v_boundary.clear();
	//std::cout << inner_point_num << std::endl;
	if (inner_point_num > 0)
	{
		step4();
	}
	else
	{
		//std::cout << model.mesh_tex.size()-1 << std::endl;
		//std::cout << (model.mesh_tex.size()) - 1 << std::endl;
		//std::cout << (model.mesh_tex).size() - 1 << std::endl;
		//model.mesh_tex.push_back(model.mesh2);
		model.mesh_tex[(model.mesh_tex.size()) - 1] = model.mesh2;
		LoadToShader2();
	}

}
void MeshObject::step4()
{
	model.mesh2.add_property(X);
	std::cout << "X correct" << std::endl;
	model.mesh2.add_property(Y);
	std::cout << "Y correct" << std::endl;
	model.mesh2.add_property(fun_weight);
	std::cout << "fun_weight correct" << std::endl;
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
			//std::cout << "*e_it" << *e_it << std::endl;
			heh = model.mesh2.halfedge_handle(*e_it, 0);
			//std::cout << "heh" << heh << std::endl;
			if (model.mesh2.is_boundary(model.mesh2.to_vertex_handle(heh)))
			{
				OpenMesh::Vec2f v2 = model.mesh2.property(v_2d, model.mesh2.to_vertex_handle(heh));
				//std::cout << "v2" << v2 << ": "<< model.mesh2.property(weight, *e_it) <<std::endl;
				model.mesh2.property(X, model.mesh2.to_vertex_handle(heh)) = v2[0] * model.mesh2.property(weight, *e_it);//point.x*weight
				model.mesh2.property(Y, model.mesh2.to_vertex_handle(heh)) = v2[1] * model.mesh2.property(weight, *e_it);//point.y*weight
				model.mesh2.property(fun_weight, model.mesh2.to_vertex_handle(heh)) = model.mesh2.property(weight, *e_it);
				//std::cout << "x" << model.mesh2.property(X, model.mesh2.to_vertex_handle(heh)) << std::endl;
				//std::cout << "y" << model.mesh2.property(Y, model.mesh2.to_vertex_handle(heh)) << std::endl;
			}
			else if (model.mesh2.is_boundary(model.mesh2.from_vertex_handle(heh)))
			{
				OpenMesh::Vec2f v1 = model.mesh2.property(v_2d, model.mesh2.from_vertex_handle(heh));
				//std::cout << "v2" << v1 << ": " << model.mesh2.property(weight, *e_it) << std::endl;
				model.mesh2.property(X, model.mesh2.from_vertex_handle(heh)) = v1[0] * model.mesh2.property(weight, *e_it);//point.x*weight
				model.mesh2.property(Y, model.mesh2.from_vertex_handle(heh)) = v1[1] * model.mesh2.property(weight, *e_it);//point.y*weight
				model.mesh2.property(fun_weight, model.mesh2.from_vertex_handle(heh)) = model.mesh2.property(weight, *e_it);
				//std::cout << "x" << model.mesh2.property(X, model.mesh2.to_vertex_handle(heh)) << std::endl;
				//std::cout << "y" << model.mesh2.property(Y, model.mesh2.to_vertex_handle(heh)) << std::endl;
			}
			else if (!model.mesh2.is_boundary(model.mesh2.from_vertex_handle(heh)) && !model.mesh2.is_boundary(model.mesh2.to_vertex_handle(heh)))
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
	//讓ji邊同步跟ij邊變一樣
	for (int i = 0; i < vertexnewID.size(); i++)
	{
		//std::cout <<" vertexnewID[i].size() "<< vertexnewID[i].size() << std::endl;
		for (int j = 0; j < vertexnewID[i].size(); j++)
		{
			vertexnewID[j][i] = vertexnewID[i][j];
			//std::cout <<"i= "<<i<<" j= "<<j<< " vertexnewID[i][j]"<< vertexnewID[i][j] <<std::endl;

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
			//std::cout << *v_it << "v_it ===================================================================="  << std::endl;
			//std::cout << "change_innerpoints_ID" << model.mesh2.property(change_innerpoints_ID, *v_it) << std::endl;
			for (int i = 0; i < model.mesh2.property(adjacent_point_num_ID, *v_it).size(); i++)
			{
				//std::cout <<"與 "<< *v_it <<" 相鄰的有 "<< model.mesh2.property(adjacent_point_num_ID, *v_it)[i] << std::endl;
				funx.push_back(model.mesh2.property(X, (model.mesh2.property(adjacent_point_num_ID, *v_it)[i])));
				funy.push_back(model.mesh2.property(Y, (model.mesh2.property(adjacent_point_num_ID, *v_it)[i])));
				funweight.push_back(model.mesh2.property(fun_weight, (model.mesh2.property(adjacent_point_num_ID, *v_it)[i])));
			}

			for (int i = 0; i < funx.size(); i++)
			{
				//std::cout <<"funweight[i]"<< funweight[i] << std::endl;
				//std::cout << "funx[i]" << funx[i] << std::endl;
				//std::cout << "funy[i]" << funy[i] << std::endl;
				funx_total += funx[i];//<-------------------------------------相鄰點x總和
				funy_total += funy[i];//<-------------------------------------相鄰點y總和
				funweight_total += funweight[i];
			}
			funx_total_final.push_back(funx_total);
			funy_total_final.push_back(funy_total);
			funweight_total_final.push_back(funweight_total);
			//std::cout << "funx_total " << funx_total << std::endl;
			//std::cout << "funy_total " << funy_total << std::endl;
			//std::cout << "funweight_total " << funy_total << std::endl;
			funx_total = 0;
			funy_total = 0;
			funweight_total = 0;
			funx.clear();
			funy.clear();
			funweight.clear();
		}
	}
	//解線性方程
	int size = inner_point_num;
	//std::cout << "444444444444444444444444:   " << size << std::endl;
	SparseMatrix<double> inner_points_edge(size, size);
	for (int i = 0; i < sqrt(inner_points_edge.size()); i++)
	{

		for (int j = i + 1; j < sqrt(inner_points_edge.size()); j++)
		{
			//std::cout << i<<j<<" vertexnewID[i][j] "<< vertexnewID[i][j] << std::endl;
			inner_points_edge.insert(i, j) = inner_points_edge.insert(j, i) = -(vertexnewID[i][j]);
			funweight_total_final[i] += vertexnewID[i][j];
		}
		for (int k = i - 1; k >= 0; k--)
		{
			//std::cout << i << k << " vertexnewID[i][k] " << vertexnewID[i][k] << std::endl;
			funweight_total_final[i] += vertexnewID[i][k];
		}
		//std::cout<<funweight_total_final[i] << std::endl;
		inner_points_edge.insert(i, i) = funweight_total_final[i];
	}
	//std::cout << inner_points_edge << std::endl;
	inner_points_edge.makeCompressed();
	VectorXd B(size);
	for (int i = 0; i < B.size(); i++)
	{
		//std::cout << "funx_total_final[i]"<<funx_total_final[i] << std::endl;
		B[i] = funx_total_final[i];
	}
	//std::cout << B << std::endl;
	VectorXd C(size);
	for (int i = 0; i < C.size(); i++)
	{
		//std::cout << "funy_total_final[i]" << funy_total_final[i] << std::endl;
		C[i] = funy_total_final[i];;
	}
	//std::cout << C << std::endl;
	Eigen::SimplicialCholesky<SparseMatrix<double >> linearSolver(inner_points_edge.transpose()*inner_points_edge);
	//SparseQR<SparseMatrix<double>, COLAMDOrdering<int>> linearSolver;
	linearSolver.compute(inner_points_edge);
	VectorXd X = linearSolver.solve(B);
	VectorXd Y = linearSolver.solve(C);
	//std::cout << X << std::endl;
	//std::cout << Y << std::endl;
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
	//std::cout << "66666666666666666666666666" << std::endl;
	//最後點的位置
	for (MyMesh::VertexIter v_it = model.mesh2.vertices_begin(); v_it != model.mesh2.vertices_end(); ++v_it)
	{
		//std::cout << "FINAL============================================FINAL" << std::endl;
		//std::cout<<"第 "<< v_it<<" 個點位置 "<<model.mesh2.property(v_2d, *v_it)<<std::endl ;
	}
	funx_total_final.clear();
	funy_total_final.clear();
	funweight_total_final.clear();
	vertexnewID.clear();
	vertexto.clear();
	inner_point_num = 0;
	funx_total_final.clear();
	funy_total_final.clear();
	model.mesh_tex[(model.mesh_tex).size() - 1] = model.mesh2;
	LoadToShader2();
}

void MeshObject::LoadToShader2()
{
	/*model.mesh2.update_face_normals();
	model.mesh2.update_vertex_normals();
	std::vector<MyMesh::Point> vertices2;

	vertices2.reserve(model.mesh.n_vertices());
	for (MyMesh::VertexIter v_it = model.mesh2.vertices_begin(); v_it != model.mesh2.vertices_end(); ++v_it)
	{
		vertices2.push_back(model.mesh2.point(*v_it));
	}


	std::vector<MyMesh::Normal> normals2;
	normals2.reserve(model.mesh.n_vertices());
	for (MyMesh::VertexIter v_it = model.mesh2.vertices_begin(); v_it != model.mesh2.vertices_end(); ++v_it)
	{
		OpenMesh::ArrayKernel::VertexHandle v2_p=(OpenMesh::ArrayKernel::VertexHandle)(model.mesh.FindVertex(model.mesh2.point(*v_it)));
		normals2.push_back(model.mesh.normal(v2_p));
	}
	std::vector<OpenMesh::Vec2f> texture2;
	texture2.reserve(model.mesh.n_vertices());
	for (MyMesh::VertexIter v_it = model.mesh2.vertices_begin(); v_it != model.mesh2.vertices_end(); ++v_it)
	{
		texture2.push_back(model.mesh2.property(v_2d, *v_it));
	}

	std::vector<unsigned int> indices2;
	indices2.reserve(model.mesh.n_faces() * 3);
	for (MyMesh::FaceIter f_it = model.mesh2.faces_begin(); f_it != model.mesh2.faces_end(); ++f_it)
	{
		for (MyMesh::FaceVertexCCWIter fv_it = model.mesh2.fv_ccwiter(*f_it); fv_it.is_valid(); ++fv_it)
		{
			indices2.push_back(fv_it->idx());
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

	glGenVertexArrays(1, &vao2);
	glBindVertexArray(vao2);

	glGenBuffers(1, &vboVertices2);
	glBindBuffer(GL_ARRAY_BUFFER, vboVertices2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(MyMesh::Point) * vertices2.size(), &vertices2[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glGenBuffers(1, &vboNormal2);
	glBindBuffer(GL_ARRAY_BUFFER, vboNormal2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(MyMesh::Normal) * normals2.size(), &normals2[0], GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);


	glGenBuffers(1, &tex2);
	glBindBuffer(GL_ARRAY_BUFFER, tex2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(OpenMesh::Vec2f) * texture2.size(), &texture2[0], GL_STATIC_DRAW);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(2);


	glGenBuffers(1, &ebo2);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo2);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * indices2.size(), &indices2[0], GL_STATIC_DRAW);

	glGenBuffers(1, &ebo3);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo3);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * indices3.size(), &indices3[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);*/
	std::vector<MyMesh::Point> vertices2;
	vertices2.reserve(model.mesh2.n_vertices());
	for (MyMesh::VertexIter v_it = model.mesh2.vertices_begin(); v_it != model.mesh2.vertices_end(); ++v_it)
	{
		vertices2.push_back(model.mesh2.point(*v_it));
	}


	std::vector<MyMesh::Normal> normals2;
	normals2.reserve(model.mesh2.n_vertices());
	for (MyMesh::VertexIter v_it = model.mesh2.vertices_begin(); v_it != model.mesh2.vertices_end(); ++v_it)
	{
		OpenMesh::ArrayKernel::VertexHandle v2_p = (OpenMesh::ArrayKernel::VertexHandle)(model.mesh.FindVertex(model.mesh2.point(*v_it)));
		normals2.push_back(model.mesh.normal(v2_p));
	}
	std::vector<OpenMesh::Vec2f> texture2;
	texture2.reserve(model.mesh2.n_vertices());
	for (MyMesh::VertexIter v_it = model.mesh2.vertices_begin(); v_it != model.mesh2.vertices_end(); ++v_it)
	{
		texture2.push_back(model.mesh2.property(v_2d, *v_it));
	}

	std::vector<unsigned int> indices2;
	indices2.reserve(model.mesh2.n_faces() * 3);
	for (MyMesh::FaceIter f_it = model.mesh2.faces_begin(); f_it != model.mesh2.faces_end(); ++f_it)
	{
		for (MyMesh::FaceVertexCCWIter fv_it = model.mesh2.fv_ccwiter(*f_it); fv_it.is_valid(); ++fv_it)
		{
			indices2.push_back(fv_it->idx());
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
	mesh_vao.push_back(0);
	mesh_vboVertices.push_back(0);
	mesh_vboNormal.push_back(0);
	mesh_texure.push_back(0);
	mesh_ebo.push_back(0);
	mesh_ebo_line.push_back(0);
	glGenVertexArrays(1, &mesh_vao[model.mesh_tex.size() - 1]);
	glBindVertexArray(mesh_vao[model.mesh_tex.size() - 1]);

	glGenBuffers(1, &mesh_vboVertices[model.mesh_tex.size() - 1]);
	glBindBuffer(GL_ARRAY_BUFFER, mesh_vboVertices[model.mesh_tex.size() - 1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(MyMesh::Point) * vertices2.size(), &vertices2[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glGenBuffers(1, &mesh_vboNormal[model.mesh_tex.size() - 1]);
	glBindBuffer(GL_ARRAY_BUFFER, mesh_vboNormal[model.mesh_tex.size() - 1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(MyMesh::Normal) * normals2.size(), &normals2[0], GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);


	glGenBuffers(1, &mesh_texure[model.mesh_tex.size() - 1]);
	glBindBuffer(GL_ARRAY_BUFFER, mesh_texure[model.mesh_tex.size() - 1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(OpenMesh::Vec2f) * texture2.size(), &texture2[0], GL_STATIC_DRAW);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(2);


	glGenBuffers(1, &mesh_ebo[model.mesh_tex.size() - 1]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh_ebo[model.mesh_tex.size() - 1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * indices2.size(), &indices2[0], GL_STATIC_DRAW);

	glGenBuffers(1, &mesh_ebo_line[model.mesh_tex.size() - 1]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh_ebo_line[model.mesh_tex.size() - 1]);
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
	glBindVertexArray(mesh_vao[model.mesh_tex.size() - 1]);
	glBindBuffer(GL_ARRAY_BUFFER, mesh_vboVertices[model.mesh_tex.size() - 1]);
	glBindBuffer(GL_ARRAY_BUFFER, mesh_vboNormal[model.mesh_tex.size() - 1]);
	glBindBuffer(GL_ARRAY_BUFFER, mesh_texure[model.mesh_tex.size() - 1]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh_ebo_line[model.mesh_tex.size() - 1]);
	glDrawElements(GL_LINES, model.mesh2.n_edges() * 2, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}
void MeshObject::Render_TexCoord2()
{
	glBindVertexArray(mesh_vao[model.mesh_tex.size() - 1]);
	glBindBuffer(GL_ARRAY_BUFFER, mesh_vboVertices[model.mesh_tex.size() - 1]);
	glBindBuffer(GL_ARRAY_BUFFER, mesh_vboNormal[model.mesh_tex.size() - 1]);
	glBindBuffer(GL_ARRAY_BUFFER, mesh_texure[model.mesh_tex.size() - 1]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh_ebo[model.mesh_tex.size() - 1]);
	glDrawElements(GL_TRIANGLES, model.mesh2.n_faces() * 3, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}
MyMesh MeshObject::record_mesh(int mesh_num)
{
	//model.mesh2 = mesh_tex[mesh_num];
	return model.mesh_tex[mesh_num];
}
void MeshObject::create_mesh()
{
	model.mesh2.ClearMesh();
	selectedFace.clear();
	selectedpoint.clear();
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
	std::cout << "pp correct" << std::endl;
	model.mesh.add_property(vertexId);
	std::cout << "vertexId correct" << std::endl;

	//model.mesh2 = model.mesh_blank;	
	//std::cout << model.mesh_tex .size()<<std::endl;

}
void MeshObject::increase_face()
{
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
	/*for (MyMesh::VertexIter v_it = model.mesh2.vertices_begin(); v_it != model.mesh2.vertices_end(); ++v_it)
	{
		model.mesh2.delete_vertex(*v_it);
	}*/
	model.mesh2.ClearMesh();
	//std::cout << model.mesh2.n_vertices() << std::endl;
	//std::cout << model.mesh2.n_edges() << std::endl;
	//std::cout << model.mesh2.n_faces() << std::endl;
	selectedFace.clear();
	selectedpoint.clear();
	model.mesh.add_property(pp);
	std::cout << "pp correct" << std::endl;
	for (int i = 0; i < face_id.size(); i++)
	{
		AddSelectedFace(face_id[i]);

	}
	face_id.clear();
	AddSelectedFacefinished();

}
void MeshObject::decrease_face()
{
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
	std::cout << "pp correct" << std::endl;
	for (int i = 0; i < face_id.size(); i++)
	{
		AddSelectedFace(face_id[i]);

	}
	face_id.clear();
	AddSelectedFacefinished();
}
float MeshObject::cotan(OpenMesh::Vec3f a, OpenMesh::Vec3f b) {
	return (a | b) / (a%b).norm();
}
float MeshObject::distance(OpenMesh::Vec3f a) {

	return  a.norm();
}


void MeshObject::DeleteSelectedFace(unsigned int faceID)
{
	selectedFace.erase(std::remove(selectedFace.begin(), selectedFace.end(), faceID), selectedFace.end());
	//selectedFace.clear();
	//selectedpoint.clear();
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