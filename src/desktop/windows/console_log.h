#ifndef _TO_DESKTOP_CONSOLE_LOG_H_
#define _TO_DESKTOP_CONSOLE_LOG_H_

#include <functional>

#include "common_window.h"

namespace to {
    class ConsoleLogWindow : public CommonWindow {
        private:
            ImGuiTextBuffer     Buf;
            ImGuiTextFilter     Filter;
            ImVector<int>       LineOffsets;
            bool                AutoScroll;

        public:
            ConsoleLogWindow();
            ~ConsoleLogWindow();

            void run();
    };
}

#endif