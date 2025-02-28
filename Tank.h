#pragma once
#include "Pawn.h"
#include "MeshComponent.h"
#include "CollisionComponent.h"
#include "PlayerController.h"

class Tank : public Pawn
{
	map<string, map<int, int>> joystickButtonByBrand;
	MeshComponent* mesh;
	CollisionComponent* collision;
public:
	Tank(Level* _level, const string& _name = "Tank");
	Tank(const Tank& _other);

protected:
	virtual void SetupInputController(Input::InputManager& _inputManager) override;
	virtual void CollisionEnter(const CollisionData& _data) override;
	virtual void CollisionUpdate(const CollisionData& _data) override;
	virtual void CollisionExit(const CollisionData& _data) override;

private:
	void JoystickActions(const int _joystickId, Input::InputManager& _inputManager);

};

