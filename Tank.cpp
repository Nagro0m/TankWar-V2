#include "Tank.h"
#include "Level.h"
#include "InputManager.h"
#define CONTROLLER_DEAD_ZONE 0.2f
using namespace Input;

Tank::Tank(Level* _level, const string& _name) : Pawn(_level, _name)
{
}

Tank::Tank(const Tank& _other) : Pawn(_other)
{
	mesh = _other.mesh;
	collision = _other.collision;
}

void Tank::SetupInputController(Input::InputManager& _inputManager)
{
	ActionMap* _moveInputs = _inputManager.CreateActionMap("PlayerMovement");

	_moveInputs->AddActions(
		{
			new Action("Connected", ActionData(JoystickConnected), [&](const float _joystick)
			{
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
	LOG(Display, "XboxID :" + to_string(_brandId));
	_controllerAction->AddActions(
		{
			new Action("ControllerY_" + to_string(_joystickId), ActionData(JoystickMoved, _joystickId, Input::InputManager::GetJoystickAxeByBrand(_brandId, "LeftJoystickY")), [&](const float _normal)
			{
				LOG(Warning, "Y movement");
				if (!(_normal > CONTROLLER_DEAD_ZONE || _normal < -CONTROLLER_DEAD_ZONE))
				{

				}

			}),
			new Action("ControllerX_" + to_string(_joystickId), ActionData(JoystickMoved, _joystickId, Input::InputManager::GetJoystickAxeByBrand(_brandId, "LeftJoystickX")), [&](const float _normal)
			{


			}),
			new Action("ControllerDash_" + to_string(_joystickId), ActionData(JoystickButtonPressed, _joystickId, Input::InputManager::GetJoystickButtonByBrand(_brandId, "B")) , [&]()
			{

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
