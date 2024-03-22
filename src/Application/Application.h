#pragma once

#include "Application/ApplicationBase.h"

namespace app {

class Application : public lib::ApplicationBase {
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="argc">引数の数</param>
    /// <param name="argv">引数</param>
    Application(int argc, char* argv[]);

    Application()                              = delete;
    Application(const Application&)            = delete;
    Application& operator=(const Application&) = delete;
    Application(Application&&)                 = delete;
    Application& operator=(Application&&)      = delete;

    ~Application();

protected:
    /// <summary>
    /// 初期化処理
    /// </summary>
    /// <returns>true:成功 false:失敗</returns>
    bool OnInitialize() final;

    /// <summary>
    /// 更新
    /// </summary>
    /// <returns>true:更新継続 false:終了</returns>
    bool OnUpdate() final;

    /// <summary>
    /// 終了処理
    /// </summary>
    /// <returns>true:成功 false:失敗</returns>
    bool OnFinalize() final;
};

}  // namespace app
