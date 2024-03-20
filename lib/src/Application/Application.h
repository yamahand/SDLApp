
class Application {
protected:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="argc">引数の数</param>
	/// <param name="argv">引数</param>
	Application(int argc, char* argv[]);

	Application() = delete;
	Application(const Application&) = delete;
	Application& operator=(const Application&) = delete;
	Application(Application&&) = delete;
	Application& operator=(Application&&) = delete;

	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~Application();

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
	virtual bool OnFinalize() = 0;

private:
	bool Initialize();

	bool Update();

	bool Finazlie();
};
