#ifndef _TO_DESKTOP_APP_H_
#define _TO_DESKTOP_APP_H_

#include "windows/windows.h"

extern "C" {
    #include "client/to_client.h"
}

namespace to {
    class TOApp {
        private:
            std::shared_ptr<bebone::gfx::Window> window;
            TOClient* client;

            std::shared_ptr<MainDockspaceWindow> mainDockspaceWindow;

            std::shared_ptr<MapPreviewWindow> mapPreviewWindow;
            std::shared_ptr<SimulationInfoWindow> simulationInfoWindow;
            std::shared_ptr<ConsoleLogWindow> consoleLogWindow;

        public:
            void init();
            void load();
            void run();
            void cleanup();
            void terminate();
    };
}


#endif