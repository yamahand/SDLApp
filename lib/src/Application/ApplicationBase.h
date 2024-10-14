#pragma once

#include <memory>

namespace lib {
class SDL;

class ApplicationBase {
protected:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="argc">引数の数</param>
    /// <param name="argv">引数</param>
    ApplicationBase(int argc, char* argv[]);

    ApplicationBase()                                  = delete;
    ApplicationBase(const ApplicationBase&)            = delete;
    ApplicationBase& operator=(const ApplicationBase&) = delete;
    ApplicationBase(ApplicationBase&&)                 = delete;
    ApplicationBase& operator=(ApplicationBase&&)      = delete;

    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~ApplicationBase();

public:
    void Run();

protected:
    /// <summary>
    /// 初期化処理
    /// </summary>
    /// <returns>true:成功 false:失敗</returns>
    virtual bool OnInitialize() = 0;

    /// <summary>
    /// 更新
    /// </summary>
    /// <returns>true:更新継続 false:終了</returns>
    virtual bool OnUpdate() = 0;

    /// <summary>
    /// 終了処理
    /// </summary>
    /// <returns>true:成功 false:失敗</returns>
    virtual void OnFinalize() = 0;

private:
    /// <summary>
    /// 初期化処理
    /// </summary>
    /// <returns></returns>
    bool Initialize();

    /// <summary>
    /// 更新
    /// </summary>
    /// <returns></returns>
    bool Update();

    /// <summary>
    /// 終了
    /// </summary>
    /// <returns></returns>
    void Finazlie();

protected:
};
}  // namespace lib
