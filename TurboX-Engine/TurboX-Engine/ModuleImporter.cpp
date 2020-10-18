#include "Globals.h"
#include "Application.h"
#include "ModuleImporter.h"


ModuleImporter::ModuleImporter(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	name = "Importer";
}

// Destructor
ModuleImporter::~ModuleImporter()
{}

// Called before render is available
bool ModuleImporter::Init(JSON_Object* obj)
{
	LoadFBX("Assets/BakerHouse.fbx");

	bool ret = true;
	json_object_clear(obj);
	return ret;
}

// Called before quitting
bool ModuleImporter::CleanUp()
{

	return true;
}

void ModuleImporter::LoadFBX(char* file_path)
{
	const aiScene* scene = aiImportFile(file_path, aiProcessPreset_TargetRealtime_MaxQuality);
	
	if (scene != nullptr && scene->HasMeshes())
	{
		// Use scene->mNumMeshes to iterate on scene->mMeshes array
		for (int i = 0; i < scene->mNumMeshes; i++)
		{
			aiMesh* meshIterator = scene->mMeshes[i];
			
			// copy vertices
			ourMesh.num_vertex = meshIterator->mNumVertices;
			ourMesh.vertex = new float[ourMesh.num_vertex * 3];
			memcpy(ourMesh.vertex, meshIterator->mVertices, sizeof(float) * ourMesh.num_vertex * 3);
			MY_LOG("New mesh with %d vertices", ourMesh.num_vertex);
			
			// copy faces
			if (meshIterator->HasFaces())
			{
				ourMesh.num_index = meshIterator->mNumFaces * 3;
				ourMesh.index = new uint[ourMesh.num_index]; // assume each face is a triangle
				for (uint i = 0; i < meshIterator->mNumFaces; ++i)
				{
					if (meshIterator->mFaces[i].mNumIndices != 3)
					{
						MY_LOG("WARNING, geometry face with != 3 indices!");
					}
					else 
					{ 
						memcpy(&ourMesh.index[i * 3], meshIterator->mFaces[i].mIndices, 3 * sizeof(uint));
					}
				}
			}

		}

		aiReleaseImport(scene);
	}
	else
		MY_LOG("Error loading scene % s", file_path);

}