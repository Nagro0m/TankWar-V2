#pragma once
#include "Component.h"
#include "Actor.h"

class TankMovement : public Component
{
protected:
	float moveSpeed;
	float rotationSpeed;
	Vector2f direction;
	float targetRotation;

public:
	FORCEINLINE Vector2f GetDirection() const { return direction; }
	FORCEINLINE void SetDirection(const Vector2f _direction) { direction = _direction; }
	FORCEINLINE void SetMoveSpeed(const float _speed) { moveSpeed = _speed; }
	FORCEINLINE void SetRotationSpeed(const float _speed) { rotationSpeed = _speed; }

	FORCEINLINE virtual Component* Clone(Actor* _owner) const
	{
		return new TankMovement(_owner, this);
	}

private:
	FORCEINLINE bool IsVector2fNull(const Vector2f& _vectorDirection)
	{
		return _vectorDirection.x == 0.0f && _vectorDirection.y == 0.0f;
	}

public:
	TankMovement(Actor* _owner);
	TankMovement(Actor* _owner, const TankMovement* _other);

protected: 
	float InterpAngleConstantTo(float _current, float _target, float _deltaTime, float _speed);
	virtual void Move(const float _deltaTime);
	virtual void Rotate(const float _deltaTime);

public:
	virtual void Tick(const float _deltaTime);
	void ResetY();
	void ResetX();
	void ProcessYController(const float _controllerAxisY);
	void ProcessXController(const float _controllerAxisX);
	void UpdateDirection();
	void UpdateRotationTarget();
};

