#ifndef _TO_DESKTOP_MAP_PREVIEW_WINDOW_H_
#define _TO_DESKTOP_MAP_PREVIEW_WINDOW_H_

#include <functional>

#include "common_window.h"

namespace to {
    class MapPreviewWindow : public CommonWindow {
        private:
            bool showGrid = true;
            ImVec2 scrolling = ImVec2(0.0f, 0.0f);

        public:
            MapPreviewWindow();
            ~MapPreviewWindow() override;

            void run();
    };
}

#endif