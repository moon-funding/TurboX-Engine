#include "GameObject.h"
#include "Application.h"
#include "ModuleScene.h"

GameObject::GameObject()
{	
	active = true;
	ChangeName("Custom Mesh");
	is_selected = false;
	to_delete = false;

	mesh = nullptr;
	material = nullptr;
	transform = nullptr;
	parent = nullptr;
}

GameObject::~GameObject()
{
	
}

Component* GameObject::CreateComponent(Component::Type type)
{
	Component* new_component = nullptr;

	switch (type)
	{
	case Component::Type::None:		
		break;
	case Component::Type::Transform:
		new_component = new C_Transform(Component::Type::Transform, this);
		transform = (C_Transform*)new_component;
		break;
	case Component::Type::Mesh:
		new_component = new C_Mesh(Component::Type::Mesh, this);
		mesh = (C_Mesh*)new_component;
		break;
	case Component::Type::Material:
		new_component = new C_Material(Component::Type::Material, this);
		material = (C_Material*)new_component;
		break;
	default:
		break;
	}

	if (new_component)
		components.push_back(new_component);

	return new_component;
}

void GameObject::DestroyComponent()
{
	Component::Type type;

	for (int i = 0; i < components.size(); i++)
	{
		if (type == components[i]->GetComponentType())
		{
			components[i]->Disable();
		}
	}
}

Component* GameObject::GetComponent(Component::Type type)
{

	for (int i = 0; i < components.size(); i++)
	{
		if (type == components[i]->GetComponentType())
		{
			return components[i];
		}
	}

	return nullptr;
}

void GameObject::Draw()
{
	if (mesh != nullptr)
	{
		//glPushMatrix();
		//glMultMatrixf((float*)transform->globalMatrix.Transposed().v);
		mesh->Draw();
		//glPopMatrix();
	}
	
	for (size_t i = 0; i < childs.size(); i++)
	{
		if (childs[i]->active)
			childs[i]->Draw();
	}
}

void GameObject::ChangeName(std::string _name)
{
	name = _name;
}

bool GameObject::Get_IsSelected()
{
	return is_selected;
}

void GameObject::Select()
{
	is_selected = true;
}

void GameObject::Unselect()
{
	is_selected = false;
}

void GameObject::AddChildren(GameObject* child)
{
	for (int i = 0; i < childs.size(); i++) {
		if (childs[i] == child) {
			return;
		}
	}
	this->childs.push_back(child);
	child->SetParent(this);
}

void GameObject::SetParent(GameObject* _parent)
{

	if (parent != nullptr) {
		if (parent = _parent) {
			return;
		}
		for (std::vector<GameObject*>::iterator iterator = parent->childs.begin(); iterator != parent->childs.end(); iterator++) {
			if (this == (*iterator)) {
				parent->childs.erase(iterator);
				break;
			}
		}
	}
	parent = _parent;
	parent->AddChildren(this);
}

