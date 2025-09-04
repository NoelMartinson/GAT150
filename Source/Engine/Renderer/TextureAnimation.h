#pragma once

namespace fox {
	class Texture;

	class TextureAnimation : public Resource {
	public:
		TextureAnimation() = default;
		~TextureAnimation() = default;

		bool Load(const std::string& filename, class Renderer& renderer);

		vec2 GetSize() const;

		rect GetFrameRect(int frame) const;
		int GetTotalFrames() const { return totalFrames; }
		float GetFPS() const { return framesPerSecond; }
		bool IsValidFrame(int frame) const { return frame >= 0 && frame < totalFrames; }
		bool IsLooping() const { return loop; }

		res_t<Texture> GetTexture() { return texture; }

	private:
		int columns = 0;
		int rows = 0;
		int startFrame = 0;
		int totalFrames = 0;
		float framesPerSecond = 0;
		bool loop = true;

		res_t<Texture> texture;
	};
}