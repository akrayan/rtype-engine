#pragma once
#include "IComponent.h"
class Script :
	public IComponent
{
public:
	Script() {}
	virtual ~Script() {}

	virtual void Start() {}
	virtual void Update() {}
	virtual void OnCollisionEnter(Collision *col) {}
	virtual void OnClientConnect(int id) {}

};

