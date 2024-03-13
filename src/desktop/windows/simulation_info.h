#ifndef _TO_DESKTOP_SIMULATION_INFO_H_
#define _TO_DESKTOP_SIMULATION_INFO_H_

#include <functional>

#include "common_window.h"

namespace to {
    class SimulationInfoWindow : public CommonWindow {
        private:

        public:
            SimulationInfoWindow();
            ~SimulationInfoWindow();

            void run();
    };
}

#endif