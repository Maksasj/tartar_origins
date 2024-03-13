#include "to_app.h"

#define TO_SERVER_PORT 6969
#define TO_SERVER_ADDRESS "127.0.0.1"

namespace to {
    const unsigned int SCR_WIDTH = 800;
    const unsigned int SCR_HEIGHT = 600;

    using namespace bebone::gfx;
    using namespace bebone::gfx::opengl;

    void TOApp::init() {
        GLFWContext::init();

        window = WindowFactory::create_window("TODesktop", SCR_WIDTH, SCR_HEIGHT, GfxAPI::OPENGL);

        GLContext::load_opengl();
        GLContext::set_viewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

        // Loading and setting up imgui
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();

        ImGuiIO &io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_None;
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

        ImGui::CreateContext();
        ImGui::StyleColorsDark();
        ImGui_ImplGlfw_InitForOpenGL(window->get_backend(), true);
        ImGui_ImplOpenGL3_Init("#version 330");

        mainDockspaceWindow = std::make_shared<MainDockspaceWindow>();

        mapPreviewWindow = std::make_shared<MapPreviewWindow>();
        simulationInfoWindow = std::make_shared<SimulationInfoWindow>();
    }

    void TOApp::load() {
        client = to_new_client();
        if(client == NULL) {
            // return 1;
        }

        int res = to_client_connect(client, TO_SERVER_ADDRESS, TO_SERVER_PORT);

        if(!res) {
            // TO_LOG(TO_ERROR, "Failed to connect to server");
            // return 0;
        }
    }

    void TOApp::run() {
        while (!window->closing()) {
            GLContext::clear_color(0.2f, 0.2f, 0.2f, 1.0f);
            GLContext::clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            mainDockspaceWindow->run([&]() {
                mapPreviewWindow->run();
                simulationInfoWindow->run();
            });

            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            GLFWContext::swap_buffers(*window);
            GLFWContext::poll_events();
        }
    }

    void TOApp::cleanup() {
        to_close_client(client);
        to_free_client(client);
    }

    void TOApp::terminate() {
        GLFWContext::terminate();
    }
}
