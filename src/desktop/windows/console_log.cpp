#include "console_log.h"

namespace to {
    ConsoleLogWindow::ConsoleLogWindow() : CommonWindow("Simulation Info") {

    }

    ConsoleLogWindow::~ConsoleLogWindow() {

    }

    void ConsoleLogWindow::run() {
        static bool open = true;

        ImGui::Begin("Console Log", &open);

        ImGui::ShowDemoWindow(NULL);

        if (ImGui::BeginChild("scrolling", ImVec2(0, 0), ImGuiChildFlags_None, ImGuiWindowFlags_HorizontalScrollbar)) {
            ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
            const char* buf = Buf.begin();
            const char* buf_end = Buf.end();

            ImGuiListClipper clipper;
            clipper.Begin(LineOffsets.Size);

            while (clipper.Step())
                for (int line_no = clipper.DisplayStart; line_no < clipper.DisplayEnd; ++line_no)
                    ImGui::Text("some text");

            clipper.End();

            ImGui::PopStyleVar();

            if (AutoScroll && ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
                ImGui::SetScrollHereY(1.0f);
        }

        ImGui::EndChild();
        ImGui::End();
    }
}
