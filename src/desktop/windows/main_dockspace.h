#ifndef _TO_DESKTOP_MAIN_DOCKSPACE_H_
#define _TO_DESKTOP_MAIN_DOCKSPACE_H_

#include <functional>
#include "common_window.h"

namespace to {
    class MainDockspaceWindow : public CommonWindow {
        private:

        public:
            MainDockspaceWindow();
            ~MainDockspaceWindow();

            void run(const std::function<void(void)>& dockSpaceBody);
    };
}

#endif