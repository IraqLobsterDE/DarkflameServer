#pragma once

#include "BitStream.h"
#include "Entity.h"
#include "PhysicsComponent.h"
#include "eReplicaComponentType.h"

struct RemoteInputInfo {
	RemoteInputInfo() {
		m_RemoteInputX = 0;
		m_RemoteInputY = 0;
		m_IsPowersliding = false;
		m_IsModified = false;
	}

	void operator=(const RemoteInputInfo& other) {
		m_RemoteInputX = other.m_RemoteInputX;
		m_RemoteInputY = other.m_RemoteInputY;
		m_IsPowersliding = other.m_IsPowersliding;
		m_IsModified = other.m_IsModified;
	}

	bool operator==(const RemoteInputInfo& other) {
		return m_RemoteInputX == other.m_RemoteInputX && m_RemoteInputY == other.m_RemoteInputY && m_IsPowersliding == other.m_IsPowersliding && m_IsModified == other.m_IsModified;
	}

	float m_RemoteInputX;
	float m_RemoteInputY;
	bool m_IsPowersliding;
	bool m_IsModified;
};

/**
 * Physics component for vehicles.
 */
class VehiclePhysicsComponent : public PhysicsComponent {
public:
	inline static const eReplicaComponentType ComponentType = eReplicaComponentType::VEHICLE_PHYSICS;

	VehiclePhysicsComponent(Entity* parentEntity);

	void Serialize(RakNet::BitStream* outBitStream, bool bIsInitialUpdate) override;

	void Update(float deltaTime) override;

	/**
	 * Sets the velocity
	 * @param vel the new velocity
	 */
	void SetVelocity(const NiPoint3& vel);

	/**
	 * Gets the velocity
	 * @return the velocity
	 */
	const NiPoint3& GetVelocity() const { return m_Velocity; }

	/**
	 * Sets the angular velocity
	 * @param vel the new angular velocity
	 */
	void SetAngularVelocity(const NiPoint3& vel);

	/**
	 * Gets the angular velocity
	 * @return the angular velocity
	 */
	const NiPoint3& GetAngularVelocity() const { return m_AngularVelocity; }

	/**
	 * Sets whether the vehicle is on the ground
	 * @param val whether the vehicle is on the ground
	 */
	void SetIsOnGround(bool val);

	/**
	 * Gets whether the vehicle is on the ground
	 * @return whether the vehicle is on the ground
	 */
	const bool GetIsOnGround() const { return m_IsOnGround; }

	/**
	 * Gets whether the vehicle is on rail
	 * @return whether the vehicle is on rail
	 */
	void SetIsOnRail(bool val);

	/**
	 * Gets whether the vehicle is on rail
	 * @return whether the vehicle is on rail
	 */
	const bool GetIsOnRail() const { return m_IsOnRail; }

	void SetDirtyPosition(bool val);
	void SetDirtyVelocity(bool val);
	void SetDirtyAngularVelocity(bool val);
	void SetRemoteInputInfo(const RemoteInputInfo&);

private:
	bool m_DirtyVelocity;
	NiPoint3 m_Velocity;

	bool m_DirtyAngularVelocity;
	NiPoint3 m_AngularVelocity;
	bool m_IsOnGround;
	bool m_IsOnRail;

	float m_SoftUpdate = 0;
	uint32_t m_EndBehavior;
	RemoteInputInfo m_RemoteInputInfo;
	bool m_DirtyRemoteInput;
};
