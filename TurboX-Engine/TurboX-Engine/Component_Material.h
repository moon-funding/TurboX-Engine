#ifndef __COMPONENT_MATERIAL_H_
#define __COMPONENT_MATERIAL_H_

#include "Component.h"
#include "ResourceTexture.h"
#include "glew\glew.h"
#include "DevIL/include/ilut.h"
#include <string>

#pragma comment (lib, "Libraries/glew/glew32.lib") /* link OpenGL Utility lib */
#pragma comment (lib, "Libraries/DevIL/lib/DevIL.lib")
#pragma comment (lib, "Libraries/DevIL/lib/ILUT.lib")
#pragma comment (lib, "Libraries/DevIL/lib/ILU.lib")

using namespace std;

class C_Material : public Component {
public:
	C_Material(Component::Type type, GameObject* owner);
	~C_Material();

	float3 colors = { 0,0,0 };

	void SetResource(uint resource)override;
	const uint GetTexID() const;
	const bool HasTexture() const;

	bool Save(Config* data) override;
	bool Load(Config* data) override;
	
	Component::Type GetComponentType() override;
	ResourceTexture* GetResourceTexture() const { return resourceTexture; }

private:
	ResourceTexture* resourceTexture = nullptr;

};
#endif // !__COMPONENT_MATERIAL_H_
