#include "CppScripts.h"

class FrictionVolumeServer : public CppScripts::Script {
public:
	void OnStartup(Entity* self) override;
private:
	const float DefaultFrictionAmount = 1.5f;
};
