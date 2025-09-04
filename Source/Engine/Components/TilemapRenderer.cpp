#include "TilemapRenderer.h"
#include "Renderer/Tilemap.h"
#include "Engine.h"

namespace fox {
	FACTORY_REGISTER(TilemapRenderer)

	TilemapRenderer::TilemapRenderer(const TilemapRenderer& other) {
	}

	void TilemapRenderer::Start() {
		// Load the tilemap resource
		tilemap = Resources().Get<Tilemap>(tilemapName, GetEngine().GetRenderer());
		if (!tilemap) {
			Logger::Error("Could not load tilemap: {}", tilemapName);
			return;
		}
		
		// create physics bodies
		Transform transform;
		transform.scale = owner->transform.scale;
		transform.rotation = owner->transform.rotation;

		PhysicsBody::physicsBodyDef bodyDef;
		bodyDef.isDynamic = false;
		bodyDef.actor = owner;

		// iterate through layers
		for (auto layer : tilemap->GetLayers()) {

			if (!layer.hasCollision) continue;

			// get layer data (layout)
			for (int i = 0; i < layer.data.size(); i++) {
				int tileId = layer.data[i];
				if (tileId == 0) continue;

				rect source = tilemap->GetTextureRect(layer, tileId);
				vec2 position = owner->transform.position + (tilemap->GetPosition(layer, i) * owner->transform.scale);

				transform.position = position;
				vec2 size = vec2{ source.w, source.h };

				auto physicsBody = std::make_unique<PhysicsBody>(transform, size, bodyDef, GetEngine().GetPhysics());
				physicsBodies.push_back(std::move(physicsBody));
			}
		}
	}

	void TilemapRenderer::Update(float dt) {
		//
	}

	void TilemapRenderer::Draw(Renderer& renderer) {
		// iterate through layers
		for (auto layer : tilemap->GetLayers()) {
			// get layer data (layout)
			for (int i = 0; i < layer.data.size(); i++) {
				int tileId = layer.data[i];
				if (tileId == 0) continue;

				rect source = tilemap->GetTextureRect(layer, tileId);
				vec2 position = owner->transform.position + tilemap->GetPosition(layer, i) * owner->transform.scale;

				renderer.DrawTexture(*layer.texture, source, position.x, position.y, owner->transform.rotation, owner->transform.scale);
			}
		}
	}

	void TilemapRenderer::Read(const json::value_t& value) {
		Object::Read(value);

		JSON_READ_NAME(value, "tilemap_name", tilemapName);
	}
}