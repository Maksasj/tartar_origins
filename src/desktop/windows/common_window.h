#ifndef _TO_DESKTOP_WINDOW_COMMON_WINDOW_H_
#define _TO_DESKTOP_WINDOW_COMMON_WINDOW_H_

#include "bebone/bebone.h"

#include <string>

namespace to {
    class CommonWindow {
    private:
        const std::string title;
        bool focused;
        bool open;

        void update_iternal_state();

    protected:
        bool start_window();

        void end_window();

    public:
        CommonWindow(const std::string& title, const bool& open = true);

        virtual ~CommonWindow();

        const bool& is_focused() const;
        const bool& is_open() const;
        bool& ref_open_flag();

        void force_open();
        void force_close();
    };
}

#endif