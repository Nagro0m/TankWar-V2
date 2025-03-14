#include "TankMovement.h"
#include <cmath>

TankMovement::TankMovement(Actor* _owner) : Component(_owner)
{
	moveSpeed = 200.0f;
	rotationSpeed = 50.0f;
	targetRotation = 0.0f;
}

TankMovement::TankMovement(Actor* _owner, const TankMovement* _other) : Component(_owner)
{
	moveSpeed = _other->moveSpeed;
	rotationSpeed = _other->rotationSpeed;
	direction = _other->direction;
	targetRotation = _other->targetRotation;
}

float TankMovement::InterpAngleConstantTo(float _current, float _target, float _deltaTime, float _speed)
{
    const float _delta = fmod(_target - _current + 180.0f, 360.0f) - 180.0f;

    const float _step = _speed * _deltaTime;

    if (fabs(_delta) <= _step)
        return _target;

    return _current + (_delta > 0 ? _step : -_step);
}

void TankMovement::Move(const float _deltaTime)
{
	const Vector2f& _offset = direction * moveSpeed * _deltaTime;
	owner->Move(_offset);
}

void TankMovement::Rotate(const float _deltaTime)
{
	const float _currentRot = owner->GetRotation().asDegrees();
	if (_currentRot == targetRotation) return;
	const float _newRot = InterpAngleConstantTo(_currentRot, targetRotation, _deltaTime, rotationSpeed);
	owner->SetRotation(degrees(_newRot));
}

void TankMovement::Tick(const float _deltaTime)
{
	Move(_deltaTime);
	Rotate(_deltaTime);
}

void TankMovement::ResetY()
{
	direction.y = 0;
	UpdateRotationTarget();
}

void TankMovement::ResetX()
{
	direction.x = 0;
	UpdateRotationTarget();
}

void TankMovement::ProcessYController(const float _controllerAxisY)
{
	direction.y = _controllerAxisY;
	if (!IsVector2fNull(direction))
	{
		direction = direction.normalized();
		UpdateDirection();
	}
}

void TankMovement::ProcessXController(const float _controllerAxisX)
{
	direction.x = _controllerAxisX;
	if (!IsVector2fNull(direction))
	{
		direction = direction.normalized();
		UpdateDirection();
	}
}

void TankMovement::UpdateDirection()
{
	if (!IsVector2fNull(direction))
	{
		direction = direction.normalized();
		UpdateRotationTarget();
	}
}

void TankMovement::UpdateRotationTarget()
{
	if (!IsVector2fNull(direction))
	{
		// Calcul de l'angle en fonction du joystick
		targetRotation = atan2(direction.y, direction.x) * (180.0f / pi);
	}
}