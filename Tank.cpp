#include "Tank.h"
#include "Level.h"
#include "InputManager.h"
#define CONTROLLER_DEAD_ZONE 0.2f
using namespace Input;

void Tank::SetTankComponents(MeshComponent* _body, MeshComponent* _tracks, MeshComponent* _turrel)
{
}

Tank::Tank(Level* _level, const string& _name) : Pawn(_level, _name)
{
	const Vector2f _tankSize = Vector2f(100.0f, 150.0f);
	mesh = CreateComponent<MeshComponent>(RectangleShapeData(_tankSize, "Tank/Tank_2"));
	//mesh->GetShape()->SetOrigin(GetOrigin());
	movement = CreateComponent<TankMovement>();
	movement->SetMoveSpeed(10.0f);
}

Tank::Tank(const Tank& _other) : Pawn(_other)
{
	mesh = GetComponent<MeshComponent>();
	collision = GetComponent<CollisionComponent>();
	movement = GetComponent<TankMovement>();
}

void Tank::SetupInputController(Input::InputManager& _inputManager)
{
	ActionMap* _moveInputs = _inputManager.CreateActionMap("PlayerMovement");

	_moveInputs->AddActions(
		{
			new Action("Connected", ActionData(JoystickConnected), [&](const float _joystick)
			{
				LOG(Warning, "Connection");

				const int _joystickId = CAST(int, _joystick);
				if (_joystickId != 0) return;
				JoystickActions(_joystickId, _inputManager);
			})
		});
	if (Joystick::isConnected(0))
	{
		JoystickActions(0, _inputManager);
	}
	_moveInputs->Enable();
}

void Tank::CollisionEnter(const CollisionData& _data)
{

}

void Tank::CollisionUpdate(const CollisionData& _data)
{

}

void Tank::CollisionExit(const CollisionData& _data)
{

}

void Tank::JoystickActions(const int _joystickId, Input::InputManager& _inputManager)
{
	ActionMap* _controllerAction = _inputManager.CreateActionMap("JoystickMovement");
	const int _brandId = Joystick::getIdentification(_joystickId).productId;
	LOG(Display, "Controller id ->" + to_string(_brandId));
	_controllerAction->AddActions(
		{
			new Action("ControllerY_" + to_string(_joystickId), ActionData(JoystickMoved, _joystickId, Input::InputManager::GetJoystickAxeByBrand(_brandId, "LeftJoystickY")), [&](const float _normal)
			{
				if (!(_normal > CONTROLLER_DEAD_ZONE || _normal < -CONTROLLER_DEAD_ZONE))
				{
					movement->ResetY();
					return;
				}
				movement->ProcessYController(_normal);

			}),
			new Action("ControllerX_" + to_string(_joystickId), ActionData(JoystickMoved, _joystickId, Input::InputManager::GetJoystickAxeByBrand(_brandId, "LeftJoystickX")), [&](const float _normal)
			{
				movement->ProcessXController(_normal);

			}),
			new Action("ButtonA_" + to_string(_joystickId), ActionData(JoystickButtonPressed, _joystickId, Input::InputManager::GetJoystickButtonByBrand(_brandId, "A")), [&]()
			{
				LOG(Warning, "Controller A");
			}),
			new Action("ButtonB_" + to_string(_joystickId), ActionData(JoystickButtonPressed, _joystickId, Input::InputManager::GetJoystickButtonByBrand(_brandId, "B")), [&]()
			{
				LOG(Warning, "Controller B");
			}),
			new Action("ButtonX_" + to_string(_joystickId), ActionData(JoystickButtonPressed, _joystickId, Input::InputManager::GetJoystickButtonByBrand(_brandId, "X")), [&]()
			{
				LOG(Warning, "Controller X");
			}),
			new Action("ButtonY_" + to_string(_joystickId), ActionData(JoystickButtonPressed, _joystickId, Input::InputManager::GetJoystickButtonByBrand(_brandId, "Y")), [&]()
			{
				LOG(Warning, "Controller Y");
			}),
			new Action("ControllerInteract_" + to_string(_joystickId), ActionData(JoystickButtonPressed, _joystickId, Input::InputManager::GetJoystickButtonByBrand(_brandId, "A")) , [&]()
			{

			}),
			new Action("Disconnect_" + to_string(_joystickId), ActionData(JoystickDisconnected), [&](const float _joystickDisconnected)
			{
				if (CAST(int, _joystickDisconnected) != 0) return;
				_inputManager.DeleteActionMap("JoystickMovement");
			})
		}
	);
	_controllerAction->Enable();
}
