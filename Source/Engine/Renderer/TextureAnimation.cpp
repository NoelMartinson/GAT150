#include "TextureAnimation.h"

namespace fox {
	bool TextureAnimation::Load(const std::string& filename, class Renderer& renderer) {
		fox::json::document_t document;
		if (!fox::json::Load(filename, document)) {
			Logger::Error("Could not load TextureAnimation {}", filename);
			return false;
		}

		std::string texture_name;
		JSON_READ(document, texture_name);

		texture = Resources().Get<Texture>(texture_name, renderer);
		if (!texture) {
			Logger::Error("Could not load texture in Texture Animation {}", texture_name);
		}

		JSON_READ_NAME(document, "columns", columns);
		JSON_READ_NAME(document, "rows", rows);
		JSON_READ_NAME(document, "start_frame", startFrame);
		JSON_READ_NAME(document, "total_frames", totalFrames);
		JSON_READ_NAME(document, "frames_per_second", framesPerSecond);
		JSON_READ_NAME(document, "loop", loop);

		return true;
	}

	vec2 TextureAnimation::GetSize() const {
		vec2 size = texture->GetSize();

		return { size.x / columns, size.y / rows };
	}

	rect TextureAnimation::GetFrameRect(int frame) const {
		if (!IsValidFrame(frame)) {
			Logger::Warning("Frame is outside bounds {}/{}", frame, totalFrames);
			frame = 0;
		}

		rect frameRect;
		vec2 size = GetSize();

		frameRect.w = size.x;
		frameRect.h = size.y;
		frameRect.x = ((startFrame + frame) % columns) * frameRect.w;
		frameRect.y = ((startFrame + frame) / columns) * frameRect.h;

		return frameRect;
	}
}