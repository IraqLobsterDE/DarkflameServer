#include "JetPackBehavior.h"

#include "BehaviorBranchContext.h"
#include "GameMessages.h"

#include "Character.h"

void JetPackBehavior::Handle(BehaviorContext* context, RakNet::BitStream* bit_stream, const BehaviorBranchContext branch) {
	auto* entity = Game::entityManager->GetEntity(branch.target);

	GameMessages::SendSetJetPackMode(entity, true, this->m_BypassChecks, this->m_EnableHover, this->m_effectId, this->m_Airspeed, this->m_MaxAirspeed, this->m_VerticalVelocity, this->m_WarningEffectID);

	if (entity->IsPlayer()) {
		auto* character = entity->GetCharacter();

		if (character) {
			character->SetIsFlying(true);
		}
	}
}

void JetPackBehavior::UnCast(BehaviorContext* context, BehaviorBranchContext branch) {
	auto* entity = Game::entityManager->GetEntity(branch.target);

	GameMessages::SendSetJetPackMode(entity, false);

	if (entity->IsPlayer()) {
        auto* character = entity->GetCharacter();

        if (character) {
            character->SetIsFlying(false);
        }
    }
}

void JetPackBehavior::Calculate(BehaviorContext* context, RakNet::BitStream* bit_stream, const BehaviorBranchContext branch) {
	Handle(context, bit_stream, branch);
}

void JetPackBehavior::Load() {
	this->m_WarningEffectID = GetInt("warning_effect_id", -1);
	this->m_Airspeed = GetFloat("airspeed", 10);
	this->m_MaxAirspeed = GetFloat("max_airspeed", 15);
	this->m_VerticalVelocity = GetFloat("vertical_velocity", 1);
	this->m_EnableHover = GetBoolean("enable_hover", false);

	// TODO: Implement proper jetpack checks, so we can set this default to false
	this->m_BypassChecks = GetBoolean("bypass_checks", true); 
}
