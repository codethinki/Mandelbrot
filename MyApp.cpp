#include "MyApp.hpp"
#include "HlcSimpleRS.hpp"
#include <glm/glm.hpp>
#include <chrono>

namespace hlc {
	using namespace std;
	using namespace chrono;

	std::unique_ptr<HlcModel> createSquareModel(HlcDevice& device, const glm::vec2 position, const glm::vec2 extent) {
		std::vector<HlcModel::Vertex> vertices = {
			{{0.f, 0.f}, {1.f, 0.f, 0.f}},
			{{extent.x, extent.y},{1.f, 1.f, 0.f}},
			{{0.f, extent.y}, {0.f, 1.f, 0.f}},
			{{0.f, 0.f}, {1.f, 0.f, 0.f}},
			{{extent.x, 0.f}, {0.f, 0.f, 1.f}},
			{{extent.x, extent.y}, {1.f, 1.f, 0.f}},
		};
		for (auto& v : vertices) {
			v.position += position;
		}
		return std::make_unique<HlcModel>(device, vertices);
	}

	MyApp::MyApp() {}
	MyApp::~MyApp() {}

	void MyApp::run() {

		const shared_ptr squareModel = createSquareModel(hlcDevice, { -1.f, -1.f }, { 2.f, 2.f });
		auto square  = HlcGameObject::createGameObject();
		square.model = squareModel;

		SimpleRenderSystem simpleRenderSystem{ hlcDevice, hlcRenderer.getSwapchainRenderPass(), hlcDevice.wideShader };

		constexpr double zoomSpeed = 0.03, moveSpeed = 0.05;
		double zoom = 1, zoomY = 0, zoomX = 0;
		while (!hlcWindow.shouldClose()) {
			glfwPollEvents();
			const auto commandBuffer = hlcRenderer.beginFrame();
			if (commandBuffer != nullptr) {
				//update System
				if (hlcWindow.w) zoomY -= moveSpeed / zoom;
				if (hlcWindow.s) zoomY += moveSpeed / zoom;
				if (hlcWindow.a) zoomX -= moveSpeed / zoom;
				if (hlcWindow.d) zoomX += moveSpeed / zoom;

				simpleRenderSystem.windowSize = hlcWindow.getExtent();
				const double ratio =  static_cast<double>(simpleRenderSystem.windowSize.width) / simpleRenderSystem.windowSize.height;

				if(hlcWindow.mRight) simpleRenderSystem.detail > 1 ? simpleRenderSystem.detail-- : 0;
				if(hlcWindow.mLeft) simpleRenderSystem.detail++;

				if(hlcWindow.yScroll != 0) {
					zoom *=  1 + zoomSpeed * hlcWindow.yScroll * 3;
					hlcWindow.yScroll = 0;
				}

				simpleRenderSystem.extent = glm::vec4(zoomX - 2 * ratio / zoom, zoomX + 2 * ratio / zoom, zoomY - 2 / zoom, zoomY + 2 / zoom);

				//render
				hlcRenderer.beginSwapchainRenderPass(commandBuffer);
				simpleRenderSystem.renderSquare(commandBuffer, square);
				hlcRenderer.endSwapchainRenderPass(commandBuffer);
				hlcRenderer.endFrame();
			}
		}
		vkDeviceWaitIdle(hlcDevice.device());
	}
}
