#pragma once
#ifndef _MESH_H_
#define _MESH_H_

#include <vector>
#include <iostream>


#include "math_header.h"
#include "io_mesh.h"
#include "opengl_headers.h"

//#include "global_headers.h
//#include "math_headers.h"
//#include "io_mesh.h"
//#include "anttweakbar_wrapper.h"
//#include "simulation.h"
//#include "camera.h"
//#include "primitive.h"

//forward declarations
class Camera;
class AntTweakBarWrapper;
class Simulation;

typedef enum
{
	MESH_TYPE_TET,

	MESH_TYPE_TOTAL_NUM
} MeshType;

class Mesh
{
	//friend class AntTweakBarWrapper;
	friend class Simulation;
	friend class Camera;

public:
	Mesh() : mesh_type() {}
	Mesh(MeshType mesh_type) : mesh_type(mesh_type) {}
	virtual ~Mesh() { cleanup(); }

	void    reset();
	virtual bool init() { std::cout << "Warning: reach base class virtual init function." << std::endl; return false; }
	virtual void cleanup();
	virtual void initialset();
	virtual void draw(const VBO& vbos, bool wire_frame = false, int show_texture = 0);

	// member accessor
	//virtual inline uint GetNumberOfVertices() { return m_vert_num; }
	//virtual inline uint GetDimension() { return m_system_dim; }
	inline MeshType GetMeshType() { return mesh_type; }
	void set_scale(double num) { m_tet_scaling = num; }

public:
	//get num
	uint GetVertexNum() { return m_vert_num;  }
	uint GetTetNum() { return m_T.size(); }
	//Eigen::Vector3d GetVertex(const int i) { return m_V[i]; }
	//int GetTetra(const int i, const int j) { return m_T[i][j]; }
	//void SetVertex(const int i, Eigen::Vector3d _vert) { m_V[i] = _vert; }

protected:
	MeshType mesh_type;

	uint m_vert_num;   // m
	uint m_dim;        // 2 or 3
	uint m_system_dim; // 3m
	//uint 
	Eigen::MatrixXd  m_V0;	// rest pose
	Eigen::MatrixXd  m_V;	// current pose
	Eigen::MatrixXd  m_N;	// current normal
	Eigen::MatrixXi  m_F;  // tri index
	Eigen::MatrixXi  m_T;  // tet index

						// for visualization
	std::vector<glm::vec3> m_positions;
	std::vector<glm::vec3> m_normals;
	std::vector<glm::vec3> m_colors;
	std::vector<glm::vec2> m_texcoords;
	std::vector<uint> m_triangle_list;

	ScalarType m_total_mass;
	ScalarType m_tet_scaling;

	char mesh_file_path[256];


protected:
	virtual void generateParticleList() { std::cout << "Warning: reach base class virtual function." << std::endl; } // initialize every particle pos / vel / mass / color.
	virtual void generateTriangleList() { std::cout << "Warning: reach base class virtual function." << std::endl; } // generate triangle list from vetices

	void computeNormal();

};

class TetMesh : public Mesh
{
//	friend class AntTweakBarWrapper;
//	friend class Simulation;

public:
	TetMesh() {};//;//: Mesh(MESH_TYPE_TET), m_loaded_mesh(NULL) {}
	//void Set_tetfile(std::string file) { m_tet_file_path = file.c_str(); }
	virtual ~TetMesh() { if (m_loaded_mesh) { delete m_loaded_mesh; } }
	
	virtual bool Init();
//	char m_tet_file_path[256];
	bool LoadTetMesh();
	
protected:
	// tet mesh if loaded from mesh file
	MeshLoader *m_loaded_mesh;
	
protected:
	virtual void generateParticleList();
	virtual void generateTriangleList();
	
};

#endif