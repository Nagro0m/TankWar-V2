#include "TankMovement.h"
#include <cmath>

TankMovement::TankMovement(Actor* _owner) : Component(_owner)
{
	moveSpeed = 0.0f;
	maxMoveSpeed = 200.0f;
	rotationSpeed = 100.0f;
	lastRotation = 0.0f;
}

TankMovement::TankMovement(Actor* _owner, const TankMovement* _other) : Component(_owner)
{
	moveSpeed = _other->moveSpeed;
	rotationSpeed = _other->rotationSpeed;
	direction = _other->direction;
	lastRotation = _other->lastRotation;
}

float TankMovement::InterpAngleConstantTo(float _current, float _target, float _deltaTime, float _speed)
{
	float _delta = fmod(_target - _current + 180.0f, 360.0f) - 180.0f;

	if (_delta > 180.0f)
		_delta -= 360.0f;
	else if (_delta < -180.0f)
		_delta += 360.0f;

	const float _step = _speed * _deltaTime;

	if (fabs(_delta) <= _step)
		return _target;

	return _current + (_delta > 0 ? _step : -_step);
}


void TankMovement::Move(const float _deltaTime)
{
	const Vector2f& _offset = direction * moveSpeed * _deltaTime;
	owner->SetPosition(owner->GetPosition() + _offset);
}

void TankMovement::Rotate(const float _deltaTime)
{
	float _radians = (owner->GetRotation().asDegrees() - 90.0f) * pi / 180.0f;
	Vector2f _direction = Vector2f(cos(_radians), sin(_radians));
	direction = _direction;

	//Si la valeur de rotation est supérieur a 0.6 ou inférieur a -0.6 alors on tourne plus vite, sinon on tourne plus lentement
	const float _sign = lastRotation >= 0.0f ? 1.0f : -1.0f;
	if (lastRotation == 0.0f) return;
	if (lastRotation > 0.6f || lastRotation < -0.6f)
	{
		//Get sign of the rotation
		owner->SetRotation(owner->GetRotation() + degrees(50) * _sign * _deltaTime);
	}
	else
	{
		owner->SetRotation(owner->GetRotation() + degrees(25) * _sign * _deltaTime);
	}
}

void TankMovement::Tick(const float _deltaTime)
{
	Super::Tick(_deltaTime);
	Move(_deltaTime);
	Rotate(_deltaTime);
}

void TankMovement::ProcessYController(const float _controllerAxisY)
{
}

void TankMovement::ProcessXController(const float _controllerAxisX)
{
	lastRotation = _controllerAxisX;
}

void TankMovement::ProcessBackRightController(const float _controllerBackRight)
{
	LOG(Warning, to_string(_controllerBackRight));

	const float _speed = MapTriggerToSpeed(_controllerBackRight);
	moveSpeed = _speed * maxMoveSpeed;
	if (_controllerBackRight == -1)
	{
		moveSpeed = 0.0f;
		return;
	}

	if (_controllerBackRight <= 0.1f)
	{
		moveSpeed = 0.1f * maxMoveSpeed;
	}
}

void TankMovement::ProcessBackLeftController(const float _controllerBackRight)
{
	if (moveSpeed > 0) moveSpeed = 0.0f;
	else moveSpeed = -0.1f * maxMoveSpeed;
}

float TankMovement::MapTriggerToSpeed(float triggerValue)
{
	return round(triggerValue * 5.0f) * 0.2f;
}
