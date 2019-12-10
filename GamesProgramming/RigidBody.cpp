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
	m_rigidBody->setFriction(1);
}

void RigidBody::UpdateParent()
{
	//TODO: Get the transform from the rigidbody's motionstate and apply it to the game objects transform

	//get the transform from the rigibody's motionstate!
	//btTransform bt;
	//m_rigidBody->getMotionState()->getWorldTransform(bt);  
	//
	//std::cout << m_entity->GetTransform()->GetPosition().x << std::endl;
	//
	////and apply it to the game objects transform
	//m_entity->GetTransform()->SetPosition(glm::vec3(bt.getOrigin().getX(), bt.getOrigin().getY(), bt.getOrigin().getZ()));
	//m_entity->GetTransform()->SetRotation(glm::quat(bt.getRotation().getW(), bt.getRotation().getX(), bt.getRotation().getY(), bt.getRotation().getZ()));

	btTransform* newPos = &m_rigidBody->getWorldTransform();
	m_entity->GetTransform()->SetPosition(glm::vec3((float)newPos->getOrigin().getX(), (float)newPos->getOrigin().getY(), (float)newPos->getOrigin().getZ()));
	//m_entity->GetTransform()->SetRotation(glm::quat((float)newPos->getRotation().getW(), (float)newPos->getRotation().getX(), (float)newPos->getRotation().getY(), (float)newPos->getRotation().getZ()));
	
}

void RigidBody::UpdateRigidBody()
{
	btTransform t = Physics::ConvertTransformToBtTransform(*m_entity->GetTransform());
	
	m_rigidBody->setWorldTransform(t);
	m_rigidBody->getMotionState()->setWorldTransform(t);

	
}

