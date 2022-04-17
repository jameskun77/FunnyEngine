#pragma once

#include <vector>
#include <map>

namespace Funny
{
	class Material;
	class Renderer;
	class Shader;
	class RenderTarget;

	class MaterialLibrary
	{
		friend Renderer;
	public:
		std::map<unsigned int, Material*> mDefaultMaterials;
		std::vector<Material*> mMaterials;

		Material* defaultBlitMaterial;

		Shader* deferredAmbientShader;
		Shader* deferredIrradianceShader;
		Shader* deferredDirectionalShader;
		Shader* deferredPointShader;

		Shader* dirShadowShader;

		Material* debugLightMaterial;

	public:
		MaterialLibrary(RenderTarget *gBuffer);
		~MaterialLibrary();

		// create either a deferred default material (based on default set of materials available (like glass)), or a custom material (with custom you have to supply your own shader)
		Material* CreateMaterial(std::string base);             // these don't have the custom flag set (default material has default state and uses checkerboard texture as albedo (and black metallic, half roughness, purple normal, white ao)
		Material* CreateCustomMaterial(Shader *shader);         // these have the custom flag set (will be rendered in forward pass)
		Material* CreatePostProcessingMaterial(Shader *shader); // these have the post-processing flag set (will be rendered after deferred/forward pass)
	private:
		// generate all default template materials
		void generateDefaultMaterials();
		// generate all internal materials used by the renderer; run in MaterialLibrary to improve readability.
		void generateInternalMaterials(RenderTarget *gBuffer);
	};
}