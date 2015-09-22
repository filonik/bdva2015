#include "scene-3ds.h"

#include <vector>
#include <string>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <cstdlib>

/////////////////////////////////////////////////////////////////////////////

#define chunk_main                     0x4d4d
#define   chunk_mesh                   0x3d3d
#define     chunk_material             0xafff
#define       chunk_matname            0xa000
#define       chunk_matambient         0xa010
#define       chunk_matdiffuse         0xa020
#define       chunk_matspecular        0xa030
#define       chunk_percent            0x0030
#define       chunk_matfname           0xa300
#define       chunk_mattexture         0xa200
#define       chunk_mattexture_wm      0xa33e
#define       chunk_mattexture2        0xa33a
#define       chunk_mattexture2_wm     0xa340
#define       chunk_matopacity         0xa210
#define       chunk_matopacity_wm      0xa342
#define       chunk_matbump            0xa230
#define       chunk_matbump_wm         0xa344
#define       chunk_matspecularr       0xa204
#define       chunk_matspecularr_wm    0xa348
#define       chunk_matshiniess        0xa33c
#define       chunk_matshiniess_wm     0xa346
#define       chunk_matillumination    0xa33d
#define       chunk_matillumination_wm 0xa34a
#define       chunk_matreflection      0xa220
#define       chunk_matreflection_wm   0xa34c
#define       chunk_matshading         0xa100
#define       chunk_matwire            0xa085
#define       chunk_matwiresize        0xa087
#define     chunk_object               0x4000
#define       chunk_trimesh            0x4100
#define         chunk_vertexlist       0x4110
#define         chunk_maplist          0x4140
#define         chunk_textureinfo      0x4170
#define         chunk_vertflags        0x4111
#define         chunk_facelist         0x4120
#define         chunk_matrix           0x4160
#define         chunk_meshcolor        0x4165
#define         chunk_smoothlist       0x4150
#define         chunk_facematerial     0x4130
#define       chunk_light              0x4600
#define         chunk_spotlight        0x4610
#define       chunk_camera             0x4700
#define         chunk_camranges        0x4720
#define   chunk_keyframer              0xb000
#define     chunk_kfhdr                0xb00a
#define     chunk_frames               0xb008
#define     chunk_nodeobject           0xb002
#define       chunk_nodehdr            0xb010
#define       chunk_nodeid             0xb030
#define       chunk_pivot              0xb013
#define       chunk_postrack           0xb020
#define       chunk_objhide            0xb029
#define       chunk_objrot             0xb021
#define       chunk_objscale           0xb022
#define     chunk_nodelight            0xb005
#define     chunk_nodecamera           0xb003
#define       chunk_fovtrack           0xb023
#define       chunk_rolltrack          0xb024
#define     chunk_nodecameratarget     0xb004

/////////////////////////////////////////////////////////////////////////////



std::ifstream file;

int fileGetInt();
unsigned char fileGetUChar();
short fileGetWord();

void readMeshChunk();
void readMaterialChunk();
void readObjectChunk();
std::string readTextureChunk();
void readTrimeshChunk();
void readCameraChunk();

float m11;// = fileGetFloat();
float m13;// = fileGetFloat();
float m12;// = fileGetFloat();
float m14;// = 0.0f;
float m31;// = fileGetFloat();
float m33;// = fileGetFloat();
float m32;// = fileGetFloat();
float m34;// = 0.0f;
float m21;// = fileGetFloat();
float m23;// = fileGetFloat();
float m22;// = fileGetFloat();
float m24;// = 0.0f;
float m41;// = fileGetFloat();
float m43;// = fileGetFloat();
float m42;// = fileGetFloat();
float m44;// = 1.0f;

short Scene3DS::fileGetWord()
{
   short tmp;
   file.read((char*)&tmp, 2);
   return tmp;
}
std::string Scene3DS::fileGetName()
{
	std::vector<unsigned char> str;
	int i2, i;
	i2 = fileGetInt()-6;
	for (i=0; i<i2; i++) str.push_back(fileGetUChar());
	return (char*)&str[0];
}
std::string Scene3DS::fileGetObjectName()
{
	std::vector<unsigned char> str;
	unsigned char tmp;
	do {
		tmp = fileGetUChar();
		str.push_back(tmp);
	} while(tmp);
	return (char*)&str[0];
}
float Scene3DS::fileGetFloat()
{
	float tmp;
	file.read((char*)&tmp, 4);
	return tmp;
}
int Scene3DS::fileGetInt()
{
	int tmp;
	file.read((char*)&tmp, 4);
	return tmp;
}
unsigned char Scene3DS::fileGetUChar()
{
	unsigned char tmp;
	file.read((char*)&tmp, 1);
	return tmp;
}


void Scene3DS::load3ds(const std::string& filename)
{
   file.open(filename.c_str(), std::ios::in | std::ios::binary);
   
   if (!file) {
      std::cerr << "ERROR LOAD 3DS: can't open \"" << filename << "\"" << std::endl;
      return;
   }
   
   // Check whether main chunk of 3DS file is OK.
   if (fileGetWord() != chunk_main)
   {
      std::cerr << "ERROR LOAD 3DS: wrong .3DS file" << std::endl;
      return;
   }
   
   int iFileSize = fileGetInt();
   
   std::cout << "++ main" << std::endl;
   
   bool finished = false;
   while (!finished)
   {
      unsigned short id_chunk = fileGetWord();
      
      switch (id_chunk)
      {
         case chunk_mesh:
            std::cout << " ++ mesh" << std::endl;
            readMeshChunk();
            break;
         case chunk_keyframer:
            std::cout << " ++ keyframer" << std::endl;
            // break;
         default:
            // read unknown or yet not implemented chunk
            int size_chunk = fileGetInt();
            file.seekg((int)file.tellg()+size_chunk-6);
            break;
      }
      if ((int)file.tellg() >= iFileSize) finished = true;
   }
   
   file.close();
}


void Scene3DS::readMeshChunk()
{
	int file_pos = (int)file.tellg()-2;
	int chunk_size = fileGetInt();
   
	bool finished = false;
	while(!finished) {
		unsigned short id_chunk = fileGetWord();
		//printf("!!!!!! %x\n", id_chunk);
      
		switch(id_chunk) {
			case chunk_object:
            std::cout << "  ++ object ";
				readObjectChunk();
				break;
			case chunk_material:
            std::cout << "  ++ material" << std::endl;
				readMaterialChunk();
            break;
			default:
				int size_chunk = fileGetInt();
				file.seekg((int)file.tellg()+size_chunk-6);
				break;
		}
		if (((int)file.tellg()-file_pos) >= chunk_size) finished = true;
	}
}


void Scene3DS::readMaterialChunk()
{
	int file_pos = (int)file.tellg()-2;
	int chunk_size = fileGetInt();
   
	// KDMaterial3DS material;
   
	bool finished = false;
	while(!finished) {
		unsigned short id_chunk = fileGetWord();
      
		switch(id_chunk) {
			case chunk_matname:
            std::cout << "   ++ name: ";
				// material.name = fileGetName();
            std::cout << fileGetName() << std::endl;
				break;
			case chunk_mattexture:
				//material.texture1.fname = readTextureChunk();
            std::cout << "    ++ texure1 filename:  " << readTextureChunk() << std::endl;
				break;
			case chunk_mattexture2:
				//material.texture2.fname = readTextureChunk();
            std::cout << "    ++ texure2 filename: " << readTextureChunk() << std::endl;
				break;
			default:
				int size_chunk = fileGetInt();
				file.seekg((int)file.tellg()+size_chunk-6);
				break;
		}
		if (((int)file.tellg()-file_pos) >= chunk_size) finished = true;
	}
	//materials.push_back(material);
}


std::string Scene3DS::readTextureChunk()
{
	int file_pos = (int)file.tellg()-2;
	int chunk_size = fileGetInt();
   
   std::string str;
   
	bool finished = false;
	while(!finished) {
		unsigned short id_chunk = fileGetWord();
      
		switch(id_chunk) {
			case chunk_matfname:
				str = fileGetName();
				break;
			default:
				int size_chunk = fileGetInt();
				file.seekg((int)file.tellg()+size_chunk-6);
				break;
		}
		if (((int)file.tellg()-file_pos) >= chunk_size) finished = true;
	}
	return str;
}



void Scene3DS::readObjectChunk()
{
	int file_pos = (int)file.tellg()-2;
	int chunk_size = fileGetInt();
   
   std::string str = fileGetObjectName();
   
	// KDObject object;
	// KDCamera camera;
   
   Object *object = new Object;
   
	bool finished = false;
	while(!finished)
   {
		unsigned short id_chunk = fileGetWord();
      
		switch(id_chunk)
      {
			case chunk_trimesh:
				// object.name = str;
				// objects.push_back(object);
            // m_akObjects.addObject(object);
            addObject(object);
            std::cout << "trimesh: " << str << std::endl;
				readTrimeshChunk(object);
            object->init();
				break;
			case chunk_camera :
				// camera.name = (char*)&str[0];
				// cameras.push_back(camera);
            std::cout << "camera: " << str << std::endl;
				readCameraChunk();
				break;
			case chunk_light:
			default:
				int size_chunk = fileGetInt();
				file.seekg((int)file.tellg()+size_chunk-6);
				break;
		}
		if (((int)file.tellg()-file_pos) >= chunk_size) finished = true;
	}
}


void Scene3DS::readTrimeshChunk(Object *object)
{
	int file_pos = (int)file.tellg()-2;
	int chunk_size = fileGetInt();
   
	int number_of_vertices, number_of_faces, number_of_uv, i, j, k;
   std::string str;
   
	bool finished = false;
	while(!finished) {
		unsigned short id_chunk = fileGetWord();
      
		switch(id_chunk)
      {
			case chunk_vertexlist:
				fileGetInt();
				number_of_vertices = fileGetWord();
            std::cout << "   ++ vertices: " << number_of_vertices << std::endl;
				// objects.back().number_of_vertices = number_of_vertices;
				for (i=0; i<number_of_vertices; i++)
				{
               float v1 = fileGetFloat()/20.0f;
               float v3 = fileGetFloat()/20.0f;
               float v2 = fileGetFloat()/20.0f;
               glm::vec3 vec = glm::vec3(v1, v2, v3);
               object->addVertex(vec);
					//KDObject::vertex v1;
					//v1.position.x = fileGetFloat();
					//v1.position.z = fileGetFloat();
					//v1.position.y = fileGetFloat();
					//objects.back().vertices.push_back(v1);
               std::cout << "\t" << std::setiosflags(std::ios::fixed) << std::setprecision(4) << v1 << "\t" << v2 << "\t " << v3 << std::endl;
				}
				break;
			case chunk_facelist:
				fileGetInt();
				number_of_faces = fileGetWord();
				//objects.back().number_of_faces = number_of_faces;
            std::cout << "   ++ faces: " << number_of_faces << std::endl;
				for (i=0; i<number_of_faces; i++)
				{
               GLuint f1 = fileGetWord();
               GLuint f3 = fileGetWord();
               GLuint f2 = fileGetWord();
               glm::uvec3 face = glm::uvec3(f1, f2, f3);
               object->addFace(face);
					//KDObject::face fc;
					//fc.f1 = fileGetWord();
					//fc.f2 = fileGetWord();
					//fc.f3 = fileGetWord();
					//objects.back().faces.push_back(fc);
					fileGetWord(); // additional flags
               //// std::cout << "\t" << f1 << "\t" << f2 << "\t " << f3 << std::endl;
				}
				break;
			case chunk_maplist:
				fileGetInt();
				number_of_uv = fileGetWord();
            std::cout << "   ++ mapping uv: " << number_of_uv << std::endl;
				for (i=0; i<number_of_uv; i++)
				{
					// float uu = fileGetFloat();
					// float vv = fileGetFloat();
					
					// objects.back().vertices[i].uv.x = uu;
					// objects.back().vertices[i].uv.y = vv;
               //// std::cout << "\t" << std::setiosflags(std::ios::fixed) << std::setprecision(4) << uu << "\t" << vv << std::endl;
				}
				break;
			case chunk_matrix:
				fileGetInt();
            std::cout << "   ++ object matrix " << std::endl;
				// rotation
            m11 = fileGetFloat();
            m13 = fileGetFloat();
            m12 = fileGetFloat();
            m14 = 0.0f;
            m31 = fileGetFloat();
            m33 = fileGetFloat();
            m32 = fileGetFloat();
            m34 = 0.0f;
            m21 = fileGetFloat();
            m23 = fileGetFloat();
            m22 = fileGetFloat();
            m24 = 0.0f;
            m41 = fileGetFloat();
            m43 = fileGetFloat();
            m42 = fileGetFloat();
            m44 = 1.0f;
            /*
             objects.back().object_matrix._11 = fileGetFloat();
             objects.back().object_matrix._13 = fileGetFloat();
             objects.back().object_matrix._12 = fileGetFloat();
             objects.back().object_matrix._14 = 0.0f;
             objects.back().object_matrix._31 = fileGetFloat();
             objects.back().object_matrix._33 = fileGetFloat();
             objects.back().object_matrix._32 = fileGetFloat();
             objects.back().object_matrix._34 = 0.0f;
             objects.back().object_matrix._21 = fileGetFloat();
             objects.back().object_matrix._23 = fileGetFloat();
             objects.back().object_matrix._22 = fileGetFloat();
             objects.back().object_matrix._24 = 0.0f;
             // translation
             objects.back().object_matrix._41 = fileGetFloat();
             objects.back().object_matrix._43 = fileGetFloat();
             objects.back().object_matrix._42 = fileGetFloat();
             objects.back().object_matrix._44 = 1.0f;
             */
            std::cout << "      " << m11 << "  " << m12 << "  " << m13 << "  " << m14 << std::endl;
            std::cout << "      " << m21 << "  " << m22 << "  " << m23 << "  " << m24 << std::endl;
            std::cout << "      " << m31 << "  " << m32 << "  " << m33 << "  " << m34 << std::endl;
            std::cout << "      " << m41 << "  " << m42 << "  " << m43 << "  " << m44 << std::endl;
				break;
			case chunk_facematerial:
				fileGetInt();
				str = fileGetObjectName();
            std::cout << "   ++ face material applied: " << str << std::endl;
				j = 0;
				// while (materials[j].name != str) j++;
				number_of_faces = fileGetWord();
				std::cout << "    ++ on faces: " << number_of_faces << std::endl;
				for (i=0; i<number_of_faces; i++) {
					// read face number assigned to this material
					k = fileGetWord();
					// objects.back().faces[k].material = j;
				}
				break;
			default:
				int size_chunk = fileGetInt();
				file.seekg((int)file.tellg()+size_chunk-6);
				break;
		}
		if (((int)file.tellg()-file_pos) >= chunk_size) finished = true;
	}
}


void Scene3DS::readCameraChunk()
{
	int file_pos = (int)file.tellg()-2;
	int chunk_size = fileGetInt();
   
   /*
    cameras.back().position.x = fileGetFloat();
    cameras.back().position.z = fileGetFloat();
    cameras.back().position.y = fileGetFloat();
    cameras.back().target.x = fileGetFloat();
    cameras.back().target.z = fileGetFloat();
    cameras.back().target.y = fileGetFloat();
    cameras.back().roll = fileGetFloat();
    cameras.back().fov = fileGetFloat();
    */
   float p1 = fileGetFloat();
   float p3 = fileGetFloat();
   float p2 = fileGetFloat();
   float t1 = fileGetFloat();
   float t3 = fileGetFloat();
   float t2 = fileGetFloat();
   float roll = fileGetFloat();
   float fov = fileGetFloat();
   
   std::cout << "   ++ position: " << std::setiosflags(std::ios::fixed) << std::setprecision(4) << p1 << " " << p2 << " " << p3 << std::endl;
   std::cout << "   ++ target: " << std::setiosflags(std::ios::fixed) << std::setprecision(4) << t1 << " " << t2 << " " << t3 << std::endl;
   
   std::cout << "   ++ fov: " << fov << std::endl;
   std::cout << "   ++ roll: " << roll << std::endl;
   
	bool finished = false;
	while(!finished) {
		unsigned short id_chunk = fileGetWord();
      
		switch(id_chunk) {
			case chunk_camranges :
				fileGetInt();
				//cameras.back().clip_near = fileGetFloat();
				//cameras.back().clip_far = fileGetFloat();
            p1 = fileGetFloat();
            p2 = fileGetFloat();
            std::cout << "   ++ near and far clips: " << p1 << " " << p2 << std::endl;
				break;
			default:
				int size_chunk = fileGetInt();
				file.seekg((int)file.tellg()+size_chunk-6);
				break;
		}
		if (((int)file.tellg()-file_pos) >= chunk_size) finished = true;
	}
}
