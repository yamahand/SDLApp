#include "Application.h"

#include <fstream>
#include <iostream>
#include <vector>

#include "imgui/imgui.h"
#include "sdl/SDL.h"
#include "sdl/SDLSprite.h"
#include "Math/Math.h"

namespace app {

void OutputFile() {
    // 新規バイナリファイルを作成する
    std::ofstream file("example.bin", std::ios::binary);
    if (!file) {
        std::cerr << "ファイルを開けませんでした。" << std::endl;
        return;
    }

    // バイナリデータを書き込むためのバッファを用意
    std::vector<char> buffer = {/* データを初期化 */};

    // バイナリデータをファイルに書き込む
    file.write(buffer.data(), buffer.size());

    // ファイルを閉じる
    file.close();

    std::cout << "バイナリファイルが作成されました。" << std::endl;
}

void ReadFile(std::vector<char>* pBuffer) {
    // バイナリファイルを開く
    std::ifstream file("data/CustomUVChecker_byValle_1K.bmp", std::ios::binary);
    if (!file) {
        std::cerr << "ファイルを開けませんでした。" << std::endl;
        return;
    }

    // ファイルの末尾までのサイズを取得
    file.seekg(0, std::ios::end);
    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);

    // データを格納するためのバッファを用意
    //std::vector<char> buffer(size);
    pBuffer->resize(size);
    // データを読み込む
    if (file.read(pBuffer->data(), size)) {
        /* 読み込んだデータの処理 */
        std::cout << "ファイルの内容を読み込みました。" << std::endl;
    } else {
        std::cerr << "ファイルの読み込みに失敗しました。" << std::endl;
    }
}

Application::Application(int argc, char* argv[])
    : ApplicationBase(argc, argv) {
}

Application::~Application() {
}

lib::SDLSprite* pSprite = nullptr;

bool Application::OnInitialize() {
    std::vector<char> buffer;
    ReadFile(&buffer);
    if (buffer.empty()) {
        return false;
    }

    auto* sprite = new lib::SDLSprite();
    char* pData = &buffer[0];
    sprite->Intialize(reinterpret_cast<uint8_t*>(pData), buffer.size());
    pSprite = sprite;
    return true;
}


void Application::OnUpdate() {
    static float x = 0;

    x += 10.0f * 0.016f;
    if (x >= 800) {
		x = 0;
	}

    pSprite->SetPosition(x, 0.0f);
    pSprite->Draw();
    if (ImGui::Begin("sprite pos")) {
        ImGui::End();
    }
}
void Application::OnFinalize() {
}

}  // namespace app
