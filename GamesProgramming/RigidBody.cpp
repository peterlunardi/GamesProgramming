#include "pch.h"
#include "RigidBody.h"
#include "Physics.h"
#include "Entity.h"

void RigidBody::OnUpdate(float deltaTime)
{
}

void RigidBody::OnRender()
{
}

void RigidBody::Init(CollisionShape* shape, float mass, const glm::vec3 localInertia)
{
	btTransform bT = Physics::ConvertTransformToBtTransform(*m_entity->GetTransform());	
	m_mState = new btDefaultMotionState(bT);
	m_shape = shape;
	btVector3 li = btVector3(localInertia.x, localInertia.y, localInertia.z);
	m_shape->Get()->calculateLocalInertia(mass, li);
	m_rigidBody = new btRigidBody(btScalar(mass), m_mState, m_shape->Get(), li);
	Physics::GetInstance()->AddRigidbody(this);
	m_rigidBody->setSleepingThresholds(0, 0);
	m_rigidBody->setFriction(2);
}

void RigidBody::UpdateParent()
{
	//TODO: Get the transform from the rigidbody's motionstate and apply it to the game objects transform

	//get the transform from the rigibody's motionstate!
	btTransform bt;
	m_rigidBody->getMotionState()->getWorldTransform(bt);  
	
	//and apply it to the game objects transform
	m_entity->GetTransform()->SetRotation(glm::quat(bt.getRotation().getW(), bt.getRotation().getX(), bt.getRotation().getY(), bt.getRotation().getZ()));
	m_entity->GetTransform()->SetPosition(glm::vec3(bt.getOrigin().getX(), bt.getOrigin().getY(), bt.getOrigin().getZ()));
	

	
}

void RigidBody::UpdateRigidBody()
{
	btTransform t = Physics::ConvertTransformToBtTransform(*m_entity->GetTransform());
	
	m_rigidBody->setWorldTransform(t);
	m_rigidBody->getMotionState()->setWorldTransform(t);	
}

void RigidBody::ApplyForce(float f)
{
	btTransform bt;
	m_rigidBody->getMotionState()->getWorldTransform(bt);
	//m_rigidBody->applyForce(btVector3(0, -2, 1), m_rigidBody->getCenterOfMassPosition());
	m_rigidBody->applyCentralImpulse(btVector3(1 * f, 0, 0));
	//m_rigidBody->applyCentralForce(btVector3(100, 0, 0));

	m_entity->GetTransform()->SetRotation(glm::quat(bt.getRotation().getW(), bt.getRotation().getX(), bt.getRotation().getY(), bt.getRotation().getZ()));
	m_entity->GetTransform()->SetPosition(glm::vec3(bt.getOrigin().getX(), bt.getOrigin().getY(), bt.getOrigin().getZ()));
}

void RigidBody::ApplyForce(btVector3 forceVector)
{
	btTransform bt;
	m_rigidBody->getMotionState()->getWorldTransform(bt);
	//m_rigidBody->applyForce(btVector3(0, -2, 1), m_rigidBody->getCenterOfMassPosition());
	m_rigidBody->applyCentralImpulse(forceVector);
	//m_rigidBody->applyCentralForce(btVector3(100, 0, 0));

	m_entity->GetTransform()->SetRotation(glm::quat(bt.getRotation().getW(), bt.getRotation().getX(), bt.getRotation().getY(), bt.getRotation().getZ()));
	m_entity->GetTransform()->SetPosition(glm::vec3(bt.getOrigin().getX(), bt.getOrigin().getY(), bt.getOrigin().getZ()));
}

void RigidBody::ApplyTorque(float f)
{
	btTransform bt;
	m_rigidBody->getMotionState()->getWorldTransform(bt);

	m_rigidBody->applyTorqueImpulse(btVector3(1 * f, 0, 0));

	m_entity->GetTransform()->SetRotation(glm::quat(bt.getRotation().getW(), bt.getRotation().getX(), bt.getRotation().getY(), bt.getRotation().getZ()));
	m_entity->GetTransform()->SetPosition(glm::vec3(bt.getOrigin().getX(), bt.getOrigin().getY(), bt.getOrigin().getZ()));
}

