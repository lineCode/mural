#include "../src/MuGlobals.h"
#include "../src/MuCore.h"

#include "../src/MuAppController.h"
#include "../src/MuInputEvent.h"

#include <cstdio>

// Create a controller class for testing
class GameController : public mural::MuAppController {
    private:
        bool leftBtn, rightBtn;
        bool alt, ctrl, meta, shift;
        int mouseX, mouseY;
    public:
        GameController():
            leftBtn(false), rightBtn(false),
            alt(false), ctrl(false), meta(false), shift(false),
            mouseX(0), mouseY(0)
        {}
        void init() {
            app.addEventListener(this, mural::MouseEvent::MOUSE_DOWN);
            app.addEventListener(this, mural::MouseEvent::MOUSE_UP);
            app.addEventListener(this, mural::MouseEvent::MOUSE_MOVE);
        }
        void render() {
            float strokeWidth = 6.0f;
            nvgStrokeWidth(g, strokeWidth);
            nvgStrokeColor(g, nvgRGB(255, 255, 255));

            float marginLeft = 100.0f, marginTop = 100.0f;
            float w = 240.0f, h = 340.0f;
            float btnHeight = 120.0f;

            // Left button
            if (leftBtn) {
                nvgBeginPath(g);
                nvgRect(g, marginLeft + strokeWidth / 2, marginTop, w / 2 - strokeWidth, btnHeight - strokeWidth);
                nvgFillColor(g, nvgRGB(0, 255, 255));
                nvgFill(g);
            }
            // Right button
            if (rightBtn) {
                nvgBeginPath(g);
                nvgRect(g, marginLeft + w / 2 + strokeWidth / 2, marginTop, w / 2 - strokeWidth, btnHeight - strokeWidth);
                nvgFillColor(g, nvgRGB(0, 255, 255));
                nvgFill(g);
            }

            // Mouse body
            nvgBeginPath(g);
            nvgRoundedRect(g, marginLeft, marginTop, w, h, 12.0f);
            nvgStroke(g);
            nvgBeginPath(g);
            nvgMoveTo(g, marginLeft + w / 2, marginTop + strokeWidth / 2);
            nvgLineTo(g, marginLeft + w / 2, marginTop + btnHeight);
            nvgMoveTo(g, marginLeft, marginTop + btnHeight - strokeWidth / 2);
            nvgLineTo(g, marginLeft + w, marginTop + btnHeight - strokeWidth / 2);
            nvgStroke(g);

            nvgFontSize(g, 32);
            nvgTextAlign(g, NVG_ALIGN_LEFT | NVG_ALIGN_MIDDLE);
            std::string text("Position: (");
            text += std::to_string(mouseX); text += ", ";
            text += std::to_string(mouseY); text += ")";
            nvgText(g, 110.0f, 70.0f, text.c_str(), NULL);

            nvgBeginPath(g);
            // TODO: draw buttons
        }
        void handleEvent(mural::Event *evt) {
            mural::MouseEvent *mouse = dynamic_cast<mural::MouseEvent *>(evt);

            if (mouse) {
                leftBtn = mouse->buttons & 1;
                rightBtn = mouse->buttons & 2;

                mouseX = mouse->x;
                mouseY = mouse->y;

                alt = mouse->altDown;
                ctrl = mouse->ctrlDown;
                meta = mouse->metaDown;
                shift = mouse->shiftDown;
            }
        }
};

int main(int argc, char const *argv[]) {
    // Initialize everything
    app.init();
    // Set a game controller which provides REAL logic
    app.setController(new GameController);
    // Start the game
    app.start();
    // Cleanup anything and quit
    app.terminate();

    return 0;
}
